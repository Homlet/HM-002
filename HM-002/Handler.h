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
		Buffer   _buffer;
		Matrices _matrices;
	public:
		Handler( void );

		void render( glm::vec3 position, glm::vec3 look );
	};
}