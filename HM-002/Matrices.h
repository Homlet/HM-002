// "Matrices.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace render
{
	class Matrices {
	private:
		glm::mat4 _model;
		glm::mat4 _view;
		glm::mat4 _projection;
		glm::mat4 _modelViewProjection;
	public:
		Matrices( void );

		void loadIdentity( void );
		void translate( glm::vec3 translation );
		void    rotate( glm::vec3 axis, float angle );
		void     scale( glm::vec3 scale );

		void setView(
			glm::vec3 cameraPosition,
			glm::vec3 cameraTarget,
			glm::vec3 upVector
		);
		void setProjection(
			float fov,
			float aspectRatio,
			float nearClip,
			float farClip
		);

		void computeModelViewProjection( void );
		glm::mat4 getModelViewProjection( void ) const;
	};
}
