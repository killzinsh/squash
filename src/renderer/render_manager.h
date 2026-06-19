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

#define BORDER_ANIM_EXP 5
#define BORDER_OPACITY_MAX 255

void InitRenderer();
Rectangle GetActivePlayArea();

void RenderMenu(int select, const char** opt, int n);
void RenderGameStart(Player* p1, Player* p2, float resetTime, int curHits);
void RenderGame(Player* p1, Player* p2, Ball* ball, AdvertArray* ads, int curHits);
void RenderGameEnd(Player* p1, Player* p2, int curHits, int select, const char** opt, int n);

void ResetBorderAnimation(int frameLen);

void RenderBorder(int opacity);

float ExpInterp(float ratio, float exp);