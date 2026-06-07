#pragma once

#include <stdbool.h>
#include <math.h>

#include "entity.h"
#include "advert_entity.h"
#include "../asset_manager.h"

#include "raylib.h"
#include "raymath.h"

#define PLAYER_HITBOX_W 120
#define PLAYER_HITBOX_H 170
#define PLAYER_HITBOX (Vector2){PLAYER_HITBOX_W, PLAYER_HITBOX_H}
#define PLAYER_HIT_COOLDOWN 0.75f

#define BALL_R 20

enum BallWallColType {COL_NOHIT, COL_LHIT, COL_RHIT, COL_UHIT, COL_DHIT};

typedef struct {
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
    Sprite sprite;
    ControlLayout ctrl;
} Player;

typedef struct
{
    Entity obj;
    Sprite sprite;
    enum BallWallColType wallHitType;
} Ball;

void InitPlayer(Player* p, enum EntityId id, ControlLayout ctrls, double curTime);
void InitPlayerPosition(Player* p, Vector2 pos, float spd);
void InitBall(Ball* ball);
void InitBallPosition(Ball* b, Vector2 pos, float minAng, float maxAng, float spd);

void PlayerInputHandler(Player* p, Rectangle playArea, double curTime);

int BallFrameCnt(Ball* ball, Rectangle playArea, const int bounceCnt);
bool BallKinematics(Ball* b, Vector2 pCenter, Rectangle playArea, bool pHit);
Vector2 GetBallCollisionAgainstPlayArea(Vector2 futurePos, Rectangle playArea);
void SetCollisionAgainstWallType(Ball* ball, Rectangle playArea);
