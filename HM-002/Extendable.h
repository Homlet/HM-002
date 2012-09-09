// "Extendable.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace render
{
	namespace buffer
	{
		class Extendable : public Buffer {
		protected:
			std::vector<render::vertex> _data;
			std::vector<GLushort> _indices;
		public:
			Extendable( void );
			Extendable(
				std::vector<vertex>* data,
				std::vector<GLushort>* indices
			);
			
			Extendable operator+=( std::vector<render::vertex>& append );
			
			std::vector<render::vertex> getData( void ) const;
			std::vector<GLushort> getIndices( void ) const;
		};
	}
}
