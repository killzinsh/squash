#pragma once

#include "raylib.h"
#include "raymath.h"

#include "text_renderer.h"
#include "../asset_manager.h"

#define BORDER_ANIM_EXP 2
#define BORDER_OPACITY_MAX 255

void RenderCountIn(float resetTime, Vector2 screen);

void RenderScore(int p1Score, int p2Score, int curHits);

void RenderBorder(Rectangle playArea);
void ResetBorderAnimation(int frameLen);
float ExpInterp(float ratio, float exp);