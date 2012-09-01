// "Renderer.cpp"
//

#include "RenderHandler.h"

using namespace renderhandler;


// --------------------------------------------------------------------------------------------------------------------
//  Creates the Shader, VAO and VBO, sets glEnable()s and matrices
//
Renderer::Renderer( void )
{
	shader = new Shader( "shader.vert", "shader.frag" );

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
}


// --------------------------------------------------------------------------------------------------------------------
//  Handles the entire render process for one frame
//
void Renderer::render( void ) const
{
	shader->bind();

	glEnableVertexAttribArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBufferID );
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*) 0
	);

	glDrawArrays( GL_TRIANGLES, 0, 3 );

	glDisableVertexAttribArray( 0 );

	shader->unbind();
}


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
	printf( "Compiling shader: %s\n", vertFilePath );
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
	printf( "Compiling shader: %s\n", fragFilePath );
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
}


// --------------------------------------------------------------------------------------------------------------------
//  Uses the shader program for rendering
//
void Shader::bind( void ) const
{
	glUseProgram( programID );
}


// --------------------------------------------------------------------------------------------------------------------
//  Stops using the shader program for rendering
//
void Shader::unbind( void ) const
{
	glUseProgram( 0 );
}