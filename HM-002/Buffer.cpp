// "Buffer.cpp"
//

#include "Render.h"

using namespace render;


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
	this->count = count;
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		count * sizeof ( GLushort ),
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
		type,
		count,
		GL_UNSIGNED_SHORT,
		(void*) 0
	);

	glDisableVertexAttribArray( attribLocationVertex );
	glDisableVertexAttribArray( attribLocationColor );
	unbind();
}
