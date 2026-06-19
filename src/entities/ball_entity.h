#pragma once

#include "raylib.h"
#include "raymath.h"

#include "entity.h"
#include "../asset_manager.h"

#define BALL_R 20

enum BallCollisionType {COL_NOHIT, COL_PLAYER_HIT, COL_LHIT, COL_RHIT, COL_UHIT, COL_DHIT};

typedef struct
{
    Entity obj;
    Sprite sprite;
    enum BallCollisionType hitType;
} Ball;

void InitBall(Ball* ball);
void ResetBall(Ball* ball, Vector2 pos, float minAng, float maxAng, float spd);
void UpgradeBall(Ball* ball, int speedIncrease);

int BallFrameCnt(Ball* ball, Rectangle playArea, const int bounceCnt);
void  BallKinematics(Ball* b, Vector2 pCenter, Rectangle playArea, bool pHit);

Vector2 GetBallCollisionAgainstPlayArea(Vector2 futurePos, Rectangle playArea);
enum BallCollisionType GetCollisionAgainstWallType(Vector2 futurePos, Rectangle playArea);
