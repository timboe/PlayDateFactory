#include "sprite.h"
#include "input.h"

LCDBitmap* m_conveyorMasters[2][kDirN] = {NULL}; // For two different speed settings

LCDBitmapTable* m_sheet16;

LCDBitmapTable* m_sheet48;

LCDBitmap* m_bitmap16_zoom[ZOOM_LEVELS][SHEET16_SIZE];

LCDBitmap* m_bitmap48_zoom[ZOOM_LEVELS][SHEET48_SIZE];

LCDFont* m_fontRoobert24;

LCDFont* m_fontRoobert10;

LCDBitmap* loadImageAtPath(const char* _path);

LCDBitmapTable* loadImageTableAtPath(const char* _path);

LCDFont* loadFontAtPath(const char* _path);

void populateResizedSprites(void);

/// ///

LCDBitmap* loadImageAtPath(const char* _path) {
  const char* _outErr = NULL;
  LCDBitmap* _img = pd->graphics->loadBitmap(_path, &_outErr);
  if (_outErr != NULL) {
    pd->system->error("Error loading image at path '%s': %s", _path, _outErr);
  }
  return _img;
}

LCDBitmapTable* loadImageTableAtPath(const char* _path) {
  const char* _outErr = NULL;
  LCDBitmapTable* _table = pd->graphics->loadBitmapTable(_path, &_outErr);
  if (_outErr != NULL) {
    pd->system->error("Error loading image table at path '%s': %s", _path, _outErr);
  }
  return _table;
}

LCDFont* loadFontAtPath(const char* _path) {
  const char* _outErr = NULL;
  LCDFont* _f = pd->graphics->loadFont(_path, &_outErr);
  if (_outErr != NULL) {
    pd->system->error("Error loading font at path '%s': %s", _path, _outErr);
  }
  return _f;
}

LCDBitmap* getSprite16(uint32_t _x, uint32_t _y, uint8_t _zoom) {
  return getSprite16_byidx(SPRITE16_ID(_x, _y), _zoom);
}

LCDBitmap* getSprite16_byidx(uint32_t _idx, uint8_t _zoom) {
  if (_zoom == 1) {
    return pd->graphics->getTableBitmap(m_sheet16, _idx);
  } else if (_zoom < ZOOM_LEVELS) {
    return m_bitmap16_zoom[_zoom][_idx];
  }
  pd->system->error("getSprite16 Error");
  return NULL;
}

LCDBitmap* getSprite48(uint32_t _x, uint32_t _y, uint8_t _zoom) {
  return getSprite48_byidx(SPRITE48_ID(_x, _y), _zoom);
}

LCDBitmap* getSprite48_byidx(uint32_t _idx, uint8_t _zoom) {
  if (_zoom == 1) {
    return pd->graphics->getTableBitmap(m_sheet48, _idx);
  } else if (_zoom < ZOOM_LEVELS) {
    return m_bitmap48_zoom[_zoom][_idx];
  }
  pd->system->error("getSprite48 Error");
  return NULL;
}

// Note: Only works at zoom level 2
void animateConveyor() {
  static int8_t tick = 0;
  tick = (tick + 1) % 8;

  pd->graphics->setDrawMode(kDrawModeCopy);
  for (int32_t i = 0; i < kDirN; ++i) {
    pd->graphics->setDrawMode(kDrawModeInverted);
    pd->graphics->pushContext(m_conveyorMasters[1][i]);
    pd->graphics->drawBitmap(getSprite16(tick, CONV_START_Y + i, 2), 0, 0, kBitmapUnflipped);
    pd->graphics->popContext();

    pd->graphics->setDrawMode(kDrawModeCopy);
    pd->graphics->pushContext(m_conveyorMasters[0][i]);
    pd->graphics->drawBitmap(getSprite16(tick, CONV_START_Y + i, 2), 0, 0, kBitmapUnflipped);
    pd->graphics->popContext();
  }
}

LCDBitmap* getConveyorMaster(enum kDir _dir, uint8_t _speed) {
  switch (_speed) {
    case 1: m_conveyorMasters[0][_dir];
    case 2: m_conveyorMasters[1][_dir];
  }
  return NULL;
}

void setRoobert10() {
  pd->graphics->setFont(m_fontRoobert10);
}

void setRoobert24() {
  pd->graphics->setFont(m_fontRoobert24);
}

LCDFont* getRoobert24() {
  return m_fontRoobert24;
}

void populateResizedSprites() {
  for (uint32_t zoom = 2; zoom < ZOOM_LEVELS; ++zoom) {
    for (uint32_t i = 0; i < SHEET16_SIZE; ++i) {
      LCDBitmap* original = pd->graphics->getTableBitmap(m_sheet16, i);
      m_bitmap16_zoom[zoom][i] = pd->graphics->newBitmap(TILE_PIX*2, TILE_PIX*2, kColorClear);
      pd->graphics->pushContext(m_bitmap16_zoom[zoom][i]);
      pd->graphics->drawScaledBitmap(original, 0, 0, zoom, zoom);
      pd->graphics->popContext();
    }
    for (uint32_t i = 0; i < SHEET48_SIZE; ++i) {
      LCDBitmap* original = pd->graphics->getTableBitmap(m_sheet48, i);
      m_bitmap48_zoom[zoom][i] = pd->graphics->newBitmap(TILE_PIX*3*2, TILE_PIX*3*2, kColorClear);
      pd->graphics->pushContext(m_bitmap48_zoom[zoom][i]);
      pd->graphics->drawScaledBitmap(original, 0, 0, zoom, zoom);
      pd->graphics->popContext();
    }
  }
}

void initSprite() {
  pd->graphics->setDrawMode(kDrawModeCopy);
  m_sheet16 = loadImageTableAtPath("images/sheet16");
  m_sheet48 = loadImageTableAtPath("images/sheet48");
  populateResizedSprites();

  for (int32_t i = 0; i < kDirN; ++i) {
    m_conveyorMasters[0][i] = pd->graphics->copyBitmap(getSprite16(0, CONV_START_Y + i, 2));
    m_conveyorMasters[1][i] = pd->graphics->copyBitmap(getSprite16(0, CONV_START_Y + i, 2));
  }

  m_fontRoobert24 = loadFontAtPath("fonts/Roobert-24-Medium");
  m_fontRoobert10 = loadFontAtPath("fonts/Roobert-10-Bold");
  pd->graphics->setFont(m_fontRoobert24);

}
