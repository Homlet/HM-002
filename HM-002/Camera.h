// "Camera.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace update
{
	class Camera {
	private:
		glm::vec3 _position;
		glm::vec3 _look;

		GLint    _lastPolygonMode;
		GLint _currentPolygonMode;
	protected:
		void _move( glm::vec3 offset );

		float _yLookDegrees;
		float _xzLookDegrees;
		void  _updateLook( void );
	public:
		Camera( glm::vec3 pos, float yLookDegrees, float xzLookDegrees );

		virtual void update( double delta );
		
		glm::vec3 getPosition( void ) const;
		glm::vec3 getLook( void ) const;
		
		void switchPolygonMode( void );
		bool    getPolygonModeSwitch( void ) const;
		GLint   getPolygonMode( void ) const;
	};
}
