// "Renderer.h"
//

#pragma once

#include "Base.h"
#include <vector>

// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace renderhandler
{
	class Renderer {
	private:
		GLuint vertexArrayID;
		GLuint vertexBufferID;
		
	public:
		int initializeRenderer( void );
		int render( void );
	};

	class Shader {
	private:

	public:
		Shader( void );
	};
}