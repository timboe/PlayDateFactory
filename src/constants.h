
#define TICK_FREQUENCY 32

#define NEAR_TICK_FREQUENCY 2
#define FAR_TICK_FREQUENCY 16

#define NEAR_TICK_AMOUNT 1
#define FAR_TICK_AMOUNT 8

#define TICKS_PER_SEC (NEAR_TICK_AMOUNT*TICK_FREQUENCY/NEAR_TICK_FREQUENCY)

#define TILE_PIX 16

#define EXTRACTOR_PIX (3*TILE_PIX)


#define DEVICE_PIX_X 400
#define DEVICE_PIX_Y 240

#define SCREEN_PIX_X (DEVICE_PIX_X-TILE_PIX)
#define SCREEN_PIX_Y (DEVICE_PIX_Y-TILE_PIX)

#define CHUNK_PIX_X (SCREEN_PIX_X/2)
#define CHUNK_PIX_Y (SCREEN_PIX_Y/2)

#define CHUNK_NEIGHBORS_CORNER 3
#define CHUNK_NEIGHBORS_ALL 8

// The -1 is for "me"
#define CHUNK_NONNEIGHBORS_CORNER (TOT_CHUNKS - CHUNK_NEIGHBORS_CORNER - 1) 
#define CHUNK_NONNEIGHBORS_ALL (TOT_CHUNKS - CHUNK_NEIGHBORS_ALL - 1)

#define TILES_PER_CHUNK_X (CHUNK_PIX_X/TILE_PIX)
#define TILES_PER_CHUNK_Y (CHUNK_PIX_Y/TILE_PIX)
#define TILES_PER_CHUNK (TILES_PER_CHUNK_X*TILES_PER_CHUNK_Y)

// 16x16 sprite sheet has how many rows/columns
#define SHEET16_SIZE_X 16
#define SHEET16_SIZE_Y 16
#define SHEET16_SIZE (SHEET16_SIZE_X*SHEET16_SIZE_Y)

#define SHEET48_SIZE_X 4
#define SHEET48_SIZE_Y 4
#define SHEET48_SIZE (SHEET48_SIZE_X*SHEET48_SIZE_Y)

#define TOT_CARGO_OR_BUILDINGS 4096

// Number of available floor sprites
#define FLOOR_TILES (8*4)

// Where the conveyor tiles start from in Y
#define CONV_START_Y 7

// How big is the world in X and Y
#define WORLD_CHUNKS_X 8
#define WORLD_CHUNKS_Y 8
#define TOT_CHUNKS (WORLD_CHUNKS_X*WORLD_CHUNKS_Y)

#define TOT_WORLD_PIX_X (WORLD_CHUNKS_X*CHUNK_PIX_X)
#define TOT_WORLD_PIX_Y (WORLD_CHUNKS_Y*CHUNK_PIX_Y)


#define TOT_TILES_X (TILES_PER_CHUNK_X*WORLD_CHUNKS_X)
#define TOT_TILES_Y (TILES_PER_CHUNK_Y*WORLD_CHUNKS_Y)
#define TOT_TILES (TOT_TILES_X*TOT_TILES_Y)

// Player acceleration and friction
#define PLAYER_A 0.75f
#define PLAYER_FRIC 0.8f

#define SQRT_HALF 0.70710678118f

// Fraction of the screen to trigger scrolling
//#define SCROLL_EDGE 0.8f

#define Z_INDEX_UI_RIGHT 32765
#define Z_INDEX_UI_BOTTOM 32766

#define Z_INDEX_UI_T 32767
#define Z_INDEX_UI_M 32766
#define Z_INDEX_UI_B 32765

#define Z_INDEX_MAX 32767
#define Z_INDEX_CARGO 32763
#define Z_INDEX_BLUEPRINT 32764
#define Z_INDEX_CONVEYOR 1
#define Z_INDEX_FLOOR -1

#define UI_ITEMS 12

#define UI_ROTATE_ACTION 270.0f

// Note: 1 larger than actual zoom levels (0 index unused)
// TODO changing this will break the chunk->obstacle add/remove 
#define ZOOM_LEVELS 3

// 5 fixed inputs plus 1 fixed output. Or three variable self-describings outputs. CAUTION: changing this currently requires manual change to de/serialisation
#define MAX_STORE 6

// Number of crops before a plot upgrades to farmland
#define N_CROPS_BEFORE_FARMLAND 4

#define WORLD_SAVE_SLOTS 16

#define WORLD_NAME_LENGTH 32

// Versioning
#define SAVE_FORMAT 1