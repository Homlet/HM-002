// "Renderer.cpp"
//

#include "RenderHandler.h"



int renderhandler::Renderer::initializeRenderer( void )
{
	glGenVertexArrays( 1, &vertexArrayID );
	glBindVertexArray( vertexArrayID );

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f,  0.0f,
		 1.0f, -1.0f,  0.0f,
		 0.0f,  1.0f,  0.0f
	};

	glGenBuffers( 1, &vertexBufferID );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferID );
	glBufferData( GL_ARRAY_BUFFER, sizeof ( g_vertex_buffer_data ), g_vertex_buffer_data, GL_STATIC_DRAW );

	return 0;
}



int renderhandler::Renderer::render( void )
{
	glEnableVertexAttribArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferID );
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void *) 0
	);

	glDrawArrays( GL_TRIANGLES, 0, 3 );

	glDisableVertexAttribArray( 0 );

	return 0;
}