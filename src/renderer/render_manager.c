#include "render_manager.h"
#include "../game_manager.h"

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

void RenderGame(Player* p, Ball* ball, Advert* ads[], int adCnt, Game* game, int select, const char** opt, int n, enum RenderGameState state)
{
    BeginDrawing();
    {
        ClearBackground(WHITE);
        if (state == STATE_START)
        {
            float t = (GetTime() - game->resetStartTime);
            char countdownStr[TXT_BUFF];
            snprintf(countdownStr, TXT_BUFF, "%.2f", t);
                
            RenderText(countdownStr, (Vector2){WIDTH/2, HEIGHT/2}, TXT_COUNTDOWN_SIZE, FONT_REG, FONT_CENTER, FONT_MID, BLUE);
        }
        
        if(state == STATE_GAME)
        {
            RenderBallTexture(ball);
        }
    
        //DrawRectangle(p[0].obj.pos.x, p[0].obj.pos.y, PLAYER_HITBOX_W, PLAYER_HITBOX_H, (Color){0,0,0,123});
        RenderPlayerTexture(&p[0], PLAYER_HITBOX);
            
        //DrawRectangle(p[1].obj.pos.x, p[1].obj.pos.y, PLAYER_HITBOX_W, PLAYER_HITBOX_H, (Color){0,0,0,123});
        RenderPlayerTexture(&p[1], PLAYER_HITBOX);

        char scrollBuff[TXT_BUFF_EXT];
        snprintf(scrollBuff, TXT_BUFF_EXT, "BEST OF 5 GAMES - PURPLE RACKET SCORE: %d - GREEN RACKET SCORE: %d - CURRENT RALLY: %03d - ", p[0].score, p[1].score, game->curHits);
        RenderScrollingText(scrollBuff, TXT_SCROLL_SIZE, 0, TXT_SCROLL_VEL);
        
        if (state == STATE_END)
        {
            char winBuff[TXT_BUFF];
            if (p[0].score > p[1].score) snprintf(winBuff, TXT_BUFF, "PLAYER %d WON!", 1);
            else snprintf(winBuff, TXT_BUFF, "PLAYER %d WON!", 2);
            
            RenderText(winBuff, Vector2Scale(SCREEN, 0.5), TXT_WIN_SIZE, FONT_BOLD, FONT_CENTER, FONT_MID, BLUE);
            
            RenderOptionMenu(select, (Vector2){WIDTH/2, HEIGHT/2 + TXT_WIN_PAD}, opt, n, OPT_ROT_HOR);
        }
        
        if (state == STATE_GAME)
        {
            RenderAds(ads, adCnt);
            float ratio = (float)curFrame/(float)borderFrameLen; 
            RenderBorder(ExpInterp(fmin(ratio, 1.0f), BORDER_ANIM_EXP) * BORDER_OPACITY_MAX);
        }
        
        curFrame++;
    }
    EndDrawing();
}

void SetBallSprite(Ball* ball)
{
    ball->sprite.active = 0;
}

void RenderBallReset(Ball* ball, int frameLen)
{
    borderFrameLen = frameLen;
    curFrame = 0;
    ball->sprite.active = 0;
}

void UpdateBorderAnim(int frameLen)
{
    borderFrameLen = frameLen;
    curFrame = 0;
}

void UpdateBallSprite(Ball* ball) 
{   
    ball->sprite.active = fmin(ball->sprite.active + 1, BALL_TEXTURE_CNT - 1); 
}

void RenderPlayerTexture (Player* p, Vector2 hitbox)
{   
    float height = SPRITE_PLAYER_H*SPRITE_PLAYER_RATIO;
    
    float rot = SPRITE_PLAYER_ROT_H*p->obj.vel.x;
    float vOffset = 0;
    if (p->obj.vel.y == SPRITE_PLAYER_ROT_DOWN) 
    {    
        rot += 180;
        vOffset = hitbox.y;
    }
    
    Rectangle src = {0, 0, SPRITE_PLAYER_W, SPRITE_PLAYER_H};
    Rectangle dest = {p->obj.pos.x + hitbox.x/2, p->obj.pos.y + vOffset, hitbox.x, height};
 
    if (p->hit == true)
    {
        p->sprite.active = SPRITE_PLAYER_HIT;
        p->sprite.animTime = GetTime();
    }
    
    else if (GetTime() - p->sprite.animTime > PLAYER_ANIM_LEN)
    {
        p->sprite.active = SPRITE_PLAYER_NOHIT;
    }
    
    if (IsTextureValid(p->sprite.texture[p->sprite.active]) == false)
    {
        fprintf(stderr, "[ERROR]: Player texture invalid!\n");
        return;
    }
    
    DrawTexturePro(p->sprite.texture[p->sprite.active], src, dest, (Vector2){hitbox.x/2,0}, rot, WHITE);
}

void RenderBallTexture (Ball* ball)
{
    Vector2 pos = (Vector2){ball->obj.pos.x - BALL_R, ball->obj.pos.y - BALL_R};

    if (IsTextureValid(ball->sprite.texture[ball->sprite.active]) == false)
    {
        fprintf(stderr, "[ERROR]: Ball texture not valid!\n");
        return;
    }
    
    Rectangle src = {0, 0, SPRITE_BALL_W, SPRITE_BALL_H};
    Rectangle dest = {pos.x, pos.y, BALL_R * 2, BALL_R * 2};
    Vector2 origin = {0,0};
    
    switch(ball->wallHitType)
    {
        case COL_DHIT:
            dest.height /= 2;
            origin.y = -dest.height;
            break;
        case COL_UHIT:
            dest.height /= 2;
            break;
        case COL_LHIT:
            dest.width /= 2;
            break;
        case COL_RHIT:
            dest.width /= 2;
            origin.x = -dest.width;
            break;
    }
        
    DrawTexturePro(ball->sprite.texture[ball->sprite.active], src, dest, origin, 0, WHITE);
}

void RenderAds(Advert* ads[], int adCnt)
{
    for (int i = 0; i < adCnt; i++)
    {
        if (IsTextureValid(ads[i]->adImage.texture[ads[i]->adImage.active]) == false)
        {
            fprintf(stderr, "[ERROR]: Ad texture not valid!\n");
            continue;
        }
        DrawTexture(ads[i]->adImage.texture[ads[i]->adImage.active], 
                    ads[i]->obj.pos.x, 
                    ads[i]->obj.pos.y, WHITE);
    }
}

void RenderBorder(int opacity) 
{
    Color col = {255, 255, 255, opacity};
    Texture2D borderTexture = *GetBorderTexture();
    
    DrawTexturePro(borderTexture, (Rectangle){0,0, borderTexture. width, borderTexture.height}, activePlayArea, (Vector2){0,0}, 0, col);
}

float ExpInterp(float ratio, float exp)
{
    return (pow(exp, ratio) - 1) / (exp - 1);
}