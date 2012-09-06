// "Player.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  PLAYER MACROS
// ----------------------------------------------------------------------------

// Mouse sensitivity, in degrees per pixel
#define PLR_LOOK_SPEED 0.15f

// Player x/z move speed, in OGL units per second
#define PLR_MOVE_SPEED 2.5f


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace update
{
	class Player : public Camera {
	private:
		glm::vec3 _velocity;
	public:
		Player( glm::vec3 pos, float yLookDegrees, float xzLookDegrees );

		void update( double delta, Input* input );
	};
}
