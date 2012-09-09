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
		
		GLuint _uniformLocationMat4MV;
		GLuint _uniformLocationMat4P;
		GLuint _uniformLocationVec4Fog_Color;
	public:
		Shader( const char* vertFilePath, const char* fragFilePath );

		void        bind( void ) const;
		void setUniforms(
			glm::mat4 MV,
			glm::mat4 P,
			glm::vec4 Fog_Color
		) const;
		void      unbind( void ) const;
	};
}
