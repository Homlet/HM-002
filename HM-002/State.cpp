// "State.cpp"
//

#include "Base.h"
#include "Input.h"
#include "Buffer.h"
#include "Chunk.h"
#include "Camera.h"
#include "Player.h"
#include "Entity.h"
#include "State.h"

using namespace update;


// --------------------------------------------------------------------------------------------------------------------
//  Initializes the world and player
//
State::State( void ) :
	_bufferStack( new std::vector<render::Buffer> ),
	_camera( std::shared_ptr<Camera>( new Player( glm::vec3( 0.0f, 0.0f, 0.0f ), 45.0f, 45.0f ) ) )
{

}


// --------------------------------------------------------------------------------------------------------------------
//  Runs logic for member entities, player and world. Takes the frame delta as a double in seconds
//
void State::update( double delta, Input* input )
{
	_chunk.update( delta );
	_camera->update( delta, input );
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns _bufferStack
//
std::vector<render::Buffer>* State::getBuffers( void ) const
{
	_bufferStack->clear();
	_bufferStack->push_back( *_chunk.getBuffer() );
	
	return _bufferStack;
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets the look direction based on _xzLookDegrees and _yLookDegrees
//
std::shared_ptr<Camera> State::getCamera( void )
{
	return _camera;
}