// "Handler.cpp"
//

#include "Render.h"

using namespace render;


// --------------------------------------------------------------------------------------------------------------------
//  Creates the Shader, VAO and VBO, sets glEnable()s and matrices
//
Handler::Handler( void )
{
	shader = new Shader( "shader.vert", "shader.frag" );

	matrices = new Matrices();
	matrices->setView(
		glm::vec3( 4, 2, 3.5 ),
		glm::vec3( 0, 0, 0 ),
		glm::vec3( 0, 1, 0 )
	);
	matrices->setProjection(
		90.0f,
		static_cast<float> (WIN_W) / WIN_H,
		0.1f,
		100.0f
	);

	glGenVertexArrays( 1, &vertexArrayID );
	glBindVertexArray( vertexArrayID );

	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );

	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );

	buffer = (Buffer*) new utils::Cube();
}


// --------------------------------------------------------------------------------------------------------------------
//  Handles the entire render process for one frame
//
void Handler::render( void ) const
{
	shader->bind();

	matrices->loadIdentity();
	matrices->scale( glm::vec3( 1.0, 4.0, 2.0 ) );
	matrices->computeModelViewProjection();
	shader->setUniforms( matrices->getModelViewProjection() );
	buffer->render( GL_TRIANGLE_STRIP );

	shader->unbind();
}
