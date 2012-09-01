// "Renderer.h"
//

#pragma once

#include <vector>

#include "Base.h"

// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace renderhandler
{
	class Shader {
	private:
		GLuint programID;
	public:
		Shader( const char* vertFilePath, const char* fragFilePath );
		void bind( void ) const;
		void unbind( void ) const;
	};

	
	class Renderer {
	private:
		GLuint vertexArrayID;
		GLuint vertexBufferID;

		renderhandler::Shader* shader;
	public:
		Renderer( void );
		void render( void ) const;
	};


	typedef struct {
		float x, y, z,
		      r, b, g,
		      s, t;
	} Vertex;


	typedef struct {
		unsigned int a, b, c;
	} Triangle;


	typedef struct {
		renderhandler::Vertex* vertices;
		renderhandler::Triangle* indices;
	} Buffer;
}
