#pragma once

#include "raylib.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

enum EntityId {ENTITY_PLAYER1, ENTITY_PLAYER2, ENTITY_BALL, 
               ENTITY_AD_HOR_BANNER, ENTITY_AD_VERT_BANNER, 
               ENTITY_AD_RECT, ENTITY_CNT};

typedef struct Entity {
    enum EntityId id;
    Vector2 pos;
    Vector2 vel;
    float speed;
    Rectangle curHitbox;
} Entity;

typedef struct Sprite {
    int active;
    double animTime;
    Texture2D* texture;
} Sprite;