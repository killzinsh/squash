#pragma once

#include "raylib.h"
#include "raymath.h"
#include "../asset_manager.h"

#define TXT_SPACING 0
#define TXT_BUFF (1023+1)

#define TXT_MENU_SIZE 60
#define TXT_COUNTDOWN_SIZE 2000
#define TXT_WIN_SIZE 80
#define TXT_WIN_PAD 60

#define TXT_SCROLL_SIZE 35
#define TXT_SCROLL_VEL 3

enum FontCentering {FONT_LEFT, FONT_CENTER, FONT_RIGHT, FONT_TOP, FONT_MID, FONT_BOT};
enum MenuRotation {OPT_ROT_VERT, OPT_ROT_HOR};

int GetScrollingTextHeight(const char* str, float size);

void RenderScrollingText(const char* str, float yPos);
void RenderOptionMenu(int select, Vector2 pos, char** opt, const int n, enum MenuRotation rot);
void RenderText(const char* str, Vector2 pos, float size, enum FontStyle style, 
                enum FontCentering hor, enum FontCentering vert, Color col);