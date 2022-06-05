#pragma once

#define DEBUG_MODE
#define DEV

#define PRETEND_ZOOMED_IN false

#include <stdio.h>
#include <stdbool.h> 

#include "pd_api.h"
#include "constants.h"

extern PlaydateAPI* pd;

void setPDPtr(PlaydateAPI* _p);

int gameLoop(void* _data);

int getFrameCount(void);

uint16_t getNearTickCount(void);

uint16_t getFarTickCount(void);

uint16_t locToPix(uint16_t _loc);

uint16_t pixToLoc(uint16_t _pix);

void menuOptionsCallbackRestart(void*);

void menuOptionsCallbackLoad(void*);

void menuOptionsCallbackSave(void*);

void queueUpdateRenderList(void);

void initGame(void);

void reset(void);



