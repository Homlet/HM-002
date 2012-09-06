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
	_velocity /= 2.0f;

	// Update position
	{
		using namespace glm;

		if ( keyinput::getKeyDown( 'W' ) )
		{
			_velocity += vec3(
				sin( radians( _xzLookDegrees ) ) * PLR_MOVE_SPEED,
				0.0f,
				cos( radians( _xzLookDegrees ) ) * PLR_MOVE_SPEED
			);
		}

		if ( keyinput::getKeyDown( 'S' ) )
		{
			_velocity += vec3(
				-sin( radians( _xzLookDegrees ) ) * PLR_MOVE_SPEED,
				0.0f,
				-cos( radians( _xzLookDegrees ) ) * PLR_MOVE_SPEED
			);
		}

		if ( keyinput::getKeyDown( 'D' ) )
		{
			_velocity += vec3(
				sin( radians( _xzLookDegrees - 90 ) ) * PLR_MOVE_SPEED,
				0.0f,
				cos( radians( _xzLookDegrees - 90 ) ) * PLR_MOVE_SPEED
			);
		}

		if ( keyinput::getKeyDown( 'A' ) )
		{
			_velocity += vec3(
				sin( radians( _xzLookDegrees + 90 ) ) * PLR_MOVE_SPEED,
				0.0f,
				cos( radians( _xzLookDegrees + 90 ) ) * PLR_MOVE_SPEED
			);
		}

		clamp( _velocity, -PLR_MOVE_SPEED, PLR_MOVE_SPEED );
	}

	_move( _velocity * float( delta ) );

	// Update look direction
	int dx, dy,* dxp = &dx,* dyp = &dy;
	input->getMouseDelta( dxp, dyp );
	_xzLookDegrees -= dx * PLR_LOOK_SPEED;
	 _yLookDegrees -= dy * PLR_LOOK_SPEED;
	_updateLook();
}