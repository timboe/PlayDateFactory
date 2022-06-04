#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"
#include "game.h"
#include "sprite.h"
#include "sound.h"
#include "cargo.h"
#include "location.h"
#include "chunk.h"
#include "player.h"
#include "ui.h"
#include "building.h"
#include "io.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif

static void init(void) {
  initSprite();
  initCargo();
  initChunk();
  initLocation();
  initPlayer();
  initiUI();
  initGame();
  initBuilding();
  initSound();
}

static void deinit(void) {
}

int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, uint32_t arg) {
  switch (event) {
    case kEventInit:;
      #ifdef DEV
      playdate->system->logToConsole("EH: init");
      #endif
      setPDPtr(playdate);
      init();
      playdate->display->setRefreshRate(TICK_FREQUENCY);
      playdate->system->setUpdateCallback(gameLoop, NULL);
      break;
    case kEventTerminate:; case kEventLock:; case kEventLowPower:;
      #ifdef DEV
      playdate->system->logToConsole("EH: terminate/lock/low-p, %i", event);
      #endif
      save();
      if (event == kEventTerminate) deinit();
      break;
    case kEventUnlock:;
      #ifdef DEV
      playdate->system->logToConsole("EH: unlock");
      #endif
      break;
    case kEventPause:;
      #ifdef DEV
      playdate->system->logToConsole("EH: pause");
      #endif
      save();
      break;
    case kEventResume:;
      #ifdef DEV
      playdate->system->logToConsole("EH: resume");
      #endif
      break;
    case kEventKeyPressed:;
      #ifdef DEV
      playdate->system->logToConsole("EH: pressed %i", arg);
      #endif
      break;
    case kEventKeyReleased:;
      #ifdef DEV
      playdate->system->logToConsole("EH: released %i", arg);
      #endif
      break;
    default:
      #ifdef DEV
      playdate->system->logToConsole("EH: unknown event %i with arg %i", event, arg);
      #endif
  }
  
  return 0;
}