// "Render.h"
//

#pragma once

#include "Base.h"

#include <vector>

#include <glm/ext.hpp>


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace render
{
	class Handler {
	private:
		GLuint vertexArrayID;

		  Shader* shader;
		  Buffer* buffer;
		Matrices* matrices;
	public:
		Handler( void );

		void render( void ) const;
	};

	
	class Shader {
	private:
		GLuint programID;
		GLuint uniformLocationMatrix;
	public:
		Shader( const char* vertFilePath, const char* fragFilePath );

		void        bind( void ) const;
		void setUniforms( glm::mat4 MVP ) const;
		void      unbind( void ) const;
	};

	class Buffer {
	protected:
		static const int attribLocationVertex = 0;
		static const int attribLocationColor = 1;

		GLuint dataID;
		GLuint indicesID;
		int count;
	public:
		Buffer( void );

		void setData( const vertex* data, int count ) const;
		void setIndices( const GLushort* indices, int count );

		       void   bind( void ) const;
		static void unbind( void );

		void render( const GLint type ) const;
	};
	

	class Matrices {
	private:
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 modelViewProjection;
	public:
		Matrices( void );

		void loadIdentity( void );
		void translate( glm::vec3 translation );
		void    rotate( glm::vec3 axis, float angle );
		void     scale( glm::vec3 scale );

		void setView(
			glm::vec3 cameraPosition,
			glm::vec3 cameraTarget,
			glm::vec3 upVector
		);
		void setProjection(
			float fov,
			float aspectRatio,
			float nearClip,
			float farClip
		);

		void computeModelViewProjection( void );
		glm::mat4 getModelViewProjection( void );
	};

	namespace utils
	{
		class Cube : public Buffer {
		private:
			static const vertex data[24];
			static const GLushort indices[14];
		public:
			Cube();
		};
	}
}
