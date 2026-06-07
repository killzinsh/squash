#include "entity_manager.h"

void InitPlayer(Player* p, enum EntityId id, ControlLayout ctrls, double curTime)
{
    p->obj.id = id;
    p->ctrl = ctrls;
    p->score = 0;
    p->hitTime = curTime;
    p->sprite.texture = GetEntityTextures(id);
}

void InitPlayerPosition(Player* p, Vector2 pos, float spd)
{
    p->obj.speed = spd;
    p->obj.pos = pos;
    p->obj.vel = (Vector2){0,0};
    p->hit = 0;
}

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

void PlayerInputHandler(Player* p, Rectangle playArea, double curTime)
{   
    p->obj.vel = (Vector2){0, 0};
    if (IsKeyDown(p->ctrl.left)) p->obj.vel = Vector2Add(p->obj.vel, (Vector2){-1, 0});
    if (IsKeyDown(p->ctrl.right)) p->obj.vel = Vector2Add(p->obj.vel, (Vector2){1, 0});
    if (IsKeyDown(p->ctrl.up)) p->obj.vel = Vector2Add(p->obj.vel, (Vector2){0, -1});
    if (IsKeyDown(p->ctrl.down)) p->obj.vel = Vector2Add(p->obj.vel, (Vector2){0, 1});
    
    p->obj.vel = Vector2Scale(p->obj.vel, p->obj.speed);
    Vector2 tmpSum = Vector2Add(p->obj.vel, p->obj.pos);
    
    if (tmpSum.x >= playArea.x && 
        tmpSum.x <= playArea.x + playArea.width - PLAYER_HITBOX_W)
        p->obj.pos.x = tmpSum.x;
    
    else if (tmpSum.x >= playArea.x)
        p->obj.pos.x = fmin(playArea.x + playArea.width - PLAYER_HITBOX_W, tmpSum.x);
    
    else p->obj.pos.x = fmax(playArea.x, tmpSum.x);
    
    if (tmpSum.y >= playArea.y && 
        tmpSum.y <= playArea.y + playArea.height - PLAYER_HITBOX_H)
        p->obj.pos.y = tmpSum.y;
    else if (tmpSum.y >= playArea.y)
        p->obj.pos.y = fmin(playArea.y + playArea.height - PLAYER_HITBOX_H, tmpSum.y);
    else p->obj.pos.y = fmax(playArea.y, tmpSum.y);
    
    if (IsKeyPressed(p->ctrl.hit) && curTime - p->hitTime >= PLAYER_HIT_COOLDOWN)
    {      
        p->hit = true;
        p->hitTime = curTime;
    }
        
    else p->hit = false;
    
    p->obj.vel = Vector2Scale(p->obj.vel, 1/p->obj.speed);
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

void SetCollisionAgainstWallType(Ball* ball, Rectangle playArea)
{
    ball->wallHitType = COL_NOHIT;
    Vector2 futurePos = Vector2Add(ball->obj.vel, ball->obj.pos);
    
    if (futurePos.y < playArea.y + BALL_R)
        ball->wallHitType = COL_UHIT;
    else if (futurePos.y > playArea.y + playArea.height - BALL_R)
        ball->wallHitType = COL_DHIT;
    else if (futurePos.x < playArea.x + BALL_R)
        ball->wallHitType = COL_LHIT;
    else if (futurePos.x > playArea.x + playArea.width - BALL_R)
        ball->wallHitType = COL_RHIT;
} 