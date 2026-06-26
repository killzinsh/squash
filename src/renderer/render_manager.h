#pragma once

#include "text_renderer.h"
#include "entity_renderer.h"
#include "overlay_renderer.h"

#include "../asset_manager.h"
#include "../entities/entity_manager.h"

#include "raylib.h"

#define WIDTH 1000
#define HEIGHT 800
#define SCREEN (Vector2){WIDTH, HEIGHT}

#define PAD_MENU_Y 5
#define PAD_MENU_X 5

void InitRenderer();
Rectangle GetActivePlayArea();

void RenderStartMenu(int select, int n, char* opt[n]);
void RenderGameStart(Player* p1, Player* p2, float resetTime, int curHits);
void RenderGame(Player* p1, Player* p2, Ball* ball, AdvertArray* ads, int curHits);
void RenderGameEnd(char* winTxt, int select, int n, char* opt[n]);