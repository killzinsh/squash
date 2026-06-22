#pragma once

#include "raylib.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

enum EntityId {ENTITY_PLAYER, ENTITY_BALL, ENTITY_AD, ENTITY_CNT};
enum PlayerTypes {PLAYER_ONE, PLAYER_TWO, PLAYER_CNT};
enum AdTypes {AD_HOR, AD_VERT_LEFT, AD_VERT_RIGHT, AD_RECT, AD_TYPE_CNT};

typedef struct Entity {
    enum EntityId id;
    Vector2 pos;
    Vector2 vel;
    float speed;
    Rectangle curHitbox;
} Entity;

typedef struct {
    int cnt;
    Texture2D* textures;
} TextureArray;

typedef struct Sprite {
    int active;
    double animTime;
    TextureArray textures;
} Sprite;

typedef struct
{
    bool resetBall;
    bool finished;
    int bounces;
    int curHits;
    int curGame;
    double resetStartTime;
} Game;