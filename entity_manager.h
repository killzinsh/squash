#pragma once

#include <stdbool.h>
#include <math.h>

#include "raylib.h"
#include "raymath.h"
#include "asset_manager.h"

#define PLAYER_HITBOX_W 120
#define PLAYER_HITBOX_H 170
#define PLAYER_HITBOX (Vector2){PLAYER_HITBOX_W, PLAYER_HITBOX_H}
#define PLAYER_HIT_COOLDOWN 0.75f

#define BALL_R 20

enum EntityId {ENTITY_PLAYER1 = 0, ENTITY_PLAYER2 = 1, ENTITY_BALL, ENT_CNT};

typedef struct {
    enum EntityId id;
    Vector2 pos;
    Vector2 vel;
    float speed;
} Entity;

typedef struct
{
    KeyboardKey left;
    KeyboardKey right;
    KeyboardKey up;
    KeyboardKey down;
    KeyboardKey hit;
    
} ControlLayout;

typedef struct
{
    bool hit;
    unsigned score;
    double hitTime;
    Entity obj;
    Texture2D* sprites;
    ControlLayout ctrl;
} Player;

void InitPlayer(Player* p, enum EntityId id, ControlLayout ctrls, double curTime);
void InitPlayerPosition(Player* p, Vector2 pos, float spd);
void InitBall(Entity* ball);
void InitBallPosition(Entity* b, Vector2 pos, float minAng, float maxAng, float spd);

void PlayerInputHandler(Player* p, Rectangle playArea, double curTime);
int BallFrameCnt(Entity* ball, Rectangle playArea, const int bounceCnt);
bool BallKinematics(Entity* b, Vector2 pCenter, Rectangle playArea, bool pHit);
