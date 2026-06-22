#pragma once

#include <stdbool.h>
#include <math.h>

#include "player_entity.h"
#include "ball_entity.h"
#include "advert_entity.h"

#define PLAYER1_POS(screenWidth, screenHeight, offsetY) (Vector2){screenWidth/4*3 - PLAYER_HITBOX_W/2, screenHeight/2 + offsetY - PLAYER_HITBOX_H / 2}
#define PLAYER1_CTRLS (ControlLayout){.left = KEY_J, .right = KEY_L, .up = KEY_I, .down = KEY_K, .hit = KEY_U}
#define PLAYER2_POS(screenWidth, screenHeight, offsetY) (Vector2){screenWidth/4 - PLAYER_HITBOX_W/2, screenHeight/2 + offsetY - PLAYER_HITBOX_H / 2}
#define PLAYER2_CTRLS (ControlLayout){.left = KEY_A, .right = KEY_D, .up = KEY_W, .down = KEY_S, .hit = KEY_E}
#define PLAYER_INIT_SPEED 6
#define PLAYER_HIT_COOLDOWN 0.75f

#define BALL_POS(screenWidth, screenHeight, offsetY) (Vector2){screenWidth/2, screenHeight/2 + offsetY}
#define BALL_INIT_SPEED 8

#define INIT_ANGLE_MIN 0
#define INIT_ANGLE_MAX 360

#define MAX_ADVERT_CNT 5
#define AD_SPAWNTIME_COOLDOWN 5.0f

Game InitEntities(Player* p1, Player* p2, Ball* ball, AdvertArray* adArr);
void ResetEntities(Player* p1, Player* p2, Ball* ball, AdvertArray* adArr, Rectangle playArea);

void UpdateEntities(Player* p1, Player* p2, int activePlayerIndex, Ball* ball, AdvertArray* adArr, Rectangle playArea);
void UpgradeEntityStats(Player* p1, Player* p2, Ball* ball, float playerSpeedIncrease, float ballSpeedIncrease);
void UpdatePlayerScore(Player* p1, Player* p2, int activePlayerIndex);

bool IsBallHit(Player* activePlayer, Ball* ball);

void CloseEntities(AdvertArray* adArr);