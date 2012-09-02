// "Renderer.h"
//

#pragma once

#include "Base.h"

#include <vector>

#include <glm/ext.hpp>

// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace renderhandler
{
	typedef struct {
		float x, y, z;
		unsigned char r, g, b, a;
	} vertex;


	class Renderer;
	class Shader;
	class Buffer;
	class Matrices;


	class Renderer {
	private:
		GLuint vertexArrayID;

		renderhandler::Shader* shader;
		renderhandler::Matrices* matrices;
		renderhandler::Buffer* buffer;
	public:
		Renderer( void );

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
	private:
		static const int attribLocationVertex = 0;
		static const int attribLocationColor = 1;

		GLuint dataID;
		GLuint indicesID;
		int count;
	public:
		Buffer( void );

		void setData( vertex* data, int count ) const;
		void setIndices( unsigned int* indices, int count );

		void   bind( void ) const;
		void unbind( void ) const;

		void render( void ) const;
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
}
