#include "settings.h"
#include "../sprite.h"
#include "../ui.h"
#include "../io.h"
#include "../sound.h"

LCDBitmap* m_pause = NULL;

bool isTitle(int32_t _line);

const char* getLine(int32_t _line);

void checked(void);

void unchecked(void);

void autosave(uint32_t _time);

/// ///

LCDBitmap* getPauseImage() {
  if (m_pause == NULL) m_pause = pd->graphics->newBitmap(DEVICE_PIX_X, DEVICE_PIX_Y, kColorClear);

  pd->graphics->clearBitmap(m_pause, kColorClear);
  int32_t length, width = 0;
  char text[128];

  #define CENTRE (TILE_PIX*6)
  #define Y_SPACE (3*TILE_PIX/2)

  #define X_START TILE_PIX
  #define X_END (11*TILE_PIX - TILE_PIX/2)

  if (getGameMode() == kTitles) return m_pause;

  pd->graphics->pushContext(m_pause);
  pd->graphics->setDrawOffset(TILE_PIX/2, TILE_PIX/2);
  roundedRect(0, DEVICE_PIX_X/2 - TILE_PIX, 9*TILE_PIX, TILE_PIX, kColorBlack);
  roundedRect(TILE_PIX/4, DEVICE_PIX_X/2 - TILE_PIX, 9*TILE_PIX, TILE_PIX, kColorWhite);
  pd->graphics->setDrawOffset(0, 0);

  setRoobert10();

  snprintf(text, 128, "Sell a total of:");
  length = strlen(text);
  width = pd->graphics->getTextWidth(getRoobert10(), text, length, kUTF8Encoding, 0);
  pd->graphics->drawText(text, 128, kASCIIEncoding, CENTRE - width/2, 1*Y_SPACE);

  snprintf(text, 128, "To unlock the next:");
  length = strlen(text);
  width = pd->graphics->getTextWidth(getRoobert10(), text, length, kUTF8Encoding, 0);
  pd->graphics->drawText(text, 128, kASCIIEncoding, CENTRE - width/2, 3*Y_SPACE);

  struct Player_t* p = getPlayer();
  const uint32_t nextLevel = p->m_buildingsUnlockedTo + 1;
  const enum kCargoType cargo = UnlockDecs[ nextLevel ].ofCargo;
  const uint16_t needToSell = UnlockDecs[ nextLevel ].fromSelling;
  const uint16_t haveSold = p->m_soldCargo[ cargo ];

  pd->system->logToConsole("Showing pause menu for unlock # %i", nextLevel);


  snprintf(text, 128, "%i %ss", needToSell, toStringCargoByType(cargo));
  length = strlen(text);
  width = pd->graphics->getTextWidth(getRoobert10(), text, length, kUTF8Encoding, 0);
  pd->graphics->drawText(text, 128, kASCIIEncoding, CENTRE - width/2, 2*Y_SPACE);
  pd->graphics->drawBitmap(getSprite16_byidx( CargoDesc[ cargo ].UIIcon , 1), X_START, 2*Y_SPACE, kBitmapUnflipped);
  pd->graphics->drawBitmap(getSprite16_byidx( CargoDesc[ cargo ].UIIcon , 1), X_END, 2*Y_SPACE, kBitmapFlippedX);

  enum kBuildingType nextBuildingType = UnlockDecs[nextLevel].type;
  enum kUICat nextBuildingUICat = getBuildingTypeCat(nextBuildingType);

  const char* t = toStringHeader(nextBuildingUICat, /*plural*/ false);
  length = strlen(t);
  width = pd->graphics->getTextWidth(getRoobert10(), t, length, kUTF8Encoding, 0);
  pd->graphics->drawText(t, 128, kASCIIEncoding, CENTRE - width/2, 4*Y_SPACE);

  pd->graphics->drawBitmap(getSprite16(11, 13, 1), X_START, 4*Y_SPACE, kBitmapUnflipped);
  pd->graphics->drawBitmap(getSprite16(11, 13, 1), X_END, 4*Y_SPACE, kBitmapFlippedX);

  snprintf(text, 128, "Sold so far: %i", haveSold);
  length = strlen(text);
  width = pd->graphics->getTextWidth(getRoobert10(), text, length, kUTF8Encoding, 0);
  pd->graphics->drawText(text, 128, kASCIIEncoding, CENTRE - width/2, 5*Y_SPACE);

  pd->graphics->drawLine(X_START + TILE_PIX, 3*Y_SPACE - TILE_PIX/2, X_END, 3*Y_SPACE - TILE_PIX/2, 2, kColorBlack);
  pd->graphics->drawLine(X_START + TILE_PIX, 5*Y_SPACE - TILE_PIX/2, X_END, 5*Y_SPACE - TILE_PIX/2, 2, kColorBlack);


  pd->graphics->setDrawOffset(TILE_PIX/2, TILE_PIX*9 + TILE_PIX/2);
  roundedRect(0, DEVICE_PIX_X/2 - TILE_PIX, 4*TILE_PIX, TILE_PIX, kColorBlack);
  roundedRect(TILE_PIX/4, DEVICE_PIX_X/2 - TILE_PIX, 4*TILE_PIX, TILE_PIX, kColorWhite);
  pd->graphics->setDrawOffset(0, 0);

  snprintf(text, 128, "Total Play Time:");
  length = strlen(text);
  width = pd->graphics->getTextWidth(getRoobert10(), text, length, kUTF8Encoding, 0);
  pd->graphics->drawText(text, 128, kASCIIEncoding, CENTRE - width/2, 7*Y_SPACE);

  const uint32_t pt = p->m_playTime / TICK_FREQUENCY;
  snprintf(text, 128, "%ih:%im:%is", (int) pt/3600, (int) (pt%3600)/60, (int) (pt%3600)%60);
  length = strlen(text);
  width = pd->graphics->getTextWidth(getRoobert10(), text, length, kUTF8Encoding, 0);
  pd->graphics->drawText(text, 128, kASCIIEncoding, CENTRE - width/2, 8*Y_SPACE - TILE_PIX/4);


  pd->graphics->popContext();
  return m_pause;
}

void checked() {
  pd->graphics->setDrawMode(kDrawModeCopy);
  pd->graphics->drawBitmap(getSprite16(6, 19, 1), TILE_PIX*16, 0, kBitmapUnflipped);
}

void unchecked() {
  pd->graphics->setDrawMode(kDrawModeCopy);
  pd->graphics->drawBitmap(getSprite16(5, 19, 1), TILE_PIX*16, 0, kBitmapUnflipped);
}

void autosave(uint32_t _time) {
  pd->graphics->setDrawMode(kDrawModeFillBlack);
  switch (_time) {
    case 0: pd->graphics->drawText("OFF", 8, kUTF8Encoding, TILE_PIX*15, 0); break;
    case 5: pd->graphics->drawText("5m", 8, kUTF8Encoding, TILE_PIX*15, 0); break;
    case 10: pd->graphics->drawText("10m", 8, kUTF8Encoding, TILE_PIX*15, 0); break;
    case 15: pd->graphics->drawText("15m", 8, kUTF8Encoding, TILE_PIX*15, 0); break;
    case 30: pd->graphics->drawText("30m", 8, kUTF8Encoding, TILE_PIX*15, 0); break;
  }
}

void doSettings() {
  struct Player_t* p = getPlayer();
  const uint16_t selectedID =  getUIContentID();
  switch (selectedID) {
    case 1: p->m_soundSettings = p->m_soundSettings ^ 1; updateMusic(/*isTitle=*/false); break;
    case 2: p->m_soundSettings = p->m_soundSettings ^ 2; updateSfx(); break;
    case 4: p->m_enableScreenShake = !p->m_enableScreenShake; break;
    case 5: if (p->m_enableTutorial == 255) p->m_enableTutorial = 0; else p->m_enableTutorial = 255; break;
    case 6: p->m_enableConveyorAnimation = !p->m_enableConveyorAnimation; break;
    case 7: switch(p->m_enableAutosave) {
              case 0: p->m_enableAutosave = 5; break;
              case 5: p->m_enableAutosave = 10; break;
              case 10: p->m_enableAutosave = 15; break;
              case 15: p->m_enableAutosave = 30; break;
              case 30: p->m_enableAutosave = 0; break;
            }; break;
    case 8: p->m_enablePickupOnDestroy = !p->m_enablePickupOnDestroy; break;
    case 9: p->m_autoUseConveyorBooster = !p->m_autoUseConveyorBooster; break;
    case 10: p->m_enableDebug = !p->m_enableDebug; break;
    case 12: doIO(kDoSave, /*and then*/ kDoTitle); break;
    case 13: doIO(kDoTitle, /*and then*/ kDoNothing); break;
  }
  redrawMainmenuLine(getMainmenuUIBitmap(selectedID), selectedID);
}

#define MAX_SETTINGS_ROWS_WHICH_MIGHT_CHANGE 11
void redrawAllSettingsMenuLines() {
  for (int32_t i = 0; i < MAX_SETTINGS_ROWS_WHICH_MIGHT_CHANGE; ++i) {
    redrawMainmenuLine(getMainmenuUIBitmap(i), i);
  }
}

void redrawMainmenuLine(LCDBitmap* _bitmap, int32_t _line) {

  setRoobert10();
  pd->graphics->clearBitmap(_bitmap, kColorWhite);
  pd->graphics->pushContext(_bitmap);
  pd->graphics->setDrawMode(kDrawModeCopy);
  
  int32_t width, length;
  if (isTitle(_line)) {
    const char* text = getLine(_line);
    length = strlen(text);
    width = pd->graphics->getTextWidth(getRoobert10(), text, length, kUTF8Encoding, 0);
    pd->graphics->drawText(text, length, kUTF8Encoding, TILE_PIX*9 - width/2, 0);

  } else {
    pd->graphics->drawText("..........................................................................", 75, kASCIIEncoding, TILE_PIX, 0);
    const char* text = getLine(_line);
    length = strlen(text);
    width = pd->graphics->getTextWidth(getRoobert10(), text, length, kUTF8Encoding, 0);
    pd->graphics->fillRect(0, 0, TILE_PIX + width + TILE_PIX/4, TILE_PIX, kColorWhite);
    pd->graphics->drawText(text, length, kUTF8Encoding, TILE_PIX, 0);
  }

  struct Player_t* p = getPlayer();
  switch (_line) {
    case 1: (p->m_soundSettings == 1 || p->m_soundSettings == 3) ? checked() : unchecked(); break;
    case 2: (p->m_soundSettings == 2 || p->m_soundSettings == 3) ? checked() : unchecked(); break;
    case 4: p->m_enableScreenShake ? checked() : unchecked(); break;
    case 5: p->m_enableTutorial != 255 ? checked() : unchecked(); break;
    case 6: p->m_enableConveyorAnimation ? checked() : unchecked(); break;
    case 7: autosave(p->m_enableAutosave); break;
    case 8: p->m_enablePickupOnDestroy ? checked() : unchecked(); break;
    case 9: p->m_autoUseConveyorBooster ? checked() : unchecked(); break;
    case 10: p->m_enableDebug ? checked() : unchecked(); break;
  }

  pd->graphics->popContext();
}

void populateContentMainmenu() {
  for (int32_t i = 0; i < MAX_ROWS; ++i) {
    setUIContentMainMenu(i, isTitle(i));
  }
}

void populateInfoMainmenu() {
}

bool isTitle(int32_t _line) {
  switch (_line) {
    case 0: case 3: case 11: case 14: case 21: case 23: case 29: case 37: return true;
  }
  return false;
}

const char* getLine(int32_t _line) {
  switch (_line) {
    case 0: return "--- Sound Settings ---";
    case 1: return "Music";
    case 2: return "Sound Effects";
    //
    case 3: return "--- Game Settings ---";
    case 4: return "Screen Shake";
    case 5: return "Tutorial Enabled";
    case 6: return "Conveyor Animation";
    case 7: return "Auto Save Time";
    case 8: return "Auto Pickup on Destroy";
    case 9: return "Auto Apply Conveyor Grease";
    case 10: return "Show Debug Information";
    //
    case 11: return "--- Exit Game ---";
    case 12: return "Save & Exit to Title";
    case 13: return "Exit to Title WITHOUT Saving";
    //
    case 14: return "--- Controls ---";
    case 15: return "Inventory/Select/Interact: Ⓐ";
    case 16: return "Back/Cancel: Ⓑ";
    case 17: return "Walk: ✛";
    case 18: return "Run: Hold Ⓑ + ✛";
    case 19: return "Zoom in/out: 🎣";
    case 20: return "Rotate: 🎣 or Hold Ⓑ + ⬆️/➡️/⬇️/⬅️";
    //
    case 21: return "--- Credits ---";
    case 22: return "Factory Farming by Tim Martin";
    //
    case 23: return "-- Music --";
    case 24: return "♬ Dr Tikov: 1985";
    case 25: return "♬ BoxCat Games: B-3";
    case 26: return "♬ Eric Skiff: We're the Resistors";
    case 27: return "♬ RoccoW: Sweet Self Satisfaction";
    case 28: return "♬ RoccoW: Pumped";
    //
    case 29: return "-- Art --";
    case 30: return "Kenney: 1-Bit Pack";
    case 31: return "VectorPixelStar: 1-Bit Patterns";
    case 32: return "Josehzz: Farming Crops";
    case 33: return "ScratchIO: Farming Set";
    case 34: return "Varkalandar: Isometric Rocks";
    case 35: return "Withthelove: Character Sprites";
    case 36: return "DinosoftLab: New (NounProject)";
    //
    case 37: return "-- Fonts --";
    case 38: return "Chester Jenkins: Cooper Hewitt";
    case 39: return "Martin Vacha: Roobert";
    case 40: return "Mediengestaltung: Messing Lettern";
    case 41: return "Nick's Fonts: Coventry Garden";
    //
    case 42: return "-- Sound Effects --";

    // can currently go to 42
  }
  return "???";
}
