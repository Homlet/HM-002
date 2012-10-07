// "World.h"
//

#pragma once

#define _DEFINE_DEPRECATED_HASH_CLASSES 0
#include <hash_map>

#include "rapidxml.hpp"


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace update
{
	class World {
	private:
		world::ChunkProvider* _chunkProvider;

		std::vector<render::Buffer>* _bufferStack;

		std::hash_map<
			world::block::BlockType,
			world::block::data
		>* _blockData;
	public:
		static std::hash_map<
			world::block::BlockType,
			world::block::data
		>* loadBlockDataFromXML( char* path );

		World( void );
		~World( void );

		void update( double delta ) const;
		std::vector<render::Buffer>* getBuffers( void ) const;
	};
}
