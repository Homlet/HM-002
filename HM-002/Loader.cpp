// "Loader.cpp"
//

#include "Base.h"

#include "Loader.h"

using namespace render::texture;


Loader* Loader::_instance;


// --------------------------------------------------------------------------------------------------------------------
//  Override public constructor
//
Loader::Loader( void )
{

}


// --------------------------------------------------------------------------------------------------------------------
//  Binds, buffers texture from raw data
//
GLuint Loader::_loadTexture( char* path, int w, int h ) const
{
	glActiveTexture( GL_TEXTURE0 + 1 );

	GLuint id;
	glGenTextures( 1, &id );
	glBindTexture( GL_TEXTURE_2D, id );

	unsigned char* data = _rawRGB_TGA( path, &w, &h );
	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0] );
	glGenerateMipmap( GL_TEXTURE_2D );

	glBindTexture( GL_TEXTURE_2D, 0 );
	
	glActiveTexture( GL_TEXTURE0 );

	return id;
}


// --------------------------------------------------------------------------------------------------------------------
//  Binds, buffers texture array from raw data
//
GLuint Loader::_loadTextureArray( char** paths, int count, int w, int h ) const
{
	glActiveTexture( GL_TEXTURE0 + 2 );

	GLuint id;
	glGenTextures( 1, &id );
	glBindTexture( GL_TEXTURE_2D_ARRAY, id );
	
	glTexParameteri( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT );

	glTexImage3D( GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, w, h, count, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );

	for ( int i = 0; i < count; i++ )
	{
		unsigned char* data = _rawRGB_TGA( paths[i], &w, &h );
		glTexSubImage3D( GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, w, h, 1, GL_RGBA, GL_UNSIGNED_BYTE, &data[0] );
	}

	glGenerateMipmap( GL_TEXTURE_2D_ARRAY );

	glBindTexture( GL_TEXTURE_2D_ARRAY, 0 );
	
	glActiveTexture( GL_TEXTURE0 );

	return id;
}


// --------------------------------------------------------------------------------------------------------------------
//  Loads an RGB targa of specified width and height
//
unsigned char* Loader::_rawRGB_TGA(char *filename, int *w, int *h) const
{
	FILE *file = fopen(filename, "rb");
	if (file == NULL)
	{
		printf("Could not open the file: %s\n", filename);
		exit(0);
	}

	unsigned char header[20];

	// Read all 18 bytes of the header
	fread(header, sizeof(char), 18, file);

	// Should be image type 2 (color) or type 10 (rle compressed color)
	if (header[2] != 2 && header[2] != 10)
	{
		fclose(file);
		exit(0);
	}

	if (header[0])
	{
		fseek(file, header[0], SEEK_CUR);
	}

	// Get the size and bitdepth from the header
	int m_width = header[13] * 256 + header[12];
	int m_height = header[15] * 256 + header[14];
	int m_bpp = header[16] / 8;
	*w = m_width;
	*h = m_height;

	if (m_bpp != 3 && m_bpp != 4)
	{
		fclose(file);
		exit(0);
	}

	int imageSize = m_width * m_height * m_bpp;

	// Allocate memory for image data
	unsigned char *data = new unsigned char[imageSize];

	// Read the uncompressed image data if type 2
	if (header[2] == 2)
	{
		fread(data, sizeof(char), imageSize, file);
	}

	long ctpixel = 0,
		 ctloop = 0;

	// Read the compressed image data if type 10
	if (header[2] == 10)
	{
		// Stores the rle header and the temp color data
		unsigned char rle;
		unsigned char color[4];

		while (ctpixel < imageSize)
		{
			// Reads the the RLE header
			fread(&rle, 1, 1, file);

			// If the rle header is below 128 it means that what folows is just raw data with rle+1 pixels
			if (rle < 128)
			{
				fread(&data[ctpixel], m_bpp, rle+1, file);
				ctpixel += m_bpp*(rle+1);
			}

			// If the rle header is equal or above 128 it means that we have a string of rle-127 pixels
			// that use the folowing pixels color
			else
			{
				// Read what color we should use
				fread(&color[0], 1, m_bpp, file);

				// Insert the color stored in tmp into the folowing rle-127 pixels
				ctloop = 0;
				while (ctloop < (rle-127))
				{
					data[ctpixel] = color[0];
					data[ctpixel+1] = color[1];
					data[ctpixel+2] = color[2];
					if (m_bpp == 4)
					{
						data[ctpixel+3] = color[3];
					}

					ctpixel += m_bpp;
					ctloop++;
				}
			}
		}
	}

	ctpixel=0;

	// Because TGA file store their colors in BGRA format we need to swap the red and blue color components
	unsigned char temp;
	while (ctpixel < imageSize)
	{
		temp = data[ctpixel];
		data[ctpixel] = data[ctpixel+2];
		data[ctpixel+2] = temp;
		ctpixel += m_bpp;
	}

	// Close file
	fclose(file);

	return data;
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns a pointer to the singleton object
//
Loader* Loader::getInstance( void )
{
	if ( !_instance )
		_instance = new Loader();

	return _instance;
}


// --------------------------------------------------------------------------------------------------------------------
//  Loads textures, and returns pointer to std::vector of textures, as defined in xml with the following format:
//
//  <Texture>    : new texture_object
//     -> name   : string format, name of texture (used for reference)
//     -> path   : filename, or relative or absolute path
//     -> w      : integer, width of texture in pixels
//     -> h      : integer, height of texture in pixels
//
std::hash_map<std::string, render::texture_object, hashdef::hash_std_string>* Loader::loadFromXML( char* path ) const
{
	std::hash_map<
		std::string,
		render::texture_object,
		hashdef::hash_std_string
	>* textureObjectMap = new std::hash_map<std::string, render::texture_object, hashdef::hash_std_string>();

	using namespace rapidxml;

	// Load xml file as raw text data
	std::ifstream file;
	file.open( path, std::ios::in );
	std::string xmlRaw;
	while( file.is_open() )
	{
		std::string temp;

		while( file.good() )
		{
			getline( file, temp );
			xmlRaw.append( temp );
		}

		file.close();
	}

	// Add null terminator for RapidXML
	xmlRaw.append( "\0" );

	// Create and parse XML document
	xml_document<> xml;
	xml.parse<0>( &xmlRaw[0] );
	xml_node<>* arrayNode = xml.first_node( "Definitions" )->first_node( "Array" );

	// First check for array textures
	while ( arrayNode )
	{
		// Load individual textures within array
		xml_node<>* textureNode = arrayNode->first_node( "Texture" );
		std::vector<char*> paths;
		int count = 0;
		while ( textureNode != 0 )
		{
			// Push each texture uri to the vector, increment count
			paths.push_back( textureNode->first_attribute( "path" )->value() );
			count++;

			textureNode = textureNode->next_sibling();
		}
		
		// Load array attributes
		xml_attribute<>* name = arrayNode->first_attribute( "name" );
		xml_attribute<>* w = arrayNode->first_attribute( "w" );
		xml_attribute<>* h = arrayNode->first_attribute( "h" );

		// Bind and buffer data, get id
		GLuint id = _loadTextureArray( &paths[0], count, std::stoi( w->value() ), std::stoi( h->value() ) );

		// Create texture object for array, push it to the final map
		texture_object temp = { id, std::stoi( w->value() ), std::stoi( h->value() ), true };
		(*textureObjectMap)[name->value()] = temp;

		arrayNode = arrayNode->next_sibling();
	}
	
	// Then individual textures
	xml_node<>* textureNode = xml.first_node( "Definitions" )->first_node( "Texture" );
	while ( textureNode != 0 )
	{
		// Load texture attributes
		xml_attribute<>* name = textureNode->first_attribute( "name" );
		xml_attribute<>* path = textureNode->first_attribute( "path" );
		xml_attribute<>* w = textureNode->first_attribute( "w" );
		xml_attribute<>* h = textureNode->first_attribute( "h" );
		
		// Bind and buffer data, get id
		GLuint id = _loadTexture( path->value(), std::stoi( w->value() ), std::stoi( h->value() ) );
		
		// Create texture object for array, push it to the final map
		texture_object temp = { id, std::stoi( w->value() ), std::stoi( h->value() ), false };
		(*textureObjectMap)[name->value()] = temp;

		textureNode = textureNode->next_sibling();
	}
	
	return textureObjectMap;
}
