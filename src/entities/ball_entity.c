#include "ball_entity.h"

void InitBall(Ball* ball)
{
    ball->obj.id = ENTITY_BALL;
    ball->sprite.active = 0;
    ball->sprite.texture = GetEntityTextures(ENTITY_BALL);
}

void InitBallPosition(Ball* b, Vector2 pos, float minAng, float maxAng, float spd)
{
    b->obj.pos = pos;
    b->obj.speed = spd;
    float startAngle = DEG2RAD * GetRandomValue(minAng, maxAng);
    b->obj.vel = Vector2Scale((Vector2){cos(startAngle), sin(startAngle)}, b->obj.speed);
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

bool BallKinematics(Ball* b, Vector2 pCenter, Rectangle playArea, bool pHit)
{
    bool bounced = false;
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
    if (react.y == -1 || react.x == -1) bounced = true;
    
    b->obj.pos = Vector2Add(b->obj.pos, b->obj.vel);
    return bounced;
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

enum BallWallColType GetCollisionAgainstWallType(Vector2 futurePos, Rectangle playArea)
{   
    if (futurePos.y < playArea.y + BALL_R)
        return COL_UHIT;
    else if (futurePos.y > playArea.y + playArea.height - BALL_R)
        return COL_DHIT;
    else if (futurePos.x < playArea.x + BALL_R)
        return COL_LHIT;
    else if (futurePos.x > playArea.x + playArea.width - BALL_R)
        return COL_RHIT;
    
    return COL_NOHIT;
} 