// "Camera.cpp"
//

#include "Base.h"
#include "Camera.h"
#include "Player.h"

using namespace update;

// --------------------------------------------------------------------------------------------------------------------
//  Adds the offset to the _position vector
//
void Camera::_move( glm::vec3 offset )
{
	_position += offset;
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets the look direction based on _xzLookDegrees and _yLookDegrees
//
void Camera::_updateLook( void )
{
	using namespace glm;

	if ( _yLookDegrees > 89.9f )
		_yLookDegrees = 89.9f;
	else if ( _yLookDegrees < -89.9f )
		_yLookDegrees = -89.9f;

	vec2  y( sin( radians(  _yLookDegrees ) ), cos( radians(  _yLookDegrees ) ) );
	vec2 xz( sin( radians( _xzLookDegrees ) ), cos( radians( _xzLookDegrees ) ) );
	
	_look = _position + glm::vec3( xz[0] * y[1], y[0], xz[1] * y[1] );
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets position and look vector
//
Camera::Camera( glm::vec3 pos, float yLookDegrees, float xzLookDegrees ) :
	_position( pos ),
	 _yLookDegrees( yLookDegrees ),
	_xzLookDegrees( xzLookDegrees )
{
	_updateLook();
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns the camera position
//
glm::vec3 Camera::getPosition( void ) const
{
	return _position;
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns the camera look vector
//
glm::vec3 Camera::getLook( void ) const
{
	return _look;
}
