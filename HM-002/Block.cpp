// "Block.cpp"
//

#include "Base.h"

#include "Block.h"

using namespace update::world;


// --------------------------------------------------------------------------------------------------------------------
//  Creates new block with specified parameters
//
Block::Block( BlockType type, bool active ) :
	_type( type ),
	_isActive( active )
{

}


// --------------------------------------------------------------------------------------------------------------------
//  Returns _isActive
//
bool Block::getActive( void ) const
{
	return _isActive;
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets _isActive to specified value
//
void Block::setActive( bool active )
{
	_isActive = active;
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns _type
//
BlockType Block::getType( void ) const
{
	return _type;
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets _type to specified value
//
void Block::setType( BlockType type )
{
	_type = type;
}
