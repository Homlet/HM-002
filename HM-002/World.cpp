// "World.cpp"
//

#include "WorldMacros.h"

#include "Base.h"

#include "Buffer.h"
#include "Provider.h"
#include "noise\noise.h"
#include "Generator.h"
#include "Chunk.h"

#include "World.h"

using namespace update;


// --------------------------------------------------------------------------------------------------------------------
//  Populates hash_map with block data from xml file specified
//
std::hash_map<world::block::BlockType, world::block_data>* World::loadBlockDataFromXML( char* path )
{
	std::hash_map<
		world::block::BlockType,
		world::block_data
	>* blockData = new std::hash_map<
		world::block::BlockType,
		world::block_data
	>();

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
	xml_node<>* blockNode = xml.first_node( "Definitions" );
	blockNode = blockNode->first_node( "Block" );
	while ( blockNode != 0 )
	{
		xml_attribute<>* block_type = blockNode->first_attribute( "block_type" );
		xml_attribute<>* r = blockNode->first_attribute( "r" );

		world::block_data data = { atoi( r->value() ), -1, -1, -1, -1, -1, -1 };
		
		if ( blockNode->first_attribute( "front_r" ) )
		{
			r = blockNode->first_attribute( "front_r" );
			data.front_r = atoi( r->value() );
		}

		if ( blockNode->first_attribute( "back_r" ) )
		{
			r = blockNode->first_attribute( "back_r" );
			data.back_r = atoi( r->value() );
		}

		if ( blockNode->first_attribute( "right_r" ) )
		{
			r = blockNode->first_attribute( "right_r" );
			data.right_r = atoi( r->value() );
		}

		if ( blockNode->first_attribute( "left_r" ) )
		{
			r = blockNode->first_attribute( "left_r" );
			data.left_r = atoi( r->value() );
		}

		if ( blockNode->first_attribute( "top_r" ) )
		{
			r = blockNode->first_attribute( "top_r" );
			data.top_r = atoi( r->value() );
		}

		if ( blockNode->first_attribute( "bottom_r" ) )
		{
			r = blockNode->first_attribute( "bottom_r" );
			data.bottom_r = atoi( r->value() );
		}

		(*blockData)[(world::block::BlockType) std::stoi( block_type->value() )] = data;

		blockNode = blockNode->next_sibling();
	}

	return blockData;
}


// --------------------------------------------------------------------------------------------------------------------
//  Populates chunkprovider, initialises bufferstack pointer, populates blockdata
//
World::World( void ) :
	_chunkProvider(
		new world::chunk::Provider(
			new world::Chunk(
				glm::vec3( 0 ),
				0,
				0,
				0,
				false
			)
		)
	),
	_chunkGenerator( new world::chunk::Generator( (unsigned) std::time( 0 ) ) ),
	_bufferStack( new std::vector<render::Buffer>() ),
	_blockData( loadBlockDataFromXML( "block_def.xml" ) )
{
	for ( int x = 0; x < WLD_START_SIZE; x++ )
		for ( int y = 0; y < WLD_START_SIZE; y++ )
			for ( int z = 0; z < WLD_START_SIZE; z++ )
			{
				_chunkProvider->insertChunk(
					glm::ivec3( x, y, z ),
					new world::Chunk(
						glm::vec3(
							x * WLD_CHUNK_SIZE,
							y * WLD_CHUNK_SIZE,
							z * WLD_CHUNK_SIZE
						),
						_chunkProvider,
						_chunkGenerator,
						_blockData,
						true
					)
				);
			}
}


// --------------------------------------------------------------------------------------------------------------------
//  Clears chunks from chunkprovider
//
World::~World( void )
{
	for ( int x = 0; x < WLD_START_SIZE; x++ )
		for ( int y = 0; y < WLD_START_SIZE; y++ )
			for ( int z = 0; z < WLD_START_SIZE; z++ )
			{
				world::Chunk* chunk = _chunkProvider->getChunk( glm::ivec3( x, y, z ) );
				delete chunk;
			}

	delete _chunkProvider;
	delete _bufferStack;

	_blockData->clear();
	delete _blockData;
}


// --------------------------------------------------------------------------------------------------------------------
//  Updates loaded chunks
//
void World::update( double delta ) const
{
	for ( int x = 0; x < WLD_START_SIZE; x++ )
		for ( int y = 0; y < WLD_START_SIZE; y++ )
			for ( int z = 0; z < WLD_START_SIZE; z++ )
			{
				_chunkProvider->getChunk( glm::ivec3( x, y, z ) )->update( delta );
			}
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns _bufferStack
//
std::vector<render::Buffer>* World::getBuffers( void ) const
{
	_bufferStack->clear();

	for ( int x = 0; x < WLD_START_SIZE; x++ )
		for ( int y = 0; y < WLD_START_SIZE; y++ )
			for ( int z = 0; z < WLD_START_SIZE; z++ )
			{
				_bufferStack->push_back( *_chunkProvider->getChunk( glm::ivec3( x, y, z ) )->getBuffer() );
			}
	
	return _bufferStack;
}
