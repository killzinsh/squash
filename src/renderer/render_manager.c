#include "render_manager.h"

static int curFrame = 0;
static int borderFrameLen;

static Rectangle activePlayArea;

void InitRenderer()
{
    InitTextureAssets();
    InitFontAssets();
    
    int yOffset = GetScrollingTextHeight("TEST", TXT_SCROLL_SIZE);
    activePlayArea = (Rectangle) {0.0f, (float)yOffset, WIDTH - 0, HEIGHT - yOffset};
}

Rectangle GetActivePlayArea() { return activePlayArea; }

void RenderMenu(int select, const char** opt, int n)
{
    BeginDrawing();
    {
        ClearBackground(WHITE);
        RenderOptionMenu(select, Vector2Scale(SCREEN, 0.5), opt, n, OPT_ROT_VERT);
    }
    EndDrawing();
}

void RenderGameStart(Player* p1, Player* p2, float resetTime, int curHits)
{
    BeginDrawing();
    {
        ClearBackground(WHITE);
        float t = (float)GetTime() - resetTime;
        char countdownStr[TXT_BUFF];
        snprintf(countdownStr, TXT_BUFF, "%.2f", t);

        RenderText(countdownStr, (Vector2){WIDTH/2, HEIGHT/2}, TXT_COUNTDOWN_SIZE, FONT_REG, FONT_CENTER, FONT_MID, BLUE);

        RenderPlayers(p1, p2);

        char scrollBuff[TXT_BUFF_EXT];
        snprintf(scrollBuff, TXT_BUFF_EXT, "BEST OF 5 GAMES - PURPLE RACKET SCORE: %d - GREEN RACKET SCORE: %d - CURRENT RALLY: %03d - ", 
                 p1->score, p2->score, curHits);
        RenderScrollingText(scrollBuff, 0);
    }
    EndDrawing();
}

void RenderGame(Player* p1, Player* p2, Ball* ball, AdvertArray* ads, int curHits)
{
    BeginDrawing();
    {
        ClearBackground(WHITE);
        RenderBallTexture(ball);

        RenderPlayers(p1, p2);

        RenderAds(ads);
        
        char scrollBuff[TXT_BUFF_EXT];
        snprintf(scrollBuff, TXT_BUFF_EXT, "BEST OF 5 GAMES - PURPLE RACKET SCORE: %d - GREEN RACKET SCORE: %d - CURRENT RALLY: %03d - ", 
                 p1->score, p2->score, curHits);
        RenderScrollingText(scrollBuff, 0);

        float ratio = (float)curFrame/(float)borderFrameLen; 
        RenderBorder(ExpInterp((float)fmin(ratio, 1.0f), BORDER_ANIM_EXP) * BORDER_OPACITY_MAX);
        curFrame++; 
    }
    EndDrawing();
}

void RenderGameEnd(Player* p1, Player* p2, int curHits, int select, const char** opt, int n)
{
    BeginDrawing();
    {
        ClearBackground(WHITE);
        RenderPlayers(p1, p2);

        char winBuff[TXT_BUFF];
        if (p1->score > p2->score) snprintf(winBuff, TXT_BUFF, "PLAYER %d WON!", 1);
        else snprintf(winBuff, TXT_BUFF, "PLAYER %d WON!", 2);
            
        RenderText(winBuff, Vector2Scale(SCREEN, 0.5), TXT_WIN_SIZE, FONT_BOLD, FONT_CENTER, FONT_MID, BLUE);
        RenderOptionMenu(select, (Vector2){WIDTH/2, HEIGHT/2 + TXT_WIN_PAD}, opt, n, OPT_ROT_HOR);

        char scrollBuff[TXT_BUFF_EXT];
        snprintf(scrollBuff, TXT_BUFF_EXT, "BEST OF 5 GAMES - PURPLE RACKET SCORE: %d - GREEN RACKET SCORE: %d - CURRENT RALLY: %03d - ", 
                 p1->score, p2->score, curHits);
        RenderScrollingText(scrollBuff, 0);
    }
    EndDrawing();
}

void ResetBorderAnimation(int frameLen)
{
    borderFrameLen = frameLen;
    curFrame = 0;
}

void RenderBorder(int opacity) 
{
    Color col = {255, 255, 255, opacity};
    Texture2D borderTexture = *GetBorderTexture();
    
    DrawTexturePro(borderTexture, 
                   (Rectangle){0,0, (float)borderTexture.width, (float)borderTexture.height}, 
                   activePlayArea, (Vector2){0,0}, 0, col);
}

float ExpInterp(float ratio, float exp)
{
    return (pow(exp, ratio) - 1) / (exp - 1);
}