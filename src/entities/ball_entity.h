#pragma once

#include "raylib.h"
#include "raymath.h"

#include "entity.h"
#include "../asset_manager.h"

#define BALL_R 20

enum BallWallColType {COL_NOHIT, COL_LHIT, COL_RHIT, COL_UHIT, COL_DHIT};

typedef struct
{
    Entity obj;
    Sprite sprite;
    enum BallWallColType wallHitType;
} Ball;

void InitBall(Ball* ball);
void InitBallPosition(Ball* b, Vector2 pos, float minAng, float maxAng, float spd);

int BallFrameCnt(Ball* ball, Rectangle playArea, const int bounceCnt);
bool BallKinematics(Ball* b, Vector2 pCenter, Rectangle playArea, bool pHit);

Vector2 GetBallCollisionAgainstPlayArea(Vector2 futurePos, Rectangle playArea);
enum BallWallColType GetCollisionAgainstWallType(Vector2 futurePos, Rectangle playArea);
