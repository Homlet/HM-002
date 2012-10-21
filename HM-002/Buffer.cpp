// "Buffer.cpp"
//

#include "Base.h"

#include "Buffer.h"

using namespace render;


// --------------------------------------------------------------------------------------------------------------------
//  Creates empty vertex buffer
//
Buffer::Buffer( glm::vec3 pos, int textureUnit ) :
	_position( pos ),
	_textureUnit( textureUnit )
{
	glGenBuffers( 1, &_dataID );
	glGenBuffers( 1, &_indicesID );
}


// --------------------------------------------------------------------------------------------------------------------
//  Creates vertex buffer with starting data
//
Buffer::Buffer( std::vector<render::vertex>* data, glm::vec3 pos, int textureUnit ) :
	_position( pos ),
	_textureUnit( textureUnit )
{
	glGenBuffers( 1, &_dataID );
	glGenBuffers( 1, &_indicesID );
	setData( &(*data)[0], data->size() );

	std::vector<GLushort> indices;
	GLushort j = 0;
	for ( unsigned int i = 0u; i < data->size(); i++ )
		indices.push_back( j++ );

	setIndices( &indices[0], indices.size() );
}


// --------------------------------------------------------------------------------------------------------------------
//  Creates vertex buffer with starting data and indices
//
Buffer::Buffer( std::vector<render::vertex>* data, std::vector<GLushort>* indices, glm::vec3 pos, int textureUnit ) :
	_position( pos ),
	_textureUnit( textureUnit )
{
	glGenBuffers( 1, &_dataID );
	glGenBuffers( 1, &_indicesID );
	setData( &(*data)[0], data->size() );
	setIndices( &(*indices)[0], indices->size() );
}


// --------------------------------------------------------------------------------------------------------------------
//  Deletes buffer from GPU ram
//
Buffer::~Buffer( void )
{
//	glDeleteBuffers( 1, &_dataID );
//	glDeleteBuffers( 1, &_indicesID );
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets buffer data
//
void Buffer::setData( const vertex* data, int count ) const
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
void Buffer::setIndices( const GLushort* indices, int count )
{
	bind();
	_count = count;
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		_count * sizeof ( GLushort ),
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
	glBindBuffer( GL_ARRAY_BUFFER, _dataID );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _indicesID );
}


// --------------------------------------------------------------------------------------------------------------------
//  Unbind the VBO
//
void Buffer::unbind( void )
{
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets position to specified vector value
//
void Buffer::setPosition( glm::vec3 pos )
{
	_position = pos;
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns position
//
glm::vec3 Buffer::getPosition( void ) const
{
	return _position;
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets texture unit to specified integer value
//
void Buffer::setTextureUnit( int textureUnit )
{
	_textureUnit = textureUnit;
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns texture unit
//
int Buffer::getTextureUnit( void ) const
{
	return _textureUnit;
}


// --------------------------------------------------------------------------------------------------------------------
//  Renders the buffer
//
void Buffer::render( const GLint type ) const
{
	bind();
	glEnableVertexAttribArray( _attribLocationVertex );
	glEnableVertexAttribArray( _attribLocationSTR );
	glVertexAttribPointer(
		_attribLocationVertex,
		3,
		GL_FLOAT,
		GL_FALSE,
		24,
		(void*) 0
	);
	glVertexAttribPointer(
		_attribLocationSTR,
		3,
		GL_FLOAT,
		GL_FALSE,
		24,
		(void*) 12
	);

	glDrawElements(
		type,
		_count,
		GL_UNSIGNED_SHORT,
		(void*) 0
	);

	glDisableVertexAttribArray( _attribLocationVertex );
	glDisableVertexAttribArray( _attribLocationSTR );
	unbind();
}
