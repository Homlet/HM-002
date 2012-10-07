// "Base.h"
//

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define DEBUG_MODE

#include <iostream>
#include <cstdlib>
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

namespace hashdef
{
	const struct hash_glm_ivec3 {
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

	const struct hash_std_string {
		enum
		{
			bucket_size = 4,
			min_bucket = 8
		};

		size_t operator() ( const std::string& str ) const
		{
			return std::hash<const char*>()( str.c_str() );
		}

		bool operator()(
			const std::string& left,
			const std::string& right
		) const
		{
			return strcmp( left.c_str(), right.c_str() ) == 0;
		}
	};
}

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

		class Block;

		namespace block
		{
			enum BlockType
			{
				BlockType_Air    = 0,

				BlockType_Dirt   = 1,
				BlockType_Grass  = 2,
				BlockType_Rock   = 3,
				BlockType_Sand   = 4,

				BlockType_Total
			};

			typedef struct {
				GLint r;
			} data;
		}

		class Chunk;
		class ChunkProvider;
	}
}


namespace render
{
	typedef struct {
		GLfloat x, y, z, s, t, r;
	} vertex;

	typedef struct {
		GLuint id;
		unsigned int w, h;
		bool isArray;

		void bind( void )
		{
			unbind();

			if ( isArray )
			{
				glActiveTexture( GL_TEXTURE0 + 2 );
				glBindTexture( GL_TEXTURE_2D_ARRAY, id );
			}
			else
			{
				glActiveTexture( GL_TEXTURE0 + 1 );
				glBindTexture( GL_TEXTURE_2D, id );
			}
		};

		static void unbind( void )
		{
			glActiveTexture( GL_TEXTURE0 + 1 );
			glBindTexture( GL_TEXTURE_2D, 0 );

			glActiveTexture( GL_TEXTURE0 + 2 );
			glBindTexture( GL_TEXTURE_2D_ARRAY, 0 );

			glActiveTexture( GL_TEXTURE0 );
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
