// "Camera.cpp"
//

#include "Base.h"

#include "Input.h"
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
	_xzLookDegrees( xzLookDegrees ),
	   _lastPolygonMode( 0 ),
	_currentPolygonMode( GL_FILL )
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


// --------------------------------------------------------------------------------------------------------------------
//  Toggles polygon mode indicator, used to set glPolyGonMode( GLint, GLint ) to GL_LINE or GL_FILL
//
void Camera::switchPolygonMode( void )
{
	switch ( _currentPolygonMode )
	{
	case GL_FILL:
		_currentPolygonMode = GL_LINE;
	break;

	case GL_LINE:
		_currentPolygonMode = GL_POINT;
	break;

	case GL_POINT:
		_currentPolygonMode = GL_FILL;
	break;

	default:
		fprintf( stderr, "Error: Invalid polygon mode specified; switching to GL_FILL" );
		_lastPolygonMode = 0;
		_currentPolygonMode = GL_FILL;
	break;
	}
}


// --------------------------------------------------------------------------------------------------------------------
//  Runs basic camera logic
//
void Camera::update( double delta )
{
	_lastPolygonMode = _currentPolygonMode;
	
	if ( keyinput::getKeyDown( 'F', true ) )
		switchPolygonMode();
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns true if a switch of polygon mode is due
//
bool Camera::getPolygonModeSwitch( void ) const
{
	return _currentPolygonMode != _lastPolygonMode;
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns the currently active polygon mode
//
GLint Camera::getPolygonMode( void ) const
{
	return _currentPolygonMode;
}
