// "Base.h"
//

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>

#include <math.h>

#include <GL/glew.h>
#include <GL/glfw.h>

#include <glm/glm.hpp>


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
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace render
{
	typedef struct {
		GLfloat x, y, z;
		unsigned char r, g, b, a;
	} vertex;

	class Handler;
	class Shader;
	class Buffer;
	class Matrices;

	namespace utils
	{
		class Cube;
	}
}