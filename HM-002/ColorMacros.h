// "ColorMacros.h"
//


// ----------------------------------------------------------------------------
//  COLOR MACROS
//
//  Syntax:
//    COL implies colour macro.
//    Second part shows format:
//      _CVS - rgba comma separated values
//      _VEC4 - rgba glm::vec4
//    Third part is the colour's unique name.
// ----------------------------------------------------------------------------

// OGL clear color (range 0.0f - 1.0f)
#define COL_CSV_CLEAR 0.02f, 0.03f, 0.08f, 1.0f

// Fog color
#define COL_VEC3_FOG glm::vec3( 0.01, 0.01, 0.0175 )
