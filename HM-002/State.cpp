// "State.cpp"
//

#include "Base.h"

#include "Input.h"
#include "Buffer.h"
#include "Camera.h"
#include "Player.h"
#include "Chunk.h"
#include "Provider.h"
#include "World.h"
#include "Entity.h"

#include "State.h"

using namespace update;


// --------------------------------------------------------------------------------------------------------------------
//  Initializes the world and player
//
State::State( void ) :
	_bufferStack( new std::vector<render::Buffer> ),
	_camera( std::shared_ptr<Camera>( new Player( glm::vec3( 8.0f, 8.0f, 8.0f ), 45.0f, 45.0f ) ) ),
	_world( new World() )
{

}


// --------------------------------------------------------------------------------------------------------------------
//  Cleanup for world and bufferstack
//
State::~State( void )
{
	delete[] _bufferStack;
	delete _bufferStack;
	
	delete _world;
}


// --------------------------------------------------------------------------------------------------------------------
//  Runs logic for member entities, player and world. Takes the frame delta as a double in seconds
//
void State::update( double delta )
{
	_world->update( delta );
	_camera->update( delta );

	if ( keyinput::getKeyDown( GLFW_KEY_F5, true ) )
	{
		delete _world;
		_world = new World();
	}
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns _bufferStack
//
std::vector<render::Buffer>* State::getBuffers( void ) const
{
	_bufferStack->clear();

	std::vector<render::Buffer>* tempStack = _world->getBuffers();
	_bufferStack->insert( _bufferStack->begin(), tempStack->begin(), tempStack->end() );
	
	return _bufferStack;
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets the look direction based on _xzLookDegrees and _yLookDegrees
//
std::shared_ptr<Camera> State::getCamera( void )
{
	return _camera;
}
