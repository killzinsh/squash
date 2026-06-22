#pragma once

#include <stdbool.h>

#include "raylib.h"

#include "entity.h"
#include "../asset_manager.h"

#define AD_CLOSE_HITBOX (Vector2){40, 40}
#define AD_HOVER_OVER_HITBOX_FALSE 0
#define AD_HOVER_OVER_HITBOX_TRUE 1

#define AD_HOR_BANNER_AREA(xOff,yOff,w,h) \
        ((Rectangle){50, yOff + h - 140, xOff + w - 100, 130}) //750 100
#define AD_HOR_BANNER_CNT 1

#define AD_VERT_LEFT_BANNER_AREA(xOff,yOff,w,h) \
        ((Rectangle){10 + xOff, 10 + yOff, 200, h - 80})
#define AD_VERT_LEFT_BANNER_CNT 1

#define AD_VERT_RIGHT_BANNER_AREA(xOff,yOff,w,h) \
        ((Rectangle){w - 210 - xOff, 10 + yOff, 200, h - 80})
#define AD_VERT_RIGHT_BANNER_CNT 1

#define AD_RECT_AREA(xOff,yOff,w,h) \
        ((Rectangle){140, 10 + yOff, xOff + w - 280, h - 150 + yOff})
#define AD_RECT_CNT 2

typedef struct {
    enum AdTypes adType;
    Entity obj;
    bool selected;
    Sprite closeBox;
    Sprite adImage;
} Advert;

typedef struct {
    int adCnt;
    int maxAdCnt;
    double spawnTimer;
    double spawnTimeCooldown;
    Advert** ads;
} AdvertArray;

void InitAdverts(AdvertArray* adArr, int maxCnt, double cooldownTime);
void ResetAdverts(AdvertArray* adArr, double curTime);

bool SpawnAdvert(AdvertArray* adArr, Rectangle playArea);
Advert* CreateAdvert(enum AdTypes adId, Rectangle adArea);

void ClearAdvertSelection(AdvertArray* adArr);
void AdvertPlayerCollision(AdvertArray* adArr, Rectangle pHitbox, bool isHit);
void ReorderAdArray(AdvertArray* adArr);

void FreeAdverts(AdvertArray* adArr);