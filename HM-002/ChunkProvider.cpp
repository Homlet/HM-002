// "ChunkProvider.cpp"
//

#include "WorldMacros.h"

#include "Base.h"

#include "ChunkProvider.h"

using namespace update::world;


// --------------------------------------------------------------------------------------------------------------------
//  Sets _nullChunk
//
ChunkProvider::ChunkProvider( Chunk* nullChunk ) :
	_nullChunk( nullChunk )
{

}


// --------------------------------------------------------------------------------------------------------------------
//  Deletes all chunks in hashmap, deletes _nullChunk
//
ChunkProvider::~ChunkProvider( void )
{
	_chunkMap.clear();
}


// --------------------------------------------------------------------------------------------------------------------
//  Adds chunk pointer to the specified position in the hashmap
//
void ChunkProvider::insertChunk( glm::ivec3 chunkPos, Chunk* chunk )
{
	_chunkMap[chunkPos] = chunk;
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns pointer to the chunk at the specified position
//  Returns _nullChunk if key is not registered
//
Chunk* ChunkProvider::getChunk( glm::ivec3 chunkPos ) const
{
	return ( _chunkMap.find( chunkPos ) == _chunkMap.end() ) ? _nullChunk : _chunkMap.at( chunkPos );
}
