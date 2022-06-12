#include "game.h"
#include "generate.h"
#include "sprite.h"
#include "chunk.h"
#include "location.h"
#include "building.h"

#include <math.h>

struct Tile_t* m_tiles = NULL;

uint16_t m_deserialiseIndexWorld = 0;

const int32_t SIZE_GENERATE = TOT_TILES * sizeof(struct Tile_t);
 
void generateSpriteSetup(struct Chunk_t* _chunk);

struct Tile_t* getTileInChunk(struct Chunk_t* _chunk, int32_t _u, int32_t _v);

bool addLake(int32_t _startX, int32_t _startY, int32_t _riverProb);

void addSpawn(void);

void doLakesAndRivers(void);

float pointDist(int32_t _x, int32_t _y, int32_t _x1, int32_t _y1, int32_t _x2, int32_t _y2);

/// ///

struct Tile_t* getTileInChunk(struct Chunk_t* _chunk, int32_t _u, int32_t _v) {
  return &m_tiles[ (WORLD_CHUNKS_X * TILES_PER_CHUNK_X)*((TILES_PER_CHUNK_Y * _chunk->m_y) + _v) + ((TILES_PER_CHUNK_X * _chunk->m_x) + _u) ];
}

struct Tile_t* getTile(int32_t _x, int32_t _y) {
  if (_x < 0) _x += TOT_TILES_X;
  else if (_x >= TOT_TILES_X) _x -= TOT_TILES_X;
  if (_y < 0) _y += TOT_TILES_Y;
  else if (_y >= TOT_TILES_Y) _y -= TOT_TILES_Y;
  return &m_tiles[ TOT_TILES_X*_y + _x ];
}

float pointDist(int32_t _x, int32_t _y, int32_t _x1, int32_t _y1, int32_t _x2, int32_t _y2) {

  int32_t A = _x - _x1;
  int32_t B = _y - _y1;
  int32_t C = _x2 - _x1;
  int32_t D = _y2 - _y1;

  float dot = A * C + B * D;
  int32_t len_sq = C * C + D * D;
  float param = -1;
  if (len_sq != 0) { //in case of 0 length line
    param = dot / len_sq;
  }

  int32_t xx, yy;

  if (param < 0) {
    xx = _x1;
    yy = _y1;
  } else if (param > 1) {
    xx = _x2;
    yy = _y2;
  } else {
    xx = _x1 + param * C;
    yy = _y1 + param * D;
  }

  int32_t dx = _x - xx;
  int32_t dy = _y - yy;
  return sqrt(dx * dx + dy * dy);
}

#define SPAWN_START_X 8
#define SPAWN_START_Y 8
#define SPAWN_END_X 16
#define SPAWN_END_Y 8
#define SPAWN_RADIUS 6
void addSpawn() {
  for (int32_t x = 0; x < SPAWN_END_X+SPAWN_RADIUS; ++x) {
    for (int32_t y = 0; y < SPAWN_END_Y+SPAWN_RADIUS; ++y) {
      if (pointDist(x, y, SPAWN_START_X, SPAWN_START_Y, SPAWN_END_X, SPAWN_END_Y) < SPAWN_RADIUS) {
        getTile(x, y)->m_tile = getSprite16_idx(8, 2) + rand() % 4;
      }
    }
  }
}

#define BIOME_RADIUS 16
#define BIOME_POINTS_TOO_CLOSE (TOT_TILES_X/2 - 3*BIOME_RADIUS)
void addBiome(int32_t _offX, int32_t _offY, uint16_t _imgStart) {
  bool good = false;
  int32_t x1, y1, x2, y2;
  while (!good) {
    x1 = BIOME_RADIUS + rand() % (TOT_TILES_X/2 - 2*BIOME_RADIUS);
    y1 = BIOME_RADIUS + rand() % (TOT_TILES_Y/2 - 2*BIOME_RADIUS);
    x2 = BIOME_RADIUS + rand() % (TOT_TILES_X/2 - 2*BIOME_RADIUS);
    y2 = BIOME_RADIUS + rand() % (TOT_TILES_Y/2 - 2*BIOME_RADIUS);
    if (sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ) > BIOME_POINTS_TOO_CLOSE) break;
  }
  for (int32_t x = _offX; x < TOT_TILES_X/2 + _offX; ++x) {
    for (int32_t y = _offY; y < TOT_TILES_Y/2 + _offY; ++y) {
      if (pointDist(x, y, x1 + _offX, y1 + _offY, x2 + _offX, y2 + _offY) < BIOME_RADIUS) {
        getTile(x, y)->m_tile = _imgStart + rand() % 8;
      }
    }
  }
}

uint8_t distanceFromWater(int32_t _x, int32_t _y) {
  uint8_t r = 0;
  const uint16_t waterStart = getSprite16_idx(0, 5);
  if (getTile(_x, _y)->m_tile >= waterStart) return 0;
  while (++r < 255) {
    for (int32_t x = _x - r; x < _x + r; ++x) {
      if (getTile(x, _y - r)->m_tile >= waterStart) return r;
      if (getTile(x, _y + r)->m_tile >= waterStart) return r;
    }
    for (int32_t y = _y - r; y < _y + r; ++y) {
      if (getTile(_x + r, y)->m_tile >= waterStart) return r;
      if (getTile(_x - r, y)->m_tile >= waterStart) return r;
    }
  }
  return 255;
}

void doWetness(void) {
  for (int32_t x = 0; x < TOT_TILES_X; ++x) {
    for (int32_t y = 0; y < TOT_TILES_Y; ++y) {
      getTile(x, y)->m_wetness = distanceFromWater(x,y);
    }
  }
}

#define LAKE_MIN 10
#define LAKE_MAX 18
#define RIVER_MIN 8
#define RIVER_MAX 32
bool addRiver(int32_t _startX, int32_t _startY, enum kDir _dir, int32_t _riverProb) {

  getTile(_startX,_startY)->m_tile = getSprite16_idx(5+(_dir == NS ? 1 : 0), 11);

  int32_t lenA = RIVER_MIN + rand() % (RIVER_MAX - RIVER_MIN);
  bool switchA = rand() % 2;
  bool switchDir = rand() % 2;
  int32_t lenB = RIVER_MIN + rand() % (RIVER_MAX - RIVER_MIN);
  bool switchB = switchA && rand() % 2;
  int32_t lenC = RIVER_MIN + rand() % (RIVER_MAX - RIVER_MIN);

  bool endInLake = rand() % 2;

  if (_dir == WE) {
    for (int32_t x = _startX + 1; x < _startX + lenA; ++x) getTile(x, _startY)->m_tile = getSprite16_idx(5, 12);
    if (switchA) getTile(_startX + lenA, _startY)->m_tile = getSprite16_idx(6 + (switchDir ? 0 : 1), 13);
    else if (endInLake) return addLake(_startX + lenA, _startY - LAKE_MIN/2, _riverProb);
    else getTile(_startX + lenA, _startY)->m_tile = getSprite16_idx(5, 14);
  } else if (_dir == NS) {
    for (int32_t y = _startY + 1; y < _startY + lenA; ++y) getTile(_startX, y)->m_tile = getSprite16_idx(4, 12);
    if (switchA) getTile(_startX, _startY + lenA)->m_tile = getSprite16_idx(4 + (switchDir ? 0 : 3), 13);
    else if (endInLake) return addLake(_startX - LAKE_MIN/2, _startY + lenA, _riverProb);
    else getTile(_startX, _startY + lenA)->m_tile = getSprite16_idx(4, 14);
  }

  if (switchA && _dir == WE) {
    if (switchDir) {
      for (int32_t y = _startY + 1; y < _startY + lenB; ++y) getTile(_startX + lenA, y)->m_tile = getSprite16_idx(4, 12);
      if (switchB) getTile(_startX + lenA, _startY + lenB)->m_tile = getSprite16_idx(4, 13);
      else getTile(_startX + lenA, _startY + lenB)->m_tile = getSprite16_idx(4, 14);
    } else {
      for (int32_t y = _startY - 1; y > _startY - lenB; --y) getTile(_startX + lenA, y)->m_tile = getSprite16_idx(4, 12); 
      if (switchB) getTile(_startX + lenA, _startY - lenB)->m_tile = getSprite16_idx(5, 13);
      else getTile(_startX + lenA, _startY - lenB)->m_tile = getSprite16_idx(6, 14);
    }
  } else if (switchA && _dir == NS) {
    if (switchDir) {
      for (int32_t x = _startX + 1; x < _startX + lenB; ++x) getTile(x, _startY + lenA)->m_tile = getSprite16_idx(5, 12);
      if (switchB) getTile(_startX + lenB, _startY + lenA)->m_tile = getSprite16_idx(6, 13);
      else getTile(_startX + lenB, _startY + lenA)->m_tile = getSprite16_idx(5, 14);
    } else {
      for (int32_t x = _startX - 1; x > _startX - lenB; --x) getTile(x, _startY + lenA)->m_tile = getSprite16_idx(5, 12); 
      if (switchB) getTile(_startX - lenB, _startY + lenA)->m_tile = getSprite16_idx(5, 13);
      else getTile(_startX - lenB, _startY + lenA)->m_tile = getSprite16_idx(7, 14);
    }
  }

  int32_t signedLenB = lenB * (switchDir ? 1 : -1);
  if (switchB && _dir == WE) {
    for (int32_t x = _startX + lenA + 1; x < _startX + lenA + lenC; ++x) getTile(x, _startY + signedLenB)->m_tile = getSprite16_idx(5, 12);
    if (endInLake) return addLake(_startX + lenA + lenC, _startY + signedLenB - LAKE_MIN/2, _riverProb); 
    else getTile(_startX + lenA + lenC, _startY + signedLenB)->m_tile = getSprite16_idx(5, 14);
  } else if (switchB && _dir == NS) {
    for (int32_t y = _startY + lenA + 1; y < _startY + lenA + lenC; ++y) getTile(_startX + signedLenB, y)->m_tile = getSprite16_idx(4, 12);
    if (endInLake) return addLake(_startX + signedLenB - LAKE_MIN/2, _startY + lenA + lenC, _riverProb); 
    else getTile(_startX + signedLenB, _startY + lenA + lenC)->m_tile = getSprite16_idx(4, 14);
  }

  return false;

}

bool addLake(int32_t _startX, int32_t _startY, int32_t _riverProb) {
  uint8_t w = rand() % (LAKE_MAX - LAKE_MIN) + LAKE_MIN; 
  uint8_t h = rand() % (LAKE_MAX - LAKE_MIN) + LAKE_MIN; 
  uint8_t c_x[4] = {0};
  uint8_t c_y[4] = {0};
  for (uint8_t i = 0; i < 4; ++i) {
    if (rand() % 2) {
      c_x[i] = 2 + rand() % 2;
      c_y[i] = 2 + rand() % 2;
    }
  }

  // Check
  for (int32_t x = _startX; x < _startX + w; ++x) {
    if (getTile(x,_startY)->m_tile > FLOOR_TILES) return true; // Reject
    if (getTile(x,_startY+h)->m_tile > FLOOR_TILES) return true; // Reject
  }
  for (int32_t y = _startY; y < _startY + h + 1; ++y) {
    if (getTile(_startX,y)->m_tile > FLOOR_TILES) return true; // Reject
    if (getTile(_startX+w,y)->m_tile > FLOOR_TILES) return true; // Reject
  }

  uint16_t tex;
  // LR
  for (int32_t x = _startX; x < _startX + w; ++x) {
    int32_t y = _startY;
    tex = getSprite16_idx(4,5);
    if      (x == _startX) tex = getSprite16_idx(0,5); // Corner
    else if (c_x[0] && (x-_startX) == c_x[0]) tex = getSprite16_idx(0,6); // Inner corner
    else if (c_x[1] && (x-_startX) == w - c_x[1]) tex = getSprite16_idx(1,6); // Inner corner

    if      (c_x[0] && (x-_startX) <     c_x[0] + 1) y += c_y[0];
    else if (c_x[1] && (x-_startX) > w - c_x[1] - 1) y += c_y[1];

    getTile(x,y)->m_tile = tex;

    y = _startY + h;
    tex = getSprite16_idx(6,5);
    if (x == _startX) tex = getSprite16_idx(3,5);
    else if (c_x[3] && (x-_startX) == c_x[3]) tex = getSprite16_idx(3,6); // Inner corner
    else if (c_x[2] && (x-_startX) == w - c_x[2]) tex = getSprite16_idx(2,6); // Inner corner


    if      (c_x[3] && (x-_startX) <     c_x[3] + 1) y -= c_y[3];
    else if (c_x[2] && (x-_startX) > w - c_x[2] - 1) y -= c_y[2];

    getTile(x,y)->m_tile = tex;
  }
  // TB
  for (int32_t y = _startY; y < _startY + h + 1; ++y) {
    int32_t x = _startX;
    tex = getSprite16_idx(7,5);
    if      (y == _startY) tex = getSprite16_idx(0,5); // Corner
    else if (c_y[0] && (y-_startY) == c_y[0])     tex = getSprite16_idx(0,5);
    else if (c_y[3] && (y-_startY) == h - c_y[3]) tex = getSprite16_idx(3,5);
    else if (y == _startY+h)                      tex = getSprite16_idx(3,5);

    if      (c_y[0] && (y-_startY) <     c_y[0] ) x += c_x[0];
    else if (c_y[3] && (y-_startY) > h - c_y[3] ) x += c_x[3];

    getTile(x,y)->m_tile = tex;

    x = _startX + w;
    tex = getSprite16_idx(5,5);
    if      (y == _startY) tex = getSprite16_idx(1,5); // Corner
    else if (c_y[1] && (y-_startY) == c_y[1]) tex = getSprite16_idx(1,5);
    else if (c_y[2] && (y-_startY) == h - c_y[2]) tex = getSprite16_idx(2,5);
    else if (y == _startY+h)          tex = getSprite16_idx(2,5);

    if      (c_y[1] && (y-_startY) <     c_y[1]) x -= c_x[1];
    else if (c_y[2] && (y-_startY) > h - c_y[2]) x -= c_x[2];

    getTile(x,y)->m_tile = tex;
  }

  // (Literal) Flood fill
  for (int32_t x = _startX + 1; x < _startX + w; ++x) {
    bool fill = false;
    for (int32_t y = _startY; y < _startY + h; ++y) {
      struct Tile_t* t = getTile(x,y);
      if (fill && t->m_tile > FLOOR_TILES) break;
      if (fill) t->m_tile = getSprite16_idx(4 + rand() % 4, 6);
      if (!fill && t->m_tile > FLOOR_TILES && getTile(x,y+1)->m_tile <= FLOOR_TILES) fill = true;
    }
  }

  bool toAddRiver = rand() < _riverProb;
  bool riverWE = rand() % 2;
  if (toAddRiver) {
    if (riverWE) return addRiver(_startX + w, _startY + h/2, WE, _riverProb/2);
    else return addRiver(_startX + w/2, _startY + h, NS, _riverProb/2);
  }

  return false;
}

void doLakesAndRivers() {
  struct Tile_t* backup = pd->system->realloc(NULL, SIZE_GENERATE);
  int8_t addToRegion[7] = {1,1,1,1,1,1,1};
  if (rand() % 2 == 0) addToRegion[rand() % 7] = 0;
  if (rand() % 4 == 0) addToRegion[rand() % 7] = 0;

  for (uint8_t i = 0; i < 5; ++i) {
    if (!addToRegion[i]) continue;
    for (int32_t try = 0; try < 5; ++try) {
      int32_t x = rand() % (TOT_TILES_X/2);
      int32_t y = rand() % (TOT_TILES_Y/2);
      switch (i) {
        case 1: x += TOT_TILES_X/2; break;
        case 2: y += TOT_TILES_Y/2; break;
        case 3: x += TOT_TILES_X/2; y += TOT_TILES_Y/2; break;
        case 4: x += TOT_TILES_X/4; y += TOT_TILES_Y/4; break;
        case 5: case 6: x = rand() % TOT_TILES_X; y = rand() % TOT_TILES_Y; break;
      }
      memcpy(backup, m_tiles, SIZE_GENERATE);
      bool reject = addLake(x, y, RAND_MAX/2);
      if (reject) {
        pd->system->logToConsole("generate: rejected %i lake system at %i,%i (try %i)", i, x, y, try);
        memcpy(m_tiles, backup, SIZE_GENERATE);
      } else {
        pd->system->logToConsole("generate: added %i lake system at %i,%i", i, x, y);
        break;
      }
    }
  }
  pd->system->realloc(backup, 0); // Free
  
}

void renderChunkBackgroundImage(struct Chunk_t* _chunk) {
  pd->graphics->pushContext(_chunk->m_bkgImage[1]);
  pd->graphics->setDrawMode(kDrawModeCopy);
  pd->graphics->fillRect(0, 0, CHUNK_PIX_X, CHUNK_PIX_Y, kColorWhite);
  for (uint16_t v = 0; v < TILES_PER_CHUNK_Y; ++v) {
    for (uint16_t u = 0; u < TILES_PER_CHUNK_X; ++u) {
      struct Tile_t* t = getTileInChunk(_chunk, u, v);
      LCDBitmap* b = getSprite16(t->m_tile, 0, 1); // Top row of sprite sheet
      pd->graphics->drawBitmap(b, u * TILE_PIX, v * TILE_PIX, kBitmapUnflipped);
      if (t->m_wetness > 0 && t->m_wetness < 8) { // If wet, but not actually water
        for (int32_t w = 0; w < (8 - t->m_wetness); ++w) {
          pd->graphics->drawBitmap(getSprite16(12 + (w/2 + v*u)%4, 2, 1), u * TILE_PIX, v * TILE_PIX, kBitmapUnflipped);
        }
      }
    }
  }

  #ifdef DEV
  setRoobert24();
  pd->graphics->drawRect(0, 0, CHUNK_PIX_X, CHUNK_PIX_Y, kColorBlack);
  static char text[16];
  snprintf(text, 16, "(%u,%u)", _chunk->m_x, _chunk->m_y);
  pd->graphics->drawText(text, 16, kASCIIEncoding, TILE_PIX, TILE_PIX);
  #endif

  // Shift from Sprite to Bitmap draw coords
  const int16_t off_x = (_chunk->m_x * CHUNK_PIX_X) + TILE_PIX/2;
  const int16_t off_y = (_chunk->m_y * CHUNK_PIX_Y) + TILE_PIX/2;

  // Render locations into the background image
  for (uint32_t i = 0; i < _chunk->m_nBuildings; ++i) {
    struct Building_t* building = _chunk->m_buildings[i];
    if (building->m_type != kNoBuilding && building->m_image[1]) {
      pd->graphics->drawBitmap(building->m_image[1], building->m_pix_x - off_x, building->m_pix_y - off_y, kBitmapUnflipped);
    }
  }

  pd->graphics->popContext();

  for (uint32_t zoom = 2; zoom < ZOOM_LEVELS; ++zoom) {
    pd->graphics->pushContext(_chunk->m_bkgImage[zoom]);
    pd->graphics->drawScaledBitmap(_chunk->m_bkgImage[1], 0, 0, (float)zoom, (float)zoom);
    pd->graphics->popContext();
  }

}

void generateSpriteSetup(struct Chunk_t* _chunk) {
  for (uint32_t zoom = 1; zoom < ZOOM_LEVELS; ++zoom) {
    if (_chunk->m_bkgImage[zoom] == NULL) _chunk->m_bkgImage[zoom] = pd->graphics->newBitmap(CHUNK_PIX_X*zoom, CHUNK_PIX_Y*zoom, kColorClear);
    // Not enough RAM for this :(
    //if (_chunk->m_bkgImage2[zoom] == NULL) _chunk->m_bkgImage2[zoom] = pd->graphics->newBitmap(CHUNK_PIX_X*zoom, CHUNK_PIX_Y*zoom, kColorClear);
    // ...
    if (_chunk->m_bkgSprite[zoom] == NULL) _chunk->m_bkgSprite[zoom] = pd->sprite->newSprite();
    PDRect bound = {.x = 0, .y = 0, .width = CHUNK_PIX_X*zoom, .height = CHUNK_PIX_Y*zoom};
    pd->sprite->setBounds(_chunk->m_bkgSprite[zoom], bound);
    pd->sprite->setImage(_chunk->m_bkgSprite[zoom], _chunk->m_bkgImage[zoom], kBitmapUnflipped);
    pd->sprite->moveTo(_chunk->m_bkgSprite[zoom], (CHUNK_PIX_X*_chunk->m_x + CHUNK_PIX_X/2.0)*zoom, (CHUNK_PIX_Y*_chunk->m_y + CHUNK_PIX_Y/2.0)*zoom);
    pd->sprite->setZIndex(_chunk->m_bkgSprite[zoom], -1);
  }
}

void setChunkBackgrounds() {
  for (uint16_t y = 0; y < WORLD_CHUNKS_Y; ++y) {
    for (uint16_t x = 0; x < WORLD_CHUNKS_X; ++x) {
      struct Chunk_t* chunk = getChunk_noCheck(x, y);
      generateSpriteSetup(chunk);
      renderChunkBackgroundImage(chunk);
    }
  }
}

void resetWorld() {
  memset(m_tiles, 0, SIZE_GENERATE);
  m_deserialiseIndexWorld = 0;
}

void initWorld() {
  m_tiles = pd->system->realloc(NULL, SIZE_GENERATE);
  pd->system->logToConsole("malloc: for world %i", SIZE_GENERATE/1024);
}

void serialiseWorld(struct json_encoder* je) {
  je->addTableMember(je, "world", 5);
  je->startArray(je);

  for (uint32_t i = 0; i < TOT_TILES; ++i) {
    je->addArrayMember(je);
    je->startTable(je);
    je->addTableMember(je, "tile", 4);
    je->writeInt(je, m_tiles[i].m_tile);
    je->endTable(je);
  }

  je->endArray(je);
}

void deserialiseValueWorld(json_decoder* jd, const char* _key, json_value _value) {
  if (strcmp(_key, "tile") == 0) {
    m_tiles[m_deserialiseIndexWorld].m_tile = json_intValue(_value);
  } else {
    pd->system->error("WORLD DECODE ISSUE, %s", _key);
  }
}

void* deserialiseStructDoneWorld(json_decoder* jd, const char* _name, json_value_type _type) {
  ++m_deserialiseIndexWorld;
  return NULL;
}


bool tileIsObstacle(struct Tile_t* _tile) {
  if (_tile->m_tile >= getSprite16_idx(4,6) && _tile->m_tile <= getSprite16_idx(7,6)) return false; // Water (only the border is obstacle)
  if (_tile->m_tile >= getSprite16_idx(8,2) && _tile->m_tile <= getSprite16_idx(16,2)) return false; // Entry area tiles 
  return _tile->m_tile > FLOOR_TILES;
}

void addObstacles() {
  for (uint32_t x = 0; x < TOT_TILES_X; ++x) {
    for (uint32_t y = 0; y < TOT_TILES_Y; ++y) {
      struct Tile_t* tile = getTile(x, y);
      if (!tileIsObstacle(tile)) {
        continue;
      }

      LCDSprite* obstacle_x1 = pd->sprite->newSprite();
      PDRect bound_x1 = {.x = 0, .y = 0, .width = TILE_PIX, .height = TILE_PIX};
      pd->sprite->setCollideRect(obstacle_x1, bound_x1);
      pd->sprite->moveTo(obstacle_x1, x * TILE_PIX, y * TILE_PIX);


      LCDSprite* obstacle_x2 = pd->sprite->newSprite();
      PDRect bound_x2 = {.x = 0, .y = 0, .width = TILE_PIX*2, .height = TILE_PIX*2};
      pd->sprite->setCollideRect(obstacle_x2, bound_x2);
      pd->sprite->moveTo(obstacle_x2, (x * TILE_PIX)*2, (y * TILE_PIX)*2);


      chunkAddObstacle(getLocation_noCheck(x, y)->m_chunk, obstacle_x1, obstacle_x2);
    }
  }
}

void generate() {
  srand(pd->system->getSecondsSinceEpoch(NULL));

    
  // Worldgen is very basic for now
  for (uint16_t i = 0; i < TOT_TILES; ++i) {
    m_tiles[i].m_tile = rand() % FLOOR_TILES/4;
  } 

  //addLake(1,1, RAND_MAX/2);

  addSpawn();

  addBiome(TOT_TILES_X/2, 0, getSprite16_idx(8,0));
  addBiome(0, TOT_TILES_Y/2, getSprite16_idx(0,1));
  addBiome(TOT_TILES_X/2, TOT_TILES_Y/2, getSprite16_idx(8,1));

  doLakesAndRivers();

  doWetness();



}
