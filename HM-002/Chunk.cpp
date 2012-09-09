// "Chunk.cpp"
//

#include "Base.h"
#include "Buffer.h"
#include "World.h"
#include "Chunk.h"
#include "Block.h"

using namespace update::world;


// --------------------------------------------------------------------------------------------------------------------
//  Returns a vector filled with vertex data for a cube
//
void Chunk::_createBlockBuffer(
		int x,
		int y,
		int z,
		bool front,
		bool back,
		bool right,
		bool left,
		bool top,
		bool bottom,
		BlockType type,
		std::vector<render::vertex>* data,
		std::vector<GLushort>* indices
	)
{
	GLushort offset = (GLushort) data->size();
	
	render::vertex p0 = { x - WLD_BLOCK_SIZE, y - WLD_BLOCK_SIZE, z + WLD_BLOCK_SIZE, 255,   0, 255, 255};
	render::vertex p1 = { x + WLD_BLOCK_SIZE, y - WLD_BLOCK_SIZE, z + WLD_BLOCK_SIZE, 255, 255, 255, 255};
	render::vertex p2 = { x + WLD_BLOCK_SIZE, y + WLD_BLOCK_SIZE, z + WLD_BLOCK_SIZE, 255, 255, 255, 255};
	render::vertex p3 = { x - WLD_BLOCK_SIZE, y + WLD_BLOCK_SIZE, z + WLD_BLOCK_SIZE, 255, 255,   0, 255};
	render::vertex p4 = { x + WLD_BLOCK_SIZE, y - WLD_BLOCK_SIZE, z - WLD_BLOCK_SIZE, 255,   0,   0, 255};
	render::vertex p5 = { x - WLD_BLOCK_SIZE, y - WLD_BLOCK_SIZE, z - WLD_BLOCK_SIZE, 255, 255, 255, 255};
	render::vertex p6 = { x - WLD_BLOCK_SIZE, y + WLD_BLOCK_SIZE, z - WLD_BLOCK_SIZE,   0, 255, 255, 255};
	render::vertex p7 = { x + WLD_BLOCK_SIZE, y + WLD_BLOCK_SIZE, z - WLD_BLOCK_SIZE, 255, 255, 255, 255};
	
	data->push_back( p0 );
	data->push_back( p1 );
	data->push_back( p2 );
	data->push_back( p3 );
	data->push_back( p4 );
	data->push_back( p5 );
	data->push_back( p6 );
	data->push_back( p7 );
	
	// Front
	if ( front )
	{
		indices->push_back( 0 + offset );
		indices->push_back( 1 + offset );
		indices->push_back( 2 + offset );
	
		indices->push_back( 0 + offset );
		indices->push_back( 2 + offset );
		indices->push_back( 3 + offset );
	}
	
	// Back
	if ( back )
	{
		indices->push_back( 4 + offset );
		indices->push_back( 5 + offset );
		indices->push_back( 6 + offset );
	
		indices->push_back( 4 + offset );
		indices->push_back( 6 + offset );
		indices->push_back( 7 + offset );
	}
	
	// Right
	if ( right )
	{
		indices->push_back( 1 + offset );
		indices->push_back( 4 + offset );
		indices->push_back( 7 + offset );
	
		indices->push_back( 1 + offset );
		indices->push_back( 7 + offset );
		indices->push_back( 2 + offset );
	}

	// Left
	if ( left )
	{
		indices->push_back( 5 + offset );
		indices->push_back( 0 + offset );
		indices->push_back( 3 + offset );
	
		indices->push_back( 5 + offset );
		indices->push_back( 3 + offset );
		indices->push_back( 6 + offset );
	}
	
	// Top
	if ( top )
	{
		indices->push_back( 3 + offset );
		indices->push_back( 2 + offset );
		indices->push_back( 7 + offset );
	
		indices->push_back( 3 + offset );
		indices->push_back( 7 + offset );
		indices->push_back( 6 + offset );
	}
	
	// Bottom
	if ( bottom )
	{
		indices->push_back( 5 + offset );
		indices->push_back( 4 + offset );
		indices->push_back( 1 + offset );
	
		indices->push_back( 5 + offset );
		indices->push_back( 1 + offset );
		indices->push_back( 0 + offset );
	}
}


// --------------------------------------------------------------------------------------------------------------------
//  Rebuilds the mesh
//
void Chunk::_rebuild( void )
{	
	std::vector<render::vertex>* data = &std::vector<render::vertex>();
	std::vector<GLushort>* indices = &std::vector<GLushort>();

	for ( int x = 0; x < WLD_CHUNK_SIZE; x++ )
		for ( int y = 0; y < WLD_CHUNK_SIZE; y++ )
			for ( int z = 0; z < WLD_CHUNK_SIZE; z++ )
			{
				if ( _blocks[x][y][z].getActive() == false )
					continue;
				
				bool front, back, right, left, top, bottom;

				back   = z == 0                  || !_blocks[x][y][z - 1].getActive();
				front  = z == WLD_CHUNK_SIZE - 1 || !_blocks[x][y][z + 1].getActive();
				left   = x == 0                  || !_blocks[x - 1][y][z].getActive();
				right  = x == WLD_CHUNK_SIZE - 1 || !_blocks[x + 1][y][z].getActive();
				bottom = y == 0                  || !_blocks[x][y - 1][z].getActive();
				top    = y == WLD_CHUNK_SIZE - 1 || !_blocks[x][y + 1][z].getActive();

				_createBlockBuffer(
					x,
					y,
					z,
					front,
					back,
					right,
					left,
					top,
					bottom,
					_blocks[x][y][z].getType(),
					data,
					indices
				);
			}
	
	_buffer = new render::Buffer( data, indices );
	_hasChanged = false;
}


// --------------------------------------------------------------------------------------------------------------------
//  Fills _blocks according to a 3d periodic perlin noise function
//
Chunk::Chunk( void ) :
	_hasChanged( true )
{
	_blocks = new Block**[WLD_CHUNK_SIZE];

    for ( int x = 0; x < WLD_CHUNK_SIZE; x++ )
    {
        _blocks[x] = new Block*[WLD_CHUNK_SIZE];

        for ( int y = 0; y < WLD_CHUNK_SIZE; y++ )
		{
            _blocks[x][y] = new Block[WLD_CHUNK_SIZE];

			for ( int z = 0; z < WLD_CHUNK_SIZE; z++ )
			{
				if ( glm::simplex( glm::vec3( x / WLD_FREQ, y / WLD_FREQ, z / WLD_FREQ ) ) > WLD_DENSITY_THRES )
					_blocks[x][y][z] = *new Block( BlockType_Dirt, true );
			}
		}
    }
}


// --------------------------------------------------------------------------------------------------------------------
//  Deletes all the blocks in _blocks
//
Chunk::~Chunk( void )
{
	for (int x = 0; x < WLD_CHUNK_SIZE; x++)
	{
		for ( int y = 0; y < WLD_CHUNK_SIZE; y++ )
		{
			for ( int z = 0; z < WLD_CHUNK_SIZE; z++ )
				delete &_blocks[x][y][z];
			
			delete [] _blocks[x][y];
		}
		
		delete [] _blocks[x];
	}
	
	delete [] _blocks;

	delete _buffer;
}


// --------------------------------------------------------------------------------------------------------------------
//  Runs chunk logic
//
void Chunk::update( double delta )
{
	if ( _hasChanged )
		_rebuild();
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns _meshes as a render::Buffer
//
render::Buffer* Chunk::getBuffer( void ) const
{
	return _buffer;
}
