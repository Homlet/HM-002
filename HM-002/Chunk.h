// "Chunk.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace update
{
	namespace world
	{
		class Chunk {
		private:
			static void _createBlockBuffer(
				int x,
				int y,
				int z,
				bool front,
				bool back,
				bool right,
				bool left,
				bool top,
				bool bottom,
				BlockType type,
				std::vector<render::vertex>* data,
				std::vector<GLushort>* indices
			);

			const ChunkProvider* _chunkProvider;

			Block*** _blocks;
			Block* _nullBlock;
			
			render::Buffer* _buffer;
			bool _hasChanged;
			void _rebuild( void );

			glm::vec3 _position;

			bool _active;
		public:
			Chunk( glm::vec3 pos, ChunkProvider* chunkProvider, bool active );
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