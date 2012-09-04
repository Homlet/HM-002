// "Cube.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace render
{
	namespace buffer
	{
		class Cube : public Buffer {
		private:
			static const vertex _data[24];
			static const GLushort _indices[14];
		public:
			Cube();
		};
	}
}