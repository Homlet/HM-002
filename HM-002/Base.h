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
//  GLOBAL MACROS
// ----------------------------------------------------------------------------

// Object side ids
#define GBL_FRONT 0
#define GBL_BACK 1
#define GBL_RIGHT 2
#define GBL_LEFT 3
#define GBL_TOP 4
#define GBL_BOTTOM 5


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
	class Camera;
	class Player;

//	namespace collide
//	{
//		class Sphere;
//		class AABB;
//	}

	class World;
	
	namespace world
	{
		typedef struct {
			GLint r;
			GLint front_r, back_r;
			GLint right_r, left_r;
			GLint top_r, bottom_r;

			GLint getBlockTextureBySide( int side )
			{
				switch ( side )
				{
				case GBL_FRONT :
					if ( front_r == -1 )
						return r;
					else
						return front_r;
				break;
					
				case GBL_BACK :
					if ( back_r == -1 )
						return r;
					else
						return back_r;
				break;
					
				case GBL_RIGHT :
					if ( right_r == -1 )
						return r;
					else
						return right_r;
				break;
					
				case GBL_LEFT :
					if ( left_r == -1 )
						return r;
					else
						return left_r;
				break;
					
				case GBL_TOP :
					if ( top_r == -1 )
						return r;
					else
						return top_r;
				break;
					
				case GBL_BOTTOM :
					if ( bottom_r == -1 )
						return r;
					else
						return bottom_r;
				break;

				default :
					fprintf(
						stderr,
						"Error: Invalid object side value"
					);
					return r;
				break;
				}
			};
		} block_data;

		class Block;

		namespace block
		{
			enum BlockType
			{
				BlockType_Air = 0,

			// 1
				BlockType_Dirt,
				BlockType_Grass,
				BlockType_Rock,
				BlockType_Sand,

				BlockType_Total
			};
		}

		class Chunk;

		namespace chunk
		{
			class Provider;
			class Generator;
		}
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
