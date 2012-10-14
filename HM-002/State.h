// "State.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace update
{
	class State {
	protected:
		std::vector<render::Buffer>* _bufferStack;
		std::vector<Entity>          _entityStack;
		std::shared_ptr<Camera>      _camera;
		World*                       _world;
	public:
		State( void );
		~State( void );

		virtual void update( double delta );
		std::vector<render::Buffer>* getBuffers( void ) const;

		std::shared_ptr<Camera> getCamera( void );
	};
}