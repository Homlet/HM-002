// "Buffer.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace render
{
	class Buffer {
	protected:
		static const int _attribLocationVertex = 0;
		static const int _attribLocationColor = 1;

		GLuint _dataID;
		GLuint _indicesID;
		int _count;
	public:
		Buffer( void );

		void setData( const vertex* data, int count ) const;
		void setIndices( const GLushort* indices, int count );

		       void   bind( void ) const;
		static void unbind( void );

		void render( const GLint type ) const;
	};
}
