// "State.cpp"
//

#include "Base.h"
#include "Input.h"
#include "Buffer.h"
#include "Player.h"
#include "Entity.h"
#include "State.h"

using namespace update;


// --------------------------------------------------------------------------------------------------------------------
//  Initializes the world and player
//
State::State() :
	_player( glm::vec3( 4.0, 3.0, 4.0 ), 45.0f, 45.0f )
{

}


// --------------------------------------------------------------------------------------------------------------------
//  Runs logic for member entities, player and world. Takes the frame delta as a double in seconds
//
void State::update( double delta, Input* input )
{
	_player.update( delta, input );
}
