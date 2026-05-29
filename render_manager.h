#pragma once

#include "asset_manager.h"
#include "entity_manager.h"

#include "raylib.h"
#include "raymath.h"

#define WIDTH 1000
#define HEIGHT 800
#define SCREEN (Vector2){WIDTH, HEIGHT}

#define PAD_MENU_Y 5
#define PAD_MENU_X 5

#define TXT_SPACING 0
#define TXT_BUFF (31+1)
#define TXT_BUFF_EXT (1023+1)

#define TXT_MENU_SIZE 60
#define TXT_COUNTDOWN_SIZE 2000
#define TXT_WIN_SIZE 80
#define TXT_WIN_PAD 60

#define TXT_SCROLL_SIZE 35
#define TXT_SCROLL_VEL 3

#define SPRITE_PLAYER_W 177
#define SPRITE_PLAYER_H 495
#define SPRITE_PLAYER_RATIO (PLAYER_HITBOX_W / (float)SPRITE_PLAYER_W)

#define SPRITE_PLAYER_ROT_H 7
#define SPRITE_PLAYER_ROT_DOWN 1

#define SPRITE_BALL_W 500
#define SPRITE_BALL_H 500

#define PLAYER_ANIM_LEN 0.1f

#define BORDER_ANIM_EXP 5
#define BORDER_OPACITY_MAX 255

typedef struct Game Game;

enum FontCentering {FONT_LEFT, FONT_CENTER, FONT_RIGHT, FONT_TOP, FONT_MID, FONT_BOT};

enum MenuRotation {OPT_ROT_VERT, OPT_ROT_HOR};
enum RenderGameState {STATE_START, STATE_GAME, STATE_END};

void InitRenderer();
Rectangle GetActivePlayArea();

void RenderMenu(int select, const char** opt, int n);
void RenderGame(Player* p, Entity* ball, Game* game, int select, const char** opt, int n, enum RenderGameState state);
void RenderOptionMenu(int select, Vector2 pos, const char** opt, int n, enum MenuRotation rot);

int GetScrollingTextHeight(const char* str, float size);
void RenderScrollingText(const char* str, float size, int yPos, float vel);

void RenderBallReset(int frameLen);
void UpdateBorderAnim(int frameLen);
void UpdateBallSprite();

void RenderText(const char* str, Vector2 pos, float size, enum FontStyle style, 
                enum FontCentering hor, enum FontCentering vert, Color col);
void RenderPlayerTexture (const Player* p, Vector2 hitbox);
void RenderBallTexture (const Entity* ball, int hits);
void RenderBorder(int opacity);

float ExpInterp(float ratio, float exp);