// "Shader.cpp"
//

#include "Base.h"

#include "Shader.h"

using namespace render;


// --------------------------------------------------------------------------------------------------------------------
//  Loads, compiles, check and links the shader files. Creates program
//
Shader::Shader( const char* vertFilePath, const char* fragFilePath ) :
	_programID( glCreateProgram() )
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
	glAttachShader( _programID, vertID );
	glAttachShader( _programID, fragID );
	glLinkProgram( _programID );

	// Check the program
	glGetProgramiv( _programID, GL_LINK_STATUS, &result );
	glGetProgramiv( _programID, GL_INFO_LOG_LENGTH, &infoLogLength );
	std::vector<char> programErrorMessage( glm::max( infoLogLength, int( 1 ) ) );
	glGetProgramInfoLog( _programID, infoLogLength, 0, &programErrorMessage[0] );
	fprintf( stdout, "%s\n", &programErrorMessage[0] );
	
	glDeleteShader( vertID );
	glDeleteShader( fragID );

	// Setup uniforms
	_uniformLocationMat4MV            = glGetUniformLocation( _programID, "MV" );
	_uniformLocationMat4P             = glGetUniformLocation( _programID, "P" );
	_uniformLocationVec4Fog_Color     = glGetUniformLocation( _programID, "Fog_Color" );

	_uniformLocation1iTexture_Sampler = glGetUniformLocation( _programID, "Texture_Sampler" );

	// Setup texture sampler
	bind();

	glUniform1i( _uniformLocation1iTexture_Sampler, 2 );
	glGenSamplers( 1, &_samplerLocationTexture_Sampler );
	glBindSampler( 2, _samplerLocationTexture_Sampler );

	unbind();
}


// --------------------------------------------------------------------------------------------------------------------
//  Uses the shader program for rendering
//
void Shader::bind( void ) const
{
	glUseProgram( _programID );
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets GLSL uniforms: mat4 MVP
//
void Shader::setUniforms( glm::mat4 MV, glm::mat4 P, glm::vec3 Fog_Color) const
{
	glUniformMatrix4fv( _uniformLocationMat4MV, 1, GL_FALSE, &MV[0][0] );
	glUniformMatrix4fv( _uniformLocationMat4P,  1, GL_FALSE,  &P[0][0] );
	glUniform3fv( _uniformLocationVec4Fog_Color, 1, &Fog_Color[0] );
}


// --------------------------------------------------------------------------------------------------------------------
//  Stops using the shader program for rendering
//
void Shader::unbind( void ) const
{
	glUseProgram( 0 );
}
