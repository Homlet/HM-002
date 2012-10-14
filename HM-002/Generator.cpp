// "Generator.cpp"
//

#include "WorldMacros.h"

#include "Base.h"

#include "Block.h"
#include "noise\noise.h"

#include "Generator.h"

using namespace update::world::chunk;


// --------------------------------------------------------------------------------------------------------------------
//  Returns threshold for given position based on given noise functions
//
double Generator::_getThreshold(
	glm::vec3 pos,
	const noise::module::Module* terrainFunc,
	const noise::module::Module* heightFunc
)
{
	double terrainValue = terrainFunc->GetValue( pos.x, pos.y, pos.z );
	terrainValue        = ( terrainValue + 1.0 ) / 4.0 + 0.5;

	double heightValue  = heightFunc->GetValue( pos.x, pos.z, 0.0 );
	heightValue         = ( ( heightValue + 1.0 ) / 2.0 ) * ( WLD_MOUNTAINTOP_LEVEL - WLD_SEA_LEVEL );

	return terrainValue * heightValue + WLD_SEA_LEVEL;
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns basic noise module based on set flags
//
const noise::module::Module* Generator::_getTerrainFunc( void ) const
{
	noise::module::Perlin* perlin = new noise::module::Perlin();
	perlin->SetSeed( _seed );
	perlin->SetFrequency( WLD_FREQ );
	perlin->SetPersistence( 0.45 );

	return perlin;
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns basic heightmap noise module based on set flags
//
const noise::module::Module* Generator::_getHeightFunc( void ) const
{
	noise::module::Perlin* perlin = new noise::module::Perlin();
	perlin->SetSeed( _seed );
	perlin->SetFrequency( WLD_HEIGHTMAP_FREQ );
	perlin->SetPersistence( 0.6 );

	return perlin;
}


// --------------------------------------------------------------------------------------------------------------------
//  Creates new chunk generator object with specified seed
//
Generator::Generator( long int seed ) :
	_seed( seed )
{
	_terrainFunc = _getTerrainFunc();
	_heightFunc = _getHeightFunc();
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets 3d block array of given size with set flags
//
void Generator::setChunk( glm::vec3 pos, update::world::Block**** blocks ) const
{
	*blocks = new Block**[WLD_CHUNK_SIZE];

	for ( int x = 0; x < WLD_CHUNK_SIZE; x++ )
	{
		(*blocks)[x] = new Block*[WLD_CHUNK_SIZE];

		for ( int y = 0; y < WLD_CHUNK_SIZE; y++ )
		{
			(*blocks)[x][y] = new Block[WLD_CHUNK_SIZE];

			for ( int z = 0; z < WLD_CHUNK_SIZE; z++ )
			{
				double threshold = _getThreshold(
					glm::vec3( x + pos.x, y + pos.y, z + pos.z ),
					_terrainFunc,
					_heightFunc
				);

				if ( y + pos.y <= threshold )
				{
					threshold = _getThreshold(
						glm::vec3( x + pos.x, y + pos.y + 1, z + pos.z ),
						_terrainFunc,
						_heightFunc
					);

					if ( y + pos.y + 1 > threshold )
						(*blocks)[x][y][z] = Block( block::BlockType_Grass, true );
					else
						(*blocks)[x][y][z] = Block( block::BlockType_Dirt, true );
				} else
				{
					(*blocks)[x][y][z] = Block( block::BlockType_Air, false );
				}
			}
		}
	}
}
