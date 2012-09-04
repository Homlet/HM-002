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

		float _frame;

		Shader   _shader;
		Buffer   _buffer;
		Matrices _matrices;
	public:
		Handler( void );

		void render( void );
	};
}