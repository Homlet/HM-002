// "Generator.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace update
{
	namespace world
	{
		namespace chunk
		{
			class Generator {
			private:
				static double _getThreshold(
					glm::vec3 pos,
					const noise::module::Module* terrainFunc,
					const noise::module::Module* heightFunc
				);

				const noise::module::Module* _getTerrainFunc( void ) const;
				const noise::module::Module* _getHeightFunc( void ) const;
				
				const noise::module::Module* _terrainFunc;
				const noise::module::Module*  _heightFunc;

				const long int _seed;
			public:
				Generator( long int seed );

				void setChunk(
					glm::vec3 pos,
					Block**** blocks
				) const;
			};
		}
	}
}