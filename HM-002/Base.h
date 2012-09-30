// "Base.h"
//

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define DEBUG_MODE

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
//  FORWARD DECLARATIONS
// ----------------------------------------------------------------------------

namespace update
{
	// Singleton
	class Input;

	class State;
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
		const struct HashConfig {
			enum
			{
				bucket_size = 4,
				min_bucket = 8
			};

			size_t operator() ( const glm::ivec3& vec ) const
			{
				return ( vec.x * 73856093 ^
				         vec.y * 19349663 ^
				         vec.z * 83492791 ) % ( 256 * 256 * 256 );
			}

			bool operator()(
				const glm::ivec3& left,
				const glm::ivec3& right
			) const
			{
				return left.x < right.x ||
				       left.y < right.y ||
				       left.z < right.z;
			}
		};

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
		class ChunkProvider;
	}
}


namespace render
{
	typedef struct {
		GLfloat x, y, z, s, t;
	} vertex;

	typedef struct {
		std::string name;
		GLuint id;
		unsigned int w, h;

		void bind( void )
		{
			glBindTexture( GL_TEXTURE_2D, id );
		};

		static void unbind( void )
		{
			glBindTexture( GL_TEXTURE_2D, 0 );
		};
	} texture_object;

	namespace texture
	{
		// Singleton
		class Loader;
	}
	
	class Handler;
	class Shader;
	class Matrices;
	class Buffer;

	namespace buffer
	{
		class Cube;
	}
}