#pragma once

#include "raylib.h"

enum EntityId {ENTITY_PLAYER1 = 0, ENTITY_PLAYER2 = 1, ENTITY_BALL, 
               ENTITY_AD_HOR_BANNER, ENTITY_AD_VERT_BANNER, 
               ENTITY_AD_SMALL_RECT, ENTITY_AD_BIG_RECT, ENTITY_CNT};

typedef struct Entity {
    enum EntityId id;
    Vector2 pos;
    Vector2 vel;
    float speed;
} Entity;

typedef struct Sprite {
    int active;
    double animTime;
    Texture2D* texture;
} Sprite;