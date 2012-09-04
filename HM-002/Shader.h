// "Shader.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace render
{
	class Shader {
	private:
		GLuint _programID;
		GLuint _uniformLocationMatrix;
	public:
		Shader( const char* vertFilePath, const char* fragFilePath );

		void        bind( void ) const;
		void setUniforms( glm::mat4 MVP ) const;
		void      unbind( void ) const;
	};
}
