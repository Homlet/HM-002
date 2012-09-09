// "Base.h"
//

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <math.h>

#include <GL/glew.h>
#include <GL/glfw.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>


// ----------------------------------------------------------------------------
//  WINDOW MACROS
// ----------------------------------------------------------------------------

// Window width and height
#define WIN_W 1600
#define WIN_H 900

// Bits per pixel attribute
#define WIN_RED_BITS   8
#define WIN_BLUE_BITS  8
#define WIN_GREEN_BITS 8
#define WIN_ALPHA_BITS 8

#define WIN_DEPTH_BITS 24

// FSAA samples
#define WIN_FSAA 4

// Window title
#define WIN_TITLE "HM-002"

// Fullscreen or windowed
#define WIN_TYPE GLFW_WINDOW


// ----------------------------------------------------------------------------
//  FORWARD DECLARATIONS
// ----------------------------------------------------------------------------

namespace update
{
	class State;
	class Input;
	class Entity;
	class Player;

//	namespace collide
//	{
//		class Sphere;
//		class AABB;
//	}

	class World;
	
	namespace world
	{
		enum BlockType
		{
			BlockType_Air = 0,

			BlockType_Dirt,
			BlockType_Grass,
			BlockType_Rock,
			BlockType_Sand,

			BlockType_Total
		};

		class Block;
		class Chunk;
	}
}


namespace render
{
	typedef struct {
		GLfloat x, y, z;
		GLubyte r, g, b, a;
	} vertex;
	
	class Handler;
	class Shader;
	class Matrices;
	class Buffer;

	namespace buffer
	{
		class Cube;
	}
}