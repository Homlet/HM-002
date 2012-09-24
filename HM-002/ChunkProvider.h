// "ChunkProvider.h"
//

#pragma once

#define _DEFINE_DEPRECATED_HASH_CLASSES 0
#include <hash_map>


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------


namespace update
{
	namespace world
	{
		class ChunkProvider {
		private:
			std::hash_map<
				glm::ivec3,
				Chunk*,
				HashConfig
			> _chunkMap;

			Chunk* _nullChunk;
		public:
			ChunkProvider( Chunk* nullChunk );
			~ChunkProvider( void );

			void insertChunk( glm::ivec3 chunkPos, Chunk* chunk );

			Chunk* getChunk( glm::ivec3 chunkPos ) const;
		};
	}
}