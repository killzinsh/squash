#include "render_manager.h"

static Rectangle activePlayArea;

void InitRenderer()
{
    InitTextureAssets();
    InitFontAssets();
    
    int yOffset = GetScrollingTextHeight("TEST", TXT_SCROLL_SIZE);
    activePlayArea = (Rectangle) {0.0f, (float)yOffset, WIDTH - 0, HEIGHT - yOffset};
}

Rectangle GetActivePlayArea() { return activePlayArea; }

void RenderStartMenu(int select, int n, char* opt[n])
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
        RenderCountIn(resetTime, SCREEN);
        
        RenderPlayers(p1, p2);

        RenderScore(p1->score, p2->score, curHits);
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
        
        RenderScore(p1->score, p2->score, curHits);
        RenderBorder(activePlayArea);
    }
    EndDrawing();
}

void RenderGameEnd(char* winTxt, int select, int n, char* opt[n])
{
    BeginDrawing();
    {
        ClearBackground(WHITE);
        RenderText(winTxt, Vector2Scale(SCREEN, 0.5), TXT_WIN_SIZE, FONT_BOLD, FONT_CENTER, FONT_MID, BLUE);
        RenderOptionMenu(select, (Vector2){WIDTH/2, HEIGHT/2 + TXT_WIN_PAD}, opt, n, OPT_ROT_HOR);
    }
    EndDrawing();
}

