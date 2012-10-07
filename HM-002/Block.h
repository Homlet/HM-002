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

			block::BlockType _type;
		public:
			Block(
				block::BlockType type = block::BlockType_Air,
				bool active = false
			);

			bool getActive( void ) const;
			void setActive( bool active );
			
			block::BlockType getType( void ) const;
			void setType( block::BlockType type );
		};
	}
}