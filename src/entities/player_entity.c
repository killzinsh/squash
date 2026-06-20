#include "player_entity.h"

void InitPlayer(Player* p, enum PlayerTypes idPlayer, ControlLayout ctrls, double cooldownTime)
{
    p->playerType = idPlayer;
    p->obj.id = ENTITY_PLAYER;
    p->ctrl = ctrls;
    p->score = 0;
    p->hitCooldown = cooldownTime;
    p->sprite.textures = GetPlayerTexture(idPlayer);
}

void ResetPlayer(Player* p, Vector2 pos, float spd, double curTime)
{
    p->obj.speed = spd;
    p->obj.pos = pos;
    p->obj.vel = (Vector2){0,0};
    p->hit = 0;
    p->hitTime = curTime;
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
        p->obj.pos.x = (float)fmin(playArea.x + playArea.width - PLAYER_HITBOX_W, tmpSum.x);
    
    else p->obj.pos.x = (float)fmax(playArea.x, tmpSum.x);
    
    if (tmpSum.y >= playArea.y && 
        tmpSum.y <= playArea.y + playArea.height - PLAYER_HITBOX_H)
        p->obj.pos.y = tmpSum.y;
    else if (tmpSum.y >= playArea.y)
        p->obj.pos.y = (float)fmin(playArea.y + playArea.height - PLAYER_HITBOX_H, tmpSum.y);
    else p->obj.pos.y = (float)fmax(playArea.y, tmpSum.y);
    
    if (IsKeyPressed(p->ctrl.hit) && curTime - p->hitTime >= p->hitCooldown)
    {      
        p->hit = true;
        p->hitTime = curTime;
    }
        
    else p->hit = false;
    
    p->obj.vel = Vector2Scale(p->obj.vel, 1/p->obj.speed);
}
