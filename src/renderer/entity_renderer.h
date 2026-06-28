#pragma once

#include "raylib.h"
#include "raymath.h"

#include "../entities/player_entity.h"
#include "../entities/ball_entity.h"
#include "../entities/advert_entity.h"


#define SPRITE_PLAYER_NOHIT 0
#define SPRITE_PLAYER_HIT 1
#define SPRITE_ACTIVE_PLAYER_NOHIT 2
#define SPRITE_ACTIVE_PLAYER_HIT 3
#define SPRITE_PLAYER_W 177
#define SPRITE_PLAYER_H 495
#define SPRITE_PLAYER_RATIO (PLAYER_HITBOX_W / (float)SPRITE_PLAYER_W)

#define SPRITE_PLAYER_ROT_H 7
#define SPRITE_PLAYER_ROT_DOWN 1

#define PLAYER_ANIM_LEN 0.1f

#define SPRITE_BALL_W 500
#define SPRITE_BALL_H 500

void RenderPlayers(Player* p1, Player* p2);
void RenderPlayerTexture (Player* p, Vector2 hitbox);
void RenderBallTexture (Ball* ball);
void RenderAds(AdvertArray* adArr);