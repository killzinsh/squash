#pragma once

#include "raylib.h"

#define AD_HOR_BANNER_RATE 50
#define MAX_HOR_BANNER_CNT 1

#define AD_VERT_BANNER_RATE 30
#define MAX_VERT_BANNER_CNT 2

#define AD_SMALL_RECT_RATE 15
#define MAX_SMALL_RECT_CNT 2

#define AD_BIG_RECT_RATE 5
#define MAX_BIG_RECT_CNT 2

#define AD_RANGE_MAX (AD_HOR_BANNER_RATE + AD_VERT_BANNER_RATE + AD_SMALL_RECT_RATE + AD_BIG_RECT_RATE)

typedef struct Advert Advert;

void InitAdverts(Advert* ads[], int adCnt);

void SpawnAdvert(Advert* ads[], int adCnt, Rectangle playArea);
Advert* CreateAdvert(Rectangle playArea);
