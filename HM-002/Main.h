// "Main.h"
//

#pragma once

#include "Base.h"
#include "Render.h"

// ----------------------------------------------------------------------------
//  WINDOW MACROS
// ----------------------------------------------------------------------------

// Window width and height
#define WIN_W 1280
#define WIN_H 720

// Bits per pixel attribute
#define WIN_RED_BITS   8
#define WIN_BLUE_BITS  8
#define WIN_GREEN_BITS 8
#define WIN_ALPHA_BITS 8

#define WIN_DEPTH_BITS 24

// Window title
#define WIN_TITLE "HM-002"

// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

int initializeWindow( void );
