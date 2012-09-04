// "Entity.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace update
{
	class Entity {
	private:
		glm::vec3 _position;
		render::Buffer _buffer;
	public:
		Entity( glm::vec3 pos, render::Buffer draw );

		virtual void update( double delta );

		render::Buffer getBuffer() const;
	};
}