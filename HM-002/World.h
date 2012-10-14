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
		world::chunk::Provider*  _chunkProvider;
		world::chunk::Generator* _chunkGenerator;

		std::vector<render::Buffer>* _bufferStack;

		std::hash_map<
			world::block::BlockType,
			world::block_data
		>* _blockData;
	public:
		static std::hash_map<
			world::block::BlockType,
			world::block_data
		>* loadBlockDataFromXML( char* path );

		World( void );
		~World( void );

		void update( double delta ) const;
		std::vector<render::Buffer>* getBuffers( void ) const;
	};
}
