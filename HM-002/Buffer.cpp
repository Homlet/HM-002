// "Buffer.cpp"
//

#include "Base.h"
#include "Buffer.h"

using namespace render;


// --------------------------------------------------------------------------------------------------------------------
//  Creates empty vertex buffer
//
Buffer::Buffer( void )
{
	glGenBuffers( 1, &_dataID );
	glGenBuffers( 1, &_indicesID );
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets buffer data
//
void Buffer::setData( const vertex* data, int _count ) const
{
	bind();
	glBufferData(
		GL_ARRAY_BUFFER,
		_count * sizeof ( vertex ),
		data,
		GL_STATIC_DRAW
	);
	unbind();
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets buffer indices
//
void Buffer::setIndices( const GLushort* indices, int _count )
{
	bind();
	this->_count = _count;
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
//  Renders the buffer
//
void Buffer::render( const GLint type ) const
{
	bind();
	glEnableVertexAttribArray( _attribLocationVertex );
	glEnableVertexAttribArray( _attribLocationColor );
	glVertexAttribPointer(
		_attribLocationVertex,
		3,
		GL_FLOAT,
		GL_FALSE,
		16,
		(void*) 0
	);
	glVertexAttribPointer(
		_attribLocationColor,
		4,
		GL_UNSIGNED_BYTE,
		GL_FALSE,
		16,
		(void*) 12
	);

	glDrawElements(
		type,
		_count,
		GL_UNSIGNED_SHORT,
		(void*) 0
	);

	glDisableVertexAttribArray( _attribLocationVertex );
	glDisableVertexAttribArray( _attribLocationColor );
	unbind();
}
