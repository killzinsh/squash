#include "render_manager.h"
#include "game_manager.h"

static int curFrame = 0;
static int borderFrameLen;

static Rectangle activePlayArea;

void InitRenderer()
{
    InitTextureAssets();
    InitFontAssets();
    
    int yOffset = GetScrollingTextHeight("TEST", TXT_SCROLL_SIZE);
    activePlayArea = (Rectangle) {0, yOffset, WIDTH - 0, HEIGHT - yOffset};
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

void RenderGame(Player* p, Ball* ball, Game* game, int select, const char** opt, int n, enum RenderGameState state)
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
            float ratio = (float)curFrame/(float)borderFrameLen; 
            RenderBorder(ExpInterp(fmin(ratio, 1.0f), BORDER_ANIM_EXP) * BORDER_OPACITY_MAX);
        }
        
        curFrame++;
    }
    EndDrawing();
}

void RenderOptionMenu(int select, Vector2 pos, const char** opt, int n, enum MenuRotation rot)
{
    Color txtColor[n];
    for (int i = 0; i < n; i++) txtColor[i] = BLACK;
    
    enum FontStyle fStyle[n];
    for (int i = 0; i < n; i++) fStyle[i] = FONT_REG;
    
    txtColor[select] = BLUE;
    fStyle[select] = FONT_BOLD;
    
    Vector2 totMes = {.x = 0, .y = 0};
    for (int i = 0; i < n; i++)
    {
        totMes = Vector2Add(totMes, MeasureTextEx(GetFontByStyle(fStyle[i]), opt[i], TXT_MENU_SIZE, TXT_SPACING));
    }
    
    totMes.x += PAD_MENU_X * (n-1);
    totMes.y += PAD_MENU_Y * (n-1); 
    
    if (rot == OPT_ROT_VERT)
    {
        int posY = pos.y - totMes.y/2;
        for (int i = 0; i < n; i++)
        {
            RenderText(opt[i], (Vector2){pos.x, posY}, TXT_MENU_SIZE, fStyle[i], FONT_CENTER, FONT_TOP, txtColor[i]);
            
            posY += MeasureTextEx(GetFontByStyle(fStyle[i]), opt[i], TXT_MENU_SIZE, TXT_SPACING).y;
            
            posY += PAD_MENU_Y;
        }
    }
    
    else if (rot == OPT_ROT_HOR)
    {
        int posX = pos.x - totMes.x/2;
        for (int i = 0; i < n; i++)
        {
            RenderText(opt[i], (Vector2){posX, pos.y}, TXT_MENU_SIZE, fStyle[i], FONT_LEFT, FONT_MID, txtColor[i]);
            
            posX += MeasureTextEx(GetFontByStyle(fStyle[i]), opt[i], TXT_MENU_SIZE, TXT_SPACING).x;
            
            posX += PAD_MENU_X;
        }
    }
}

int GetScrollingTextHeight(const char* str, float size)
{
    Vector2 dimn = MeasureTextEx(GetFontByStyle(FONT_BOLD_ITALIC), str, size, TXT_SPACING);
    return dimn.y;
}

void RenderScrollingText(const char* str, float size, int yPos, float vel)
{
    static float firstPos = WIDTH;
    
    Vector2 dimn = MeasureTextEx(GetFontByStyle(FONT_BOLD_ITALIC), str, size, TXT_SPACING);
    if (firstPos <= 0 - dimn.x)
        firstPos = 0;
        
    DrawRectangle(0, yPos, WIDTH, dimn.y, BLACK);
    
    RenderText(str, (Vector2){firstPos, yPos}, size, FONT_BOLD_ITALIC, FONT_LEFT, FONT_TOP, WHITE);
    RenderText(str, (Vector2){firstPos + dimn.x, yPos}, size, FONT_BOLD_ITALIC, FONT_LEFT, FONT_TOP, WHITE);
    
    firstPos -= vel;
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

void RenderText(const char* str, Vector2 pos, float size, enum FontStyle style, 
                enum FontCentering hor, enum FontCentering vert, Color col)
{
    Font fontRender = GetFontByStyle(style);
    
    Vector2 dimn = MeasureTextEx(fontRender, str, size, TXT_SPACING);
    Vector2 renderPos;
    
    switch(vert)
    {
        case FONT_TOP:
            renderPos.y = pos.y;
            break;
        case FONT_MID:
            renderPos.y = pos.y - dimn.y/2;
            break;
        case FONT_BOT:
            renderPos.y = pos.y - dimn.y;
            break;
        default:
            fprintf(stderr, "[ERROR]: Font vertical centering unrecognized!\n");
            return;
    }
        
    switch(hor)
    {
        case FONT_LEFT:
            renderPos.x = pos.x;
            break;
        case FONT_CENTER:
            renderPos.x = pos.x - dimn.x/2;
            break;
        case FONT_RIGHT:
            renderPos.x = pos.x - dimn.x;
            break;
        default:
            fprintf(stderr, "[ERROR]: Font horizontal centering unrecognized!\n");
            return;
    }
    
    DrawTextEx(fontRender, str, renderPos, size, TXT_SPACING, col);
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
            break;
        case COL_UHIT:
            dest.height /= 2;
            break;
        case COL_LHIT:
            dest.width /= 2;
            break;
        case COL_RHIT:
            dest.width /= 2;
            break;
    }
        
    DrawTexturePro(ball->sprite.texture[ball->sprite.active], src, dest, origin, 0, WHITE);
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