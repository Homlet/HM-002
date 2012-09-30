// "Handler.h"
//

#pragma once


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

		std::vector<texture_object> _textures;
	public:
		Handler( void );

		void render(
			std::shared_ptr<update::Camera> camera,
			std::vector<render::Buffer>* buffers
		);
	};
}