#pragma once

#include <stdbool.h>

#include "raylib.h"

#include "entity.h"
#include "../asset_manager.h"

#define AD_HOR_BANNER_RATE 50 //50%
#define AD_HOR_BANNER_AREA(xOff,yOff,w,h) \
        ((Rectangle){50, yOff + h - 140, xOff + w - 100, 130}) //750 100
#define MAX_HOR_BANNER_CNT 1

#define AD_VERT_LEFT_BANNER_RATE 65 //15%
#define AD_VERT_LEFT_BANNER_AREA(xOff,yOff,w,h) \
        ((Rectangle){10 + xOff, 10 + yOff, 200, h - 80})

#define AD_VERT_RIGHT_BANNER_RATE 80 // 15%
#define AD_VERT_RIGHT_BANNER_AREA(xOff,yOff,w,h) \
        ((Rectangle){w - 210 - xOff, 10 + yOff, 200, h - 80})
#define MAX_VERT_BANNER_CNT 2

#define AD_RECT_RATE 100 //20%
#define AD_RECT_AREA(xOff,yOff,w,h) \
        ((Rectangle){140, 10 + yOff, xOff + w - 280, h - 150 + yOff})
#define MAX_SMALL_RECT_CNT 2

#define AD_RANGE_MAX 100

typedef struct {
    Entity obj;
    Sprite closeBox;
    Sprite adImage;
} Advert;

typedef struct {
    int adCnt;
    int maxAdCnt;
    Advert** ads;
} AdvertArray;

void InitAdverts(AdvertArray* adArr, int n);

bool SpawnAdvert(AdvertArray* adArr, Rectangle playArea);
Advert* CreateAdvert(enum EntityId id, Rectangle adArea);

void FreeAdverts(AdvertArray* adArr);