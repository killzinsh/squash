#include "entity_renderer.h"

void RenderPlayers(Player* p1, Player* p2)
{
    //DrawRectangle(p[0].obj.pos.x, p[0].obj.pos.y, PLAYER_HITBOX_W, PLAYER_HITBOX_H, (Color){0,0,0,123});
    RenderPlayerTexture(p1, PLAYER_HITBOX);   
    
    //DrawRectangle(p[1].obj.pos.x, p[1].obj.pos.y, PLAYER_HITBOX_W, PLAYER_HITBOX_H, (Color){0,0,0,123});
    RenderPlayerTexture(p2, PLAYER_HITBOX);
}

void RenderPlayerTexture (Player* p, Vector2 hitbox)
{   
    float height = SPRITE_PLAYER_H*SPRITE_PLAYER_RATIO;
    
    float rot = SPRITE_PLAYER_ROT_H*p->obj.vel.x;
    float vOffset = 0;
    if (p->obj.vel.y == SPRITE_PLAYER_ROT_DOWN) 
    {    
        rot += 180;
        vOffset = hitbox.y;
    }
    
    Rectangle src = {0, 0, SPRITE_PLAYER_W, SPRITE_PLAYER_H};
    Rectangle dest = {p->obj.pos.x + hitbox.x/2, p->obj.pos.y + vOffset, hitbox.x, height};
 
    if (p->hit == true)
    {
        p->sprite.active = SPRITE_PLAYER_HIT;
        p->sprite.animTime = GetTime();
    }
    
    else if (GetTime() - p->sprite.animTime > PLAYER_ANIM_LEN)
    {
        p->sprite.active = SPRITE_PLAYER_NOHIT;
    }
    
    if (IsTextureValid(p->sprite.textures.textures[p->sprite.active]) == false)
    {
        fprintf(stderr, "[ERROR]: Player texture invalid!\n");
        return;
    }
    
    DrawTexturePro(p->sprite.textures.textures[p->sprite.active], src, dest, (Vector2){hitbox.x/2,0}, rot, WHITE);
}

void RenderBallTexture (Ball* ball)
{
    Vector2 pos = (Vector2){ball->obj.pos.x - BALL_R, ball->obj.pos.y - BALL_R};

    if (IsTextureValid(ball->sprite.textures.textures[ball->sprite.active]) == false)
    {
        fprintf(stderr, "[ERROR]: Ball texture not valid!\n");
        return;
    }
    
    Rectangle src = {0, 0, SPRITE_BALL_W, SPRITE_BALL_H};
    Rectangle dest = {pos.x, pos.y, BALL_R * 2, BALL_R * 2};
    Vector2 origin = {0,0};
    
    switch(ball->hitType)
    {
        case COL_DHIT:
            dest.height /= 2;
            origin.y = -dest.height;
            break;
        case COL_UHIT:
            dest.height /= 2;
            break;
        case COL_LHIT:
            dest.width /= 2;
            break;
        case COL_RHIT:
            dest.width /= 2;
            origin.x = -dest.width;
            break;
        default:
            break;
    }
        
    DrawTexturePro(ball->sprite.textures.textures[ball->sprite.active], src, dest, origin, 0, WHITE);
}

void RenderAds(AdvertArray* adArr)
{
    for (int i = 0; i < adArr->adCnt; i++)
    {
        const Advert* ad = adArr->ads[i];
        if (IsTextureValid(ad->adImage.textures.textures[ad->adImage.active]) == false)
        {
            fprintf(stderr, "[ERROR]: Ad texture not valid!\n");
            continue;
        }
        DrawTexture(ad->adImage.textures.textures[ad->adImage.active], 
                    (int)ad->obj.pos.x, (int)ad->obj.pos.y, WHITE);
            
        Rectangle src = {0, 0, (float)ad->closeBox.textures.textures[ad->closeBox.active].width, 
                               (float)ad->closeBox.textures.textures[ad->closeBox.active].height};
        Rectangle dest = {ad->adImage.textures.textures[ad->closeBox.active].width + ad->obj.pos.x - AD_CLOSE_HITBOX.x, 
                          ad->obj.pos.y, 
                          AD_CLOSE_HITBOX.x, 
                          AD_CLOSE_HITBOX.y};
        Vector2 origin = {0,0};
    
        //DrawRectangle(ads[i]->obj.pos.x, ads[i]->obj.pos.y, ads[i]->adImage.texture[ads[i]->adImage.active].width, SPRITE_CLOSE_BUTTON_H, BLACK);
        DrawTexturePro(ad->closeBox.textures.textures[ad->closeBox.active], src, dest, origin, 0, WHITE);
    }
}
