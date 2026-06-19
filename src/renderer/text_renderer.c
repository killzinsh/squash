#include "text_renderer.h"
#include "render_manager.h"

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

void RenderOptionMenu(int select, Vector2 pos, const char** opt, const int n, enum MenuRotation rot)
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
        float posY = pos.y - totMes.y/2;
        for (int i = 0; i < n; i++)
        {
            RenderText(opt[i], (Vector2){pos.x, posY}, TXT_MENU_SIZE, fStyle[i], FONT_CENTER, FONT_TOP, txtColor[i]);
            
            posY += MeasureTextEx(GetFontByStyle(fStyle[i]), opt[i], TXT_MENU_SIZE, TXT_SPACING).y;
            
            posY += PAD_MENU_Y;
        }
    }
    
    else if (rot == OPT_ROT_HOR)
    {
        float posX = pos.x - totMes.x/2;
        for (int i = 0; i < n; i++)
        {
            RenderText(opt[i], (Vector2){posX, pos.y}, TXT_MENU_SIZE, fStyle[i], FONT_LEFT, FONT_MID, txtColor[i]);
            
            posX += MeasureTextEx(GetFontByStyle(fStyle[i]), opt[i], TXT_MENU_SIZE, TXT_SPACING).x;
            
            posX += PAD_MENU_X;
        }
    }
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