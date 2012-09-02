// "Cube.cpp"
//

#include "Render.h"

using namespace render::utils;


// --------------------------------------------------------------------------------------------------------------------
//  render::vertex vertex data
//
const render::vertex Cube::data[24] = {
//  | x    | y    | z   |___| r  | g  | b  | a  |
	{-1.0f, -1.0f,  1.0f,     10, 100, 150, 255},
	{ 1.0f, -1.0f,  1.0f,     20, 120, 100, 255},
	{-1.0f,  1.0f,  1.0f,     30, 100, 150, 255},
	{ 1.0f,  1.0f,  1.0f,     40, 100, 100, 255},
	{-1.0f, -1.0f, -1.0f,     50, 120, 150, 255},
	{ 1.0f, -1.0f, -1.0f,     60, 100, 100, 255},
	{-1.0f,  1.0f, -1.0f,     70, 100, 150, 255},
	{ 1.0f,  1.0f, -1.0f,     80, 120, 100, 255}
//  | x    | y    | z   |___| r  | g  | b  | a  |
};


// --------------------------------------------------------------------------------------------------------------------
//  Unsigned short indices
//
const GLushort Cube::indices[14] = {
	0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
};


// --------------------------------------------------------------------------------------------------------------------
//  Creates vertex buffer and fills it with data to draw a 2x2x2 cube (-1.0f to 1.0f on each axis)
//
Cube::Cube( void )
{
	Buffer::setData( &data[0], sizeof ( data ) / sizeof ( vertex ) );
	Buffer::setIndices( &indices[0], sizeof ( indices ) / sizeof ( GLushort ) );
}
