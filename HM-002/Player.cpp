// "Player.cpp"
//

#include "Base.h"
#include "Input.h"
#include "Camera.h"
#include "Player.h"

using namespace update;


// --------------------------------------------------------------------------------------------------------------------
//  Calls parent constructor
//
Player::Player( glm::vec3 pos, float yLookDegrees, float xzLookDegrees ) :
	Camera( pos, yLookDegrees, xzLookDegrees ),
	_velocity()
{

}


// --------------------------------------------------------------------------------------------------------------------
//  Runs player logic (eg. moves player, resets look direction, collides)
//
void Player::update( double delta, Input* input )
{
	_velocity /= PLR_WALK_FRICTION;

	// Update position
	{
		using namespace glm;

		if ( keyinput::getKeyDown( 'W' ) )
		{
			_velocity += vec3(
				sin( radians( _xzLookDegrees ) ) * cos( radians(  _yLookDegrees ) ) * PLR_WALK_SPEED,
				sin( radians(  _yLookDegrees ) ) * PLR_WALK_SPEED,
				cos( radians( _xzLookDegrees ) ) * cos( radians(  _yLookDegrees ) ) * PLR_WALK_SPEED
			);
		}

		if ( keyinput::getKeyDown( 'S' ) )
		{
			_velocity += vec3(
				-sin( radians( _xzLookDegrees ) ) * cos( radians(  _yLookDegrees ) ) * PLR_WALK_SPEED,
				-sin( radians(  _yLookDegrees ) ) * PLR_WALK_SPEED,
				-cos( radians( _xzLookDegrees ) ) * cos( radians(  _yLookDegrees ) ) * PLR_WALK_SPEED
			);
		}

		if ( keyinput::getKeyDown( 'D' ) )
		{
			_velocity += vec3(
				sin( radians( _xzLookDegrees - 90 ) ) * PLR_WALK_SPEED,
				0.0f,
				cos( radians( _xzLookDegrees - 90 ) ) * PLR_WALK_SPEED
			);
		}

		if ( keyinput::getKeyDown( 'A' ) )
		{
			_velocity += vec3(
				sin( radians( _xzLookDegrees + 90 ) ) * PLR_WALK_SPEED,
				0.0f,
				cos( radians( _xzLookDegrees + 90 ) ) * PLR_WALK_SPEED
			);
		}

		if ( keyinput::getKeyDown( GLFW_KEY_SPACE ) )
		{
			_velocity += vec3(
				0.0f,
				PLR_WALK_SPEED,
				0.0f
			);
		}
		
		if ( keyinput::getKeyDown( GLFW_KEY_LSHIFT ) )
		{
			_velocity += vec3(
				0.0f,
				-PLR_WALK_SPEED,
				0.0f
			);
		}

		clamp( _velocity, -PLR_WALK_SPEED, PLR_WALK_SPEED );
	}

	_move( _velocity * float( delta ) );

	// Update look direction
	int dx, dy,* dxp = &dx,* dyp = &dy;
	input->getMouseDelta( dxp, dyp );
	_xzLookDegrees -= dx * PLR_LOOK_SPEED;
	 _yLookDegrees -= dy * PLR_LOOK_SPEED;
	_updateLook();
}