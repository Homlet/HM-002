// "World.h"
//

#pragma once


// ----------------------------------------------------------------------------
//  WORLD MACROS
// ----------------------------------------------------------------------------

// Chunk xyz size, in blocks
#define WLD_CHUNK_SIZE 16

// Terrain frequency divisor
#define WLD_FREQ 8.0f

// Minimum terrain density threshold
#define WLD_DENSITY_THRES 1.2f / (y / WLD_CHUNK_SIZE + 1.0f) - 1.0f

// Block size, in OGL units / 2
#define WLD_BLOCK_SIZE 0.5f
