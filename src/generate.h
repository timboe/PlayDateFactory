#pragma once
#include "game.h"
#include "sprite.h"
#include "chunk.h"

struct Tile_t {
  // Persistent
  uint8_t m_tile;
  uint8_t m_wetness;

  // Transient
};

void generate(void);

struct Tile_t* getTile(int32_t _x, int32_t _y);

void renderChunkBackgroundImage(struct Chunk_t* _chunk);

void setChunkBackgrounds(void);

bool tileIsObstacle(struct Tile_t* _tile);

void addObstacles(void);

void initWorld(void);

void resetWorld(void);

void serialiseWorld(struct json_encoder* je);

void deserialiseValueWorld(json_decoder* jd, const char* _key, json_value _value);

void* deserialiseStructDoneWorld(json_decoder* jd, const char* _name, json_value_type _type);