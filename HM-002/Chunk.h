// "Chunk.h"
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
		class Chunk {
		private:
			void _createBlockBuffer(
				float x,
				float y,
				float z,
				bool front,
				bool back,
				bool right,
				bool left,
				bool top,
				bool bottom,
				block::BlockType type,
				std::vector<render::vertex>* data,
				std::vector<GLushort>* indices
			);

			const ChunkProvider* _chunkProvider;

			Block*** _blocks;
			Block* _nullBlock;
			
			std::hash_map<
				block::BlockType,
				block::data
			>* _blockData;
			
			render::Buffer* _buffer;
			bool _hasChanged;
			void _rebuild( void );

			glm::vec3 _position;

			bool _active;
		public:
			Chunk(
				glm::vec3 pos,
				ChunkProvider* chunkProvider,
				std::hash_map<
					block::BlockType,
					block::data
				>* blockData,
				bool active
			);
			~Chunk( void );

			void update( double delta );
			render::Buffer* getBuffer( void ) const;

			void setActive( bool active );
			bool  isActive( void ) const;
			
			Block* getBlock( glm::ivec3 pos ) const;
			Block* getBlockAbsolute( glm::ivec3 absPos ) const;
		};
	}
}