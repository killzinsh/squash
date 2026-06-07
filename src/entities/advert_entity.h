#pragma once

#include <stdbool.h>

#include "raylib.h"

#include "entity.h"
#include "../asset_manager.h"

#define AD_HOR_BANNER_RATE 50 //50%
#define AD_HOR_BANNER_AREA(xOff,yOff,w,h) \
        ((Rectangle){w/2 - 375 + xOff, h/6*5 + yOff, 750, 100}) //750 100
#define MAX_HOR_BANNER_CNT 1

#define AD_VERT_LEFT_BANNER_RATE 65 //15%
#define AD_VERT_LEFT_BANNER_AREA(xOff,yOff,w,h) \
        ((Rectangle){10 + xOff, 10 + yOff, 200, h - yOff - 80})

#define AD_VERT_RIGHT_BANNER_RATE 80 // 15%
#define AD_VERT_RIGHT_BANNER_AREA(xOff,yOff,w,h) \
        ((Rectangle){w - 210 - xOff, 10 + yOff, 200, h - yOff - 80})
#define MAX_VERT_BANNER_CNT 2

#define AD_RECT_RATE 100 //20%
#define AD_RECT_AREA(xOff,yOff,w,h) \
        ((Rectangle){25 + xOff, 25 + yOff, w - 50 - xOff, h - 50 - yOff})
#define MAX_SMALL_RECT_CNT 2

#define AD_RANGE_MAX 100
#define MAX_ADVERT_CNT 5

typedef struct Advert {
    Entity obj;
    Sprite closeBox;
    Sprite adImage;
} Advert;

void InitAdverts(Advert* ads[], int n);

bool SpawnAdvert(Advert* ads[], int adCnt, Rectangle playArea);
Advert* CreateAdvert(enum EntityId id, Rectangle adArea);

void FreeAdverts(Advert* ads[], int adCnt);