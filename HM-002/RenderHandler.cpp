// "Renderer.cpp"
//

#include "RenderHandler.h"

using namespace renderhandler;


// Renderer MEMBERS ===================================================================================================

// --------------------------------------------------------------------------------------------------------------------
//  Creates the Shader, VAO and VBO, sets glEnable()s and matrices
//
Renderer::Renderer( void )
{
	shader = new Shader( "shader.vert", "shader.frag" );

	matrices = new Matrices();
	matrices->setView(
		glm::vec3( 4, 3, 3 ),
		glm::vec3( 0, 0, 0 ),
		glm::vec3( 0, 1, 0 )
	);
	matrices->setProjection(
		75.0f,
		static_cast<float> (WIN_W) / WIN_H,
		0.1f,
		100.0f
	);

	glGenVertexArrays( 1, &vertexArrayID );
	glBindVertexArray( vertexArrayID );

	buffer = new Buffer();
	vertex data[3] = {
		{-1.0f, -1.0f, 0.0f,    100, 100, 100, 255},
		{ 1.0f, -1.0f, 0.0f,     50,  50,  50, 255},
		{ 0.0f,  1.0f, 0.0f,    200, 200, 200, 255}
	};
	unsigned int indices[3] = {
		0u,
		1u,
		2u
	};
	buffer->setData( data, sizeof ( data ) / sizeof ( vertex ) );
	buffer->setIndices( indices, sizeof ( indices ) / sizeof ( unsigned int ) );
}


// --------------------------------------------------------------------------------------------------------------------
//  Handles the entire render process for one frame
//
void Renderer::render( void ) const
{
	shader->bind();

	matrices->computeModelViewProjection();
	shader->setUniforms( matrices->getModelViewProjection() );

	buffer->render();

	shader->unbind();
}


// Shader MEMBERS =====================================================================================================

// --------------------------------------------------------------------------------------------------------------------
//  Loads, compiles, check and links the shader files. Creates program
//
Shader::Shader( const char* vertFilePath, const char* fragFilePath ) :
	programID( glCreateProgram() )
{
	GLuint vertID = glCreateShader( GL_VERTEX_SHADER );
	GLuint fragID = glCreateShader( GL_FRAGMENT_SHADER );

	// Write the vertex shader to a string
	std::string vertCode;
	std::ifstream vertStream( vertFilePath, std::ios::in );

	if ( vertStream.is_open() )
	{
		std::string line = "";

		while ( getline( vertStream, line ) )
			vertCode += "\n" + line;

		vertStream.close();
	}

	// Write the fragment shader to a string
	std::string fragCode;
	std::ifstream fragStream( fragFilePath, std::ios::in );

	if ( fragStream.is_open() )
	{
		std::string line = "";

		while ( getline( fragStream, line ) )
			fragCode += "\n" + line;

		fragStream.close();
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	// Compile vertex shader
	fprintf( stdout, "Compiling shader: %s\n", vertFilePath );
	const char* vertSourcePointer = vertCode.c_str();
	glShaderSource( vertID, 1, &vertSourcePointer, 0 );
	glCompileShader( vertID );

	// Check vertex shader
	glGetShaderiv( vertID, GL_COMPILE_STATUS, &result );
	glGetShaderiv( vertID, GL_INFO_LOG_LENGTH, &infoLogLength );
	std::vector<char> vertErrorMessage( infoLogLength );
	glGetShaderInfoLog( vertID, infoLogLength, 0, &vertErrorMessage[0] );
	fprintf( stdout, "%s\n", &vertErrorMessage[0] );

	// Compile frag shader
	fprintf( stdout, "Compiling shader: %s\n", fragFilePath );
	const char* fragSourcePointer = fragCode.c_str();
	glShaderSource( fragID, 1, &fragSourcePointer, 0 );
	glCompileShader( fragID );

	// Check vertex shader
	glGetShaderiv( fragID, GL_COMPILE_STATUS, &result );
	glGetShaderiv( fragID, GL_INFO_LOG_LENGTH, &infoLogLength );
	std::vector<char> fragErrorMessage( infoLogLength );
	glGetShaderInfoLog( fragID, infoLogLength, 0, &fragErrorMessage[0] );
	fprintf( stdout, "%s\n", &fragErrorMessage[0] );

	// Link program
	fprintf( stdout, "Linking program\n" );
	glAttachShader( programID, vertID );
	glAttachShader( programID, fragID );
	glLinkProgram( programID );

	// Check the program
	glGetProgramiv( programID, GL_LINK_STATUS, &result );
	glGetProgramiv( programID, GL_INFO_LOG_LENGTH, &infoLogLength );
	std::vector<char> programErrorMessage( glm::max( infoLogLength, int( 1 ) ) );
	glGetProgramInfoLog( programID, infoLogLength, 0, &programErrorMessage[0] );
	fprintf( stdout, "%s\n", &programErrorMessage[0] );
	
	glDeleteShader( vertID );
	glDeleteShader( fragID );

	// Setup uniforms
	uniformLocationMatrix = glGetUniformLocation( programID, "MVP" );
}


// --------------------------------------------------------------------------------------------------------------------
//  Uses the shader program for rendering
//
void Shader::bind( void ) const
{
	glUseProgram( programID );
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets GLSL uniforms: mat4 MVP
//
void Shader::setUniforms( glm::mat4 MVP ) const
{
	glUniformMatrix4fv( uniformLocationMatrix, 1, GL_FALSE, &MVP[0][0] );
}


// --------------------------------------------------------------------------------------------------------------------
//  Stops using the shader program for rendering
//
void Shader::unbind( void ) const
{
	glUseProgram( 0 );
}


// Buffer MEMBERS =====================================================================================================

// --------------------------------------------------------------------------------------------------------------------
//  Creates empty vertex buffer
//
Buffer::Buffer( void )
{
	glGenBuffers( 1, &dataID );
	glGenBuffers( 1, &indicesID );
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets buffer data
//
void Buffer::setData( vertex* data, int count ) const
{
	bind();
	glBufferData(
		GL_ARRAY_BUFFER,
		count * sizeof ( vertex ),
		data,
		GL_STATIC_DRAW
	);
	unbind();
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets buffer indices
//
void Buffer::setIndices( unsigned int* indices, int count )
{
	bind();
	this->count = count;
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		count * sizeof ( unsigned int ),
		indices,
		GL_STATIC_DRAW
	);
	unbind();
}


// --------------------------------------------------------------------------------------------------------------------
//  Bind the VBO
//
void Buffer::bind( void ) const
{
	glBindBuffer( GL_ARRAY_BUFFER, dataID );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indicesID );
}


// --------------------------------------------------------------------------------------------------------------------
//  Unbind the VBO
//
void Buffer::unbind( void ) const
{
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}


// --------------------------------------------------------------------------------------------------------------------
//  Renders the buffer
//
void Buffer::render( void ) const
{
	bind();
	glEnableVertexAttribArray( attribLocationVertex );
	glEnableVertexAttribArray( attribLocationColor );
	glVertexAttribPointer(
		attribLocationVertex,
		3,
		GL_FLOAT,
		GL_FALSE,
		16,
		(void*) 0
	);
	glVertexAttribPointer(
		attribLocationColor,
		4,
		GL_UNSIGNED_BYTE,
		GL_FALSE,
		16,
		(void*) 12
	);

	glDrawElements(
		GL_TRIANGLES,
		count,
		GL_UNSIGNED_INT,
		(void*) 0
	);

	glDisableVertexAttribArray( attribLocationVertex );
	glDisableVertexAttribArray( attribLocationColor );
	unbind();
}


// Matrices MEMBERS ===================================================================================================

// --------------------------------------------------------------------------------------------------------------------
//  Loads all matrices to identity
//
Matrices::Matrices() :
	              model( glm::mat4( 1.0 ) ),
	               view( glm::mat4( 1.0 ) ),
	         projection( glm::mat4( 1.0 ) ),
	modelViewProjection( glm::mat4( 1.0 ) )
{

}


// --------------------------------------------------------------------------------------------------------------------
//  Loads the model matrix to identity
//
void Matrices::loadIdentity( void )
{
	model = glm::mat4( 1.0 );
}


// --------------------------------------------------------------------------------------------------------------------
//  Translates the model matrix
//
void Matrices::translate( glm::vec3 translation )
{
	model *= glm::translate( translation );
}


// --------------------------------------------------------------------------------------------------------------------
//  Rotates the model matrix
//
void Matrices::rotate( glm::vec3 axis, float angle )
{
	model *= glm::rotate( angle, axis );
}


// --------------------------------------------------------------------------------------------------------------------
//  Scales the model matrix
//
void Matrices::scale( glm::vec3 scale )
{
	model *= glm::scale( scale );
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets the view matrix using glm::lookAt. Use to move the camera
//
void Matrices::setView( glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 upVector)
{
	view = glm::lookAt(
		cameraPosition,
		cameraTarget,
		upVector
	);
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets the projection matrix using glm::perspective. Use only in initialisation or to change the FoV
//
void Matrices::setProjection( float fov, float aspectRatio, float nearClip, float farClip )
{
	projection = glm::perspective(
		fov,
		aspectRatio,
		nearClip,
		farClip
	);
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets modelViewProjection to the product of all three current matrices
//
void Matrices::computeModelViewProjection( void )
{
	modelViewProjection = projection * view * model;
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns modelViewProjection
//
glm::mat4 Matrices::getModelViewProjection( void )
{
	return modelViewProjection;
}
