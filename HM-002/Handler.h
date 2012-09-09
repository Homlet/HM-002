// "Handler.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace render
{
	class Handler {
	private:
		GLuint _vertexArrayID;

		Shader   _shader;
		Matrices _matrices;
	public:
		Handler( void );

		void render(
			glm::vec3 position,
			glm::vec3 look,
			std::vector<render::Buffer>* buffers
		);
	};
}