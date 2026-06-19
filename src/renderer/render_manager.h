#pragma once

#include "text_renderer.h"
#include "entity_renderer.h"

#include "../asset_manager.h"
#include "../entities/entity_manager.h"

#include "raylib.h"
#include "raymath.h"

#define WIDTH 1000
#define HEIGHT 800
#define SCREEN (Vector2){WIDTH, HEIGHT}

#define PAD_MENU_Y 5
#define PAD_MENU_X 5

#define SPRITE_PLAYER_NOHIT 0
#define SPRITE_PLAYER_HIT 1
#define SPRITE_PLAYER_W 177
#define SPRITE_PLAYER_H 495
#define SPRITE_PLAYER_RATIO (PLAYER_HITBOX_W / (float)SPRITE_PLAYER_W)

#define SPRITE_PLAYER_ROT_H 7
#define SPRITE_PLAYER_ROT_DOWN 1

#define SPRITE_BALL_W 500
#define SPRITE_BALL_H 500

#define SPRITE_CLOSE_BUTTON_W 40
#define SPRITE_CLOSE_BUTTON_H 40

#define PLAYER_ANIM_LEN 0.1f

#define BORDER_ANIM_EXP 5
#define BORDER_OPACITY_MAX 255

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct Game Game;

enum RenderGameState {STATE_START, STATE_GAME, STATE_END};

void InitRenderer();
Rectangle GetActivePlayArea();

void RenderMenu(int select, const char** opt, int n);
void RenderGame(Player* p, Ball* ball, AdvertArray* ads, Game* game, int select, const char** opt, int n, enum RenderGameState state);

void RenderBallReset(Ball* ball, int frameLen);
void UpdateBorderAnim(int frameLen);
void UpdateBallSprite(Ball* ball);

void RenderPlayerTexture (Player* p, Vector2 hitbox);
void RenderBallTexture (Ball* ball);
void RenderAds(AdvertArray* adArr);
void RenderBorder(int opacity);

float ExpInterp(float ratio, float exp);