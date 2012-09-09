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

			Block*** _blocks;
			
			render::Buffer* _buffer;
			bool _hasChanged;
			void _rebuild( void );
		public:
			Chunk( void );
			~Chunk( void );

			void update( double delta );
			render::Buffer* getBuffer( void ) const;
		};
	}
}