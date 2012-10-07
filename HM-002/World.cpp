// "World.cpp"
//

#include "WorldMacros.h"

#include "Base.h"

#include "Buffer.h"
#include "ChunkProvider.h"
#include "Chunk.h"

#include "World.h"

using namespace update;


// --------------------------------------------------------------------------------------------------------------------
//  Populates hash_map with block data from xml file specified
//
std::hash_map<world::block::BlockType, world::block::data>* World::loadBlockDataFromXML( char* path )
{
	std::hash_map<
		world::block::BlockType,
		world::block::data
	>* blockData = new std::hash_map<
		world::block::BlockType,
		world::block::data
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

		world::block::data data = { atoi( r->value() ) };
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
		new world::ChunkProvider(
			new world::Chunk(
				glm::vec3( 0 ),
				0,
				0,
				false
			)
		)
	),
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
						_blockData,
						true
					)
				);
			}
}


// --------------------------------------------------------------------------------------------------------------------
//  Clears hashmap
//
World::~World( void )
{
	delete _chunkProvider;
	delete _bufferStack;
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
