// "Block.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace update
{
	namespace world
	{
		class Block {
		private:
			bool _isActive;

			BlockType _type;
		public:
			Block( BlockType type = BlockType_Air, bool active = false );

			bool getActive( void ) const;
			void setActive( bool active );
			
			BlockType getType( void ) const;
			void setType( BlockType type );
		};
	}
}