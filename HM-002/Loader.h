// "Loader.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace render
{
	namespace texture
	{
		class Loader {
		private:
			static Loader* _instance;

			Loader( void );

			GLuint _loadTexture(
				char* path,
				int w,
				int h
			) const;

			unsigned char* _rawRGB_TGA(
				char* filename,
				int* w,
				int* h
			) const;
		public:
			static Loader* getInstance( void );

			std::vector<texture_object>* loadFromXML( char* uri ) const;
		};
	}
}
