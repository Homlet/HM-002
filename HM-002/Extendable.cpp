// "Extendable.cpp"
//

#include "Base.h"
#include "Buffer.h"
#include "Extendable.h"

using namespace render::buffer;


// --------------------------------------------------------------------------------------------------------------------
//  Creates extendable empty vertex buffer
//
Extendable::Extendable( void ) :
	Buffer()
{

}


// --------------------------------------------------------------------------------------------------------------------
//  Creates extendable vertex buffer and fills it with the starting data
//
Extendable::Extendable( std::vector<render::vertex>* data, std::vector<GLushort>* indices ) :
	Buffer(),
	_data( *data ),
	_indices( *indices )
{
	Buffer::setData( &_data[0], _data.size() );
	Buffer::setIndices( &_indices[0], _indices.size() );
}


// --------------------------------------------------------------------------------------------------------------------
//  Appends data from a vector to the end of the current buffer, performs optimisations
//
Extendable Extendable::operator+=( std::vector<render::vertex>& append )
{
	unsigned int originalSize = _data.size();

	for ( unsigned int i = 0u; i < append.size(); i++ )
	{
		int index = -1;
		for ( unsigned int j = 0u; j < originalSize; j++ )
		{
			if ( _data.at( j ).x == append.at( i ).x &&
				 _data.at( j ).y == append.at( i ).y &&
				 _data.at( j ).z == append.at( i ).z &&
				 _data.at( j ).r == append.at( i ).r &&
				 _data.at( j ).g == append.at( i ).g &&
				 _data.at( j ).b == append.at( i ).b &&
				 _data.at( j ).a == append.at( i ).a )
			{
				index = j;
			}
		}

		if ( index == -1 )
		{
			_data.push_back( append[i] );
			_indices.push_back( _data.size() );
		} else
		{
			_indices.push_back( index );
		}
	}
	
	return Extendable( &_data, &_indices );
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns _data
//
std::vector<render::vertex> Extendable::getData( void ) const
{
	return _data;
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns _indices
//
std::vector<GLushort> Extendable::getIndices( void ) const
{
	return _indices;
}
