// "Handler.cpp"
//

#include "WindowMacros.h"

#include "Base.h"

#include "Buffer.h"
#include "Camera.h"
#include "Shader.h"
#include "Matrices.h"

#include "Handler.h"

using namespace render;


// --------------------------------------------------------------------------------------------------------------------
//  Creates the Shader, VAO and VBO, sets glEnable()s and matrices
//
Handler::Handler( void ) :
	_shader( "shader.vert", "shader.frag" )
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

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	glEnable( GL_VERTEX_PROGRAM_POINT_SIZE );

	glClearColor(
		135 / 255.0f,
		206 / 255.0f,
		235 / 255.0f,
		255 / 255.0f
	);
}


// --------------------------------------------------------------------------------------------------------------------
//  Handles the entire render process for one frame
//
void Handler::render( std::shared_ptr<update::Camera> camera, std::vector<render::Buffer>* buffers )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if ( camera->getPolygonModeSwitch() )
	{
		glPolygonMode( GL_FRONT_AND_BACK, camera->getPolygonMode() );

		if ( camera->getPolygonMode() == GL_FILL )
			glEnable( GL_CULL_FACE );
		else
			glDisable( GL_CULL_FACE );
	}

	_matrices.setView(
		camera->getPosition(),
		camera->getLook(),
		glm::vec3( 0, 1, 0 )
	);

	_shader.bind();

	for ( int i = 0; i < (int) buffers->size(); i++ )
	{
		Buffer* b = &buffers->at( i );
		_matrices.loadIdentity();
		_matrices.translate( b->getPosition() );
		_matrices.computeModelView();
		_shader.setUniforms(
			_matrices.getModelView(),
			_matrices.getProjection(),
			glm::vec4( 113, 197, 231, 255 )
		);
		b->render( GL_TRIANGLES );
	}

	_shader.unbind();
}
