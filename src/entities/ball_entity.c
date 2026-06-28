#include "ball_entity.h"

void InitBall(Ball* ball)
{
    ball->obj.id = ENTITY_BALL;
    ball->sprite.active = 0;
    ball->sprite.textures = *GetBallTexture(ENTITY_BALL);
}

void ResetBall(Ball* ball, Vector2 pos, int minAng, int maxAng, float spd)
{
    ball->obj.pos = pos;
    ball->obj.speed = spd;
    float startAngle = DEG2RAD * (float)GetRandomValue(minAng, maxAng);
    ball->obj.vel = Vector2Scale((Vector2){(float)cos(startAngle), (float)sin(startAngle)}, ball->obj.speed);
    ball->sprite.active = 0;
}

void UpgradeBall(Ball* ball, float speedIncrease)
{
    ball->obj.speed += speedIncrease;
    ball->sprite.active = MIN(ball->sprite.active + 1, BALL_TEXTURE_CNT - 1); 
}

int BallFrameCnt(Ball* ball, Rectangle playArea, const int bounceCnt)
{
    int bounce = 0;
    int frameCnt = 0;
    
    Vector2 tmpVel = ball->obj.vel;
    Vector2 tmpPos = ball->obj.pos;
    
    while (bounce <= bounceCnt)
    {
        Vector2 react = GetBallCollisionAgainstPlayArea(Vector2Add(tmpPos, tmpVel), playArea);

        tmpVel.y *= react.y;
        tmpVel.x *= react.x;
        if (react.y == -1 || react.x == -1) bounce++;
        
        tmpPos = Vector2Add(tmpPos, tmpVel);
        frameCnt++;
    }
   
    return frameCnt;
}

void BallKinematics(Ball* b, Vector2 pCenter, Rectangle playArea, bool pHit)
{
    b->obj.vel = Vector2Normalize(b->obj.vel);
    if (pHit)
    {
        b->obj.vel = Vector2Normalize(Vector2Subtract(b->obj.pos, pCenter));
        if (b->obj.pos.y > pCenter.y) b->obj.vel.y *= -1;
    }
    b->obj.vel = Vector2Scale(b->obj.vel, b->obj.speed);
    
    Vector2 react = GetBallCollisionAgainstPlayArea(Vector2Add(b->obj.pos, b->obj.vel), playArea);
    b->obj.vel.y *= react.y;
    b->obj.vel.x *= react.x;
    
    b->obj.pos = Vector2Add(b->obj.pos, b->obj.vel);
}

Vector2 GetBallCollisionAgainstPlayArea(Vector2 futurePos, Rectangle playArea)
{
    Vector2 result = {.x = 1, .y = 1};
    
    if (futurePos.y < playArea.y + BALL_R || 
        futurePos.y > playArea.y + playArea.height - BALL_R)
        result.y = -1;
    
    if (futurePos.x < playArea.x + BALL_R ||
        futurePos.x > playArea.x + playArea.width - BALL_R)
        result.x = -1;
    
    return result;
}

enum BallCollisionType GetCollisionAgainstWallType(Vector2 futurePos, Rectangle playArea)
{
    enum BallCollisionType colType = COL_NOHIT;   
    if (futurePos.y < playArea.y + BALL_R)
        colType = COL_UHIT;
    else if (futurePos.y > playArea.y + playArea.height - BALL_R)
        colType = COL_DHIT;
    else if (futurePos.x < playArea.x + BALL_R)
        colType = COL_LHIT;
    else if (futurePos.x > playArea.x + playArea.width - BALL_R)
        colType = COL_RHIT;
    
    if (colType != COL_NOHIT) AssetsPlaySound(SFX_WALL);
    return colType;
} 