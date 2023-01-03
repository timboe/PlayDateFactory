#include <math.h>
#include "render.h"
#include "location.h"
#include "cargo.h"
#include "player.h"
#include "sprite.h"
#include "chunk.h"
#include "io.h"
#include "input.h"
#include "ui.h"
#include "buildings/conveyor.h"

float m_trauma = 0.0f, m_decay = 0.0f;

void chunkAddToRender(struct Chunk_t* _chunk, uint8_t _zoom, bool _includeCargoAndObs);

/// ///

void addTrauma(float _amount) {
  m_trauma += _amount;
  m_trauma *= -1;
  m_decay = _amount;
}

void render() {

  struct Player_t* p = getPlayer();
  const uint8_t zoom = getZoom();

  if (p->m_enableScreenShake && m_decay > 0.0f) {
    m_decay -= TRAUMA_DECAY;
    m_trauma += (m_trauma > 0 ? -m_decay : m_decay);
    pd->display->setOffset(0, m_trauma * TRAUMA_AMPLIFICATION);
  } else {
    pd->display->setOffset(0, 0);
  }

  const float offX = -(p->m_camera_pix_x*zoom - (SCREEN_PIX_X/2));
  const float offY = -(p->m_camera_pix_y*zoom - (SCREEN_PIX_Y/2));

  pd->graphics->setDrawMode(kDrawModeCopy);
  pd->graphics->setDrawOffset(offX, offY);

  if (getFrameCount() % NEAR_TICK_FREQUENCY == 0) {
    pd->sprite->updateAndDrawSprites();
  } else {
    pd->sprite->drawSprites();
  }

  // Draw FPS indicator (dbg only)
  if (p->m_enableDebug || ALWAYS_FPS) {
    pd->system->drawFPS(0, 0);
  }
}

void chunkAddToRender(struct Chunk_t* _chunk, uint8_t _zoom, bool _includeCargoAndObs) {
  if (_chunk->m_bkgSprite[_zoom]) pd->sprite->addSprite(_chunk->m_bkgSprite[_zoom]);
  const bool animOn = getPlayer()->m_enableConveyorAnimation; 
  for (uint32_t i = 0; i < _chunk->m_nBuildingsRender; ++i) {
    struct Building_t* b = _chunk->m_buildingsRender[i];
    if (b->m_sprite[_zoom] && (animOn || b->m_type != kConveyor)) {
      pd->sprite->addSprite(b->m_sprite[_zoom]);
    }
    // Force update the drawing of the current location of the cargo
    if (b->m_type == kConveyor && b->m_location->m_cargo) {
      conveyorLocationUpdate(b, _zoom);
    }
  }
  if (!_includeCargoAndObs) {
    return;
  }
  for (uint32_t i = 0; i < _chunk->m_nCargos; ++i) {
    pd->sprite->addSprite(_chunk->m_cargos[i]->m_sprite[_zoom]);
  }
  for (uint32_t i = 0; i < _chunk->m_nObstacles; ++i) {
    pd->sprite->addSprite(_chunk->m_obstacles[i][_zoom]);
  }
}

void updateRenderList() {
  const enum kGameMode gm = getGameMode();
  if (gm == kMenuCredits) {
    pd->sprite->removeAllSprites();
    addUIToSpriteList();
    return;
  }

  uint8_t zoom = getZoom();
  struct Chunk_t* currentChunk = getCurrentChunk();

  pd->sprite->removeAllSprites();

  struct Player_t* player = getPlayer();
  pd->sprite->addSprite(player->m_sprite[zoom]);
  pd->sprite->addSprite(player->m_blueprint[zoom]);
  pd->sprite->addSprite(player->m_blueprintRadius[zoom]);

  const enum kSaveLoadRequest io = currentIOAction();

  if (io != kDoScreenShot) {
    addUIToSpriteList();
  }

  const bool includeCargoAndObs = (gm < kMenuBuy || gm == kTitles || io == kDoScreenShot);

  chunkAddToRender(currentChunk, zoom, includeCargoAndObs);
  if (getZoom() == 1 && !PRETEND_ZOOMED_IN) {
    for (uint32_t i = 0; i < CHUNK_NEIGHBORS_ALL; ++i) {
      chunkAddToRender(currentChunk->m_neighborsALL[i], zoom, includeCargoAndObs);
    }
  } else {
    switch (getCurrentQuadrant()) {
      case NE:;
        chunkAddToRender(currentChunk->m_neighborsNE[0], zoom, includeCargoAndObs);
        chunkAddToRender(currentChunk->m_neighborsNE[1], zoom, includeCargoAndObs);
        chunkAddToRender(currentChunk->m_neighborsNE[2], zoom, includeCargoAndObs);
        break;
      case SE:;
        chunkAddToRender(currentChunk->m_neighborsSE[0], zoom, includeCargoAndObs);
        chunkAddToRender(currentChunk->m_neighborsSE[1], zoom, includeCargoAndObs);
        chunkAddToRender(currentChunk->m_neighborsSE[2], zoom, includeCargoAndObs);
        break;
      case SW:;
        chunkAddToRender(currentChunk->m_neighborsSW[0], zoom, includeCargoAndObs);
        chunkAddToRender(currentChunk->m_neighborsSW[1], zoom, includeCargoAndObs);
        chunkAddToRender(currentChunk->m_neighborsSW[2], zoom, includeCargoAndObs);
        break;
      case NW:;
        chunkAddToRender(currentChunk->m_neighborsNW[0], zoom, includeCargoAndObs);
        chunkAddToRender(currentChunk->m_neighborsNW[1], zoom, includeCargoAndObs);
        chunkAddToRender(currentChunk->m_neighborsNW[2], zoom, includeCargoAndObs);
        break;
    }
  }
}