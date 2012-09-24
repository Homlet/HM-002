// "Entity.cpp"
//

#include "Base.h"

#include "Buffer.h"

#include "Entity.h"

using namespace update;


// --------------------------------------------------------------------------------------------------------------------
//  Sets the position and draw object
//
Entity::Entity( glm::vec3 pos, render::Buffer buffer ) :
	_position( pos ),
	_buffer( buffer )
{

}


// --------------------------------------------------------------------------------------------------------------------
//  Runs object logic
//
void Entity::update( double delta )
{

}


// --------------------------------------------------------------------------------------------------------------------
//  Returns the draw object
//
render::Buffer Entity::getBuffer() const
{
	return _buffer;
}
