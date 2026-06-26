#include "overlay_renderer.h"

static int curFrame = 0;
static int borderFrameLen;

void RenderCountIn(float resetTime, Vector2 screen)
{
    float t = (float)GetTime() - resetTime;
    char countdownStr[TXT_BUFF];
    snprintf(countdownStr, TXT_BUFF, "%.2f", t);
    RenderText(countdownStr, Vector2Scale(screen, 0.5), TXT_COUNTDOWN_SIZE, FONT_REG, FONT_CENTER, FONT_MID, BLUE);
}

void RenderScore(int p1Score, int p2Score, int curHits)
{
    char scrollBuff[TXT_BUFF];
    snprintf(scrollBuff, TXT_BUFF, "BEST OF 5 GAMES - PURPLE RACKET SCORE: %d - GREEN RACKET SCORE: %d - CURRENT RALLY: %03d - ", 
            p1Score, p2Score, curHits);
        RenderScrollingText(scrollBuff, 0);
}

void ResetBorderAnimation(int frameLen)
{
    borderFrameLen = frameLen;
    curFrame = 0;
}

void RenderBorder(Rectangle playArea) 
{
    float ratio = (float)curFrame/(float)borderFrameLen;
    unsigned char opacity = ExpInterp((float)fmin(ratio, 1.0f), BORDER_ANIM_EXP) * BORDER_OPACITY_MAX;

    Color col = {255, 255, 255, opacity};
    Texture2D borderTexture = *GetBorderTexture();
    
    DrawTexturePro(borderTexture, 
                   (Rectangle){0,0, (float)borderTexture.width, (float)borderTexture.height}, 
                   playArea, (Vector2){0,0}, 0, col);
    
    curFrame++;
}

float ExpInterp(float ratio, float exp)
{
    return ((float)pow(exp, ratio) - 1) / (exp - 1);
}