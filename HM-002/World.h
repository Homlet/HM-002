// "World.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace update
{
	class World {
	private:
		world::ChunkProvider* _chunkProvider;

		std::vector<render::Buffer>* _bufferStack;
	public:
		World( void );
		~World( void );

		void update( double delta ) const;
		std::vector<render::Buffer>* getBuffers( void ) const;
	};
}
