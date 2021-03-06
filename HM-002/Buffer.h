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
		static const int _attribLocationSTR = 1;

		GLuint _dataID;
		GLuint _indicesID;
		int _count;

		glm::vec3 _position;
		int _textureUnit;
	public:
		Buffer( glm::vec3 pos, int textureUnit );
		Buffer(
			std::vector<render::vertex>* data,
			glm::vec3 pos,
			int textureUnit
		);
		Buffer(
			std::vector<render::vertex>* data,
			std::vector<GLushort>* indices,
			glm::vec3 pos,
			int textureUnit
		);
		~Buffer( void );

		void setData( const vertex* data, int count ) const;
		void setIndices( const GLushort* indices, int count );

		       void   bind( void ) const;
		static void unbind( void );
		
		     void setPosition( glm::vec3 pos );
		glm::vec3 getPosition( void ) const;
		
		void setTextureUnit( int textureUnit );
		 int getTextureUnit( void ) const;

		void render( const GLint type ) const;
	};
}
