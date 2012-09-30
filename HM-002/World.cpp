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
//  Populates chunkprovider, initialises bufferstack pointer
//
World::World( void ) :
	_chunkProvider(
		new world::ChunkProvider(
			new world::Chunk(
				glm::vec3( 0 ),
				0,
				false
			)
		)
	),
	_bufferStack( new std::vector<render::Buffer>() )
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
