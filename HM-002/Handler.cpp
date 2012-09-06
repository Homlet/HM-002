// "Handler.cpp"
//

#include "Base.h"
#include "Buffer.h"
#include "Cube.h"
#include "Shader.h"
#include "Matrices.h"
#include "Handler.h"

using namespace render;


// --------------------------------------------------------------------------------------------------------------------
//  Creates the Shader, VAO and VBO, sets glEnable()s and matrices
//
Handler::Handler( void ) :
	_shader( "shader.vert", "shader.frag" ),
	_buffer( buffer::Cube() )
{
	_matrices.setView(
		glm::vec3( 1, 1, 1 ),
		glm::vec3( 0, 0, 0 ),
		glm::vec3( 0, 1, 0 )
	);
	_matrices.setProjection(
		75.0f,
		static_cast<float> (WIN_W) / WIN_H,
		0.1f,
		100.0f
	);

	glGenVertexArrays( 1, &_vertexArrayID );
	glBindVertexArray( _vertexArrayID );

	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
}


// --------------------------------------------------------------------------------------------------------------------
//  Handles the entire render process for one frame
//
void Handler::render( glm::vec3 position, glm::vec3 look )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	_matrices.setView(
		position,
		look,
		glm::vec3( 0, 1, 0 )
	);

	_shader.bind();

	_matrices.loadIdentity();
	_matrices.computeModelViewProjection();
	_shader.setUniforms( _matrices.getModelViewProjection() );
	_buffer.render( GL_TRIANGLE_STRIP );

	_shader.unbind();
}
