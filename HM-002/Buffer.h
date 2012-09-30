// "Buffer.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace render
{
	class Buffer {
	private:
		static const int _attribLocationVertex = 0;
		static const int _attribLocationUV = 1;

		GLuint _dataID;
		GLuint _indicesID;
		int _count;

		glm::vec3 _position;
	public:
		Buffer( glm::vec3 pos );
		Buffer( std::vector<render::vertex>* data, glm::vec3 pos );
		Buffer(
			std::vector<render::vertex>* data,
			std::vector<GLushort>* indices,
			glm::vec3 pos
		);

		void setData( const vertex* data, int count ) const;
		void setIndices( const GLushort* indices, int count );

		       void   bind( void ) const;
		static void unbind( void );
		
		     void setPosition( glm::vec3 pos );
		glm::vec3 getPosition( void ) const;

		void render( const GLint type ) const;
	};
}
