// "State.cpp"
//

#include "Base.h"
#include "Input.h"
#include "Buffer.h"
#include "Camera.h"
#include "Player.h"
#include "Entity.h"
#include "State.h"

using namespace update;


// --------------------------------------------------------------------------------------------------------------------
//  Initializes the world and player
//
State::State( void ) :
_camera( std::shared_ptr<Camera>( new Player( glm::vec3( 5.0f, 0.0f, 0.0f ), 45.0f, 45.0f ) ) )
{

}


// --------------------------------------------------------------------------------------------------------------------
//  Runs logic for member entities, player and world. Takes the frame delta as a double in seconds
//
void State::update( double delta, Input* input )
{
	_camera->update( delta, input );
}



// --------------------------------------------------------------------------------------------------------------------
//  Sets the look direction based on _xzLookDegrees and _yLookDegrees
//
std::shared_ptr<Camera> State::getCamera( void )
{
	return _camera;
}