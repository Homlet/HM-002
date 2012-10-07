// "Loader.h"
//

#pragma once

#define _DEFINE_DEPRECATED_HASH_CLASSES 0
#include <hash_map>

#include "rapidxml.hpp"


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

			GLuint _loadTextureArray(
				char** paths,
				int count,
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

			std::hash_map<
				std::string,
				render::texture_object,
				hashdef::hash_std_string
			>* loadFromXML( char* uri ) const;
		};
	}
}
