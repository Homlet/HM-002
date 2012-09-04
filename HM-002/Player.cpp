// "Player.cpp"
//

#include "Base.h"
#include "Player.h"

using namespace update;

void Player::_updateLook()
{
	using namespace glm;

	vec2  y( sin( radians(  _yLookDegrees ) ), cos( radians(  _yLookDegrees ) ) );
	vec2 xz( sin( radians( _xzLookDegrees ) ), cos( radians( _xzLookDegrees ) ) );
	
	_look = _position + glm::vec3( xz.x * y.y, y.x, xz.y * y.y );
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets the position and the look direction
//
Player::Player( glm::vec3 pos, float yLookDegrees, float xzLookDegrees ) :
	_position( _position ),
	_yLookDegrees( yLookDegrees ),
	_xzLookDegrees( xzLookDegrees )
{
	_updateLook();
}


// --------------------------------------------------------------------------------------------------------------------
//  Runs player logic (eg. moves player, resets look direction, collides)
//
void Player::update( double delta, Input* input )
{
	std::cout << "Updating player" << std::endl;
}