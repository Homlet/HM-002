// "Player.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace update
{
	class Player {
	private:
		glm::vec3 _position;
		glm::vec3 _look;

		glm::vec3 _velocity;
		
		float _yLookDegrees;
		float _xzLookDegrees;
		void  _updateLook();
	public:
		Player( glm::vec3 pos, float yLookDegrees, float xzLookDegrees );

		void update( double delta, Input* input );
	};
}
