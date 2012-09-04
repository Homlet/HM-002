// "State.h"
//

#pragma once

#include <vector>


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace update
{
	class State {
	private:
		std::vector<render::Buffer> _bufferStack;
		std::vector<Entity>         _entityStack;
		Player                      _player;
	//	World                       _world;
	public:
		State();

		void update( double delta, Input* input );
	};
}