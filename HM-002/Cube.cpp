// "Cube.cpp"
//

#include "Base.h"

#include "Buffer.h"

#include "Cube.h"

using namespace render::buffer;


// --------------------------------------------------------------------------------------------------------------------
//  render::vertex vertex data
//
const render::vertex Cube::_data[24] = {
//  | x    | y    | z   |___| r  | g  | b  | a  |
	{-1.0f, -1.0f,  1.0f,    255, 255, 255, 255},
	{ 1.0f, -1.0f,  1.0f,    255, 255, 255, 255},
	{-1.0f,  1.0f,  1.0f,    255, 255, 255, 255},
	{ 1.0f,  1.0f,  1.0f,    255, 255, 255, 255},
	{-1.0f, -1.0f, -1.0f,    255, 255, 255, 255},
	{ 1.0f, -1.0f, -1.0f,    255, 255, 255, 255},
	{-1.0f,  1.0f, -1.0f,    255, 255, 255, 255},
	{ 1.0f,  1.0f, -1.0f,    255, 255, 255, 255}
//  | x    | y    | z   |___| r  | g  | b  | a  |
};


// --------------------------------------------------------------------------------------------------------------------
//  Unsigned short indices
//
const GLushort Cube::_indices[14] = {
	0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
};


// --------------------------------------------------------------------------------------------------------------------
//  Creates vertex buffer and fills it with data to draw a 2x2x2 cube (-1.0f to 1.0f on each axis)
//
Cube::Cube( void ) :
	Buffer( glm::vec3() )
{
	Buffer::setData( &_data[0], sizeof ( _data ) / sizeof ( vertex ) );
	Buffer::setIndices( &_indices[0], sizeof ( _indices ) / sizeof ( GLushort ) );
}
