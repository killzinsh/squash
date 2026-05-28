#include "entity_manager.h"

void InitPlayer(Player* p, enum EntityId id, ControlLayout ctrls, double curTime)
{
    p->obj.id = id;
    p->ctrl = ctrls;
    p->score = 0;
    p->hitTime = curTime;
    p->sprites = GetEntityTextures(id);
}

void InitPlayerPosition(Player* p, Vector2 pos, float spd)
{
    p->obj.speed = spd;
    p->obj.pos = pos;
    p->obj.vel = (Vector2){0,0};
    p->hit = 0;
}

void InitBall(Entity* ball)
{
    ball->id = ENTITY_BALL;
}

void InitBallPosition(Entity* b, Vector2 pos, float minAng, float maxAng, float spd)
{
    b->pos = pos;
    b->speed = spd;
    float startAngle = DEG2RAD * GetRandomValue(minAng, maxAng);
    b->vel = Vector2Scale((Vector2){cos(startAngle), sin(startAngle)}, b->speed);
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

int BallFrameCnt(Entity* ball, Rectangle playArea, const int bounceCnt)
{
    int bounce = 0;
    int frameCnt = 0;
    
    Vector2 tmpVel = ball->vel;
    Vector2 tmpPos = ball->pos;
    
    while (bounce <= bounceCnt)
    {
        if (Vector2Add(tmpPos, tmpVel).y < playArea.y + BALL_R ||
            Vector2Add(tmpPos, tmpVel).y > playArea.y + playArea.height - BALL_R)
        {
            tmpVel.y *= -1;
            bounce++;
        }
    
    if (Vector2Add(tmpPos, tmpVel).x < playArea.x + BALL_R ||
        Vector2Add(tmpPos, tmpVel).x > playArea.x + playArea.width - BALL_R)
    {
        tmpVel.x *= -1;
        bounce++;
    }
        
        tmpPos = Vector2Add(tmpPos, tmpVel);
        frameCnt++;
    }
    
    return frameCnt;
}

bool BallKinematics(Entity* b, Vector2 pCenter, Rectangle playArea, bool pHit)
{
    bool bounced = false;
    b->vel = Vector2Normalize(b->vel);
    if (pHit)
    {
        b->vel = Vector2Normalize(Vector2Subtract(b->pos, pCenter));
        if (b->pos.y > pCenter.y) b->vel.y *= -1;
    }
    b->vel = Vector2Scale(b->vel, b->speed);
    
    if (Vector2Add(b->pos, b->vel).y < playArea.y + BALL_R ||
        Vector2Add(b->pos, b->vel).y > playArea.y + playArea.height - BALL_R)
    {
        b->vel.y *= -1;
        bounced = true;
    }
    
    if (Vector2Add(b->pos, b->vel).x < playArea.x + BALL_R ||
        Vector2Add(b->pos, b->vel).x > playArea.x + playArea.width - BALL_R)
    {
        b->vel.x *= -1;
        bounced = true;
    }
    
    b->pos = Vector2Add(b->pos, b->vel);
    return bounced;
}