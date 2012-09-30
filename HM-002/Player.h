// "Player.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  PLAYER MACROS
// ----------------------------------------------------------------------------

// Mouse sensitivity, in degrees per pixel
#define PLR_LOOK_SPEED 0.15f

// Player x/z move speed, in OGL units per second
#define PLR_WALK_SPEED 2.5f

// Factor to divide _velocity by each update
// TODO: change to subtraction system
#define PLR_WALK_FRICTION 1.5f


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

		void update( double delta );
	};
}
