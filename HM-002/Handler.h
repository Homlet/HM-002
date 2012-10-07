// "Handler.h"
//

#pragma once

#define _DEFINE_DEPRECATED_HASH_CLASSES 0
#include <hash_map>


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace render
{
	class Handler {
	private:
		GLuint _vertexArrayID;

		Shader   _shader;
		Matrices _matrices;

		std::hash_map<
			std::string,
			texture_object,
			hashdef::hash_std_string
		> _textures;
	public:
		Handler( void );

		void render(
			std::shared_ptr<update::Camera> camera,
			std::vector<render::Buffer>* buffers
		);
	};
}