#include "asset_manager.h"

static TextureArray p1Textures;
static TextureArray p2Textures;
static TextureArray ballTextures;
static TextureArray adTexturesHorBanner;
static TextureArray adTexturesVertBanner;
static TextureArray adTexturesRect;
static Texture2D adTexturesExitButton[AD_TEXTURE_EXIT_BUTTON_CNT];

static Texture2D border;

static Sound wallSfx[WALL_SOUNDS_CNT];
static Sound racketHitSfx[WALL_SOUNDS_CNT];

static Font fonts[FONT_STYLE_CNT];

void InitAudioAssets()
{
    InitAudioDevice();
    if (IsAudioDeviceReady() == false) return;

    const char* wallSfxFiles[] = WALL_SOUNDS;
    for (int i = 0; i < WALL_SOUNDS_CNT; i++)
    {
        wallSfx[i] = LoadSound(wallSfxFiles[i]);
    }
    
    const char* racketHitSfxFiles[] = RACKETHIT_SOUNDS;
    for (int i = 0; i < RACKETHIT_SOUNDS_CNT; i++)
    {
        racketHitSfx[i] = LoadSound(racketHitSfxFiles[i]);
    }
}

void InitTextureAssets()
{
    const char* p1TexturePath[PLAYER_TEXTURE_CNT] = PLAYER1_RACKET;
    p1Textures.cnt = PLAYER_TEXTURE_CNT;
    p1Textures.textures = malloc(sizeof(Texture2D) * PLAYER_TEXTURE_CNT);
    for (int i = 0; i < PLAYER_TEXTURE_CNT; i++)
        p1Textures.textures[i] = LoadTexture(p1TexturePath[i]);

    const char* p2TexturePath[PLAYER_TEXTURE_CNT] = PLAYER2_RACKET;
    p2Textures.cnt = PLAYER_TEXTURE_CNT;
    p2Textures.textures = malloc(sizeof(Texture2D) * PLAYER_TEXTURE_CNT);
    for (int i = 0; i < PLAYER_TEXTURE_CNT; i++)
        p2Textures.textures[i] = LoadTexture(p2TexturePath[i]);
    
    const char* ballTexturePath[BALL_TEXTURE_CNT] = BALL_TEXTURES;
    ballTextures.cnt = BALL_TEXTURE_CNT;
    ballTextures.textures = malloc(sizeof(Texture2D) * BALL_TEXTURE_CNT);
    for (int i = 0; i < BALL_TEXTURE_CNT; i++)
        ballTextures.textures[i] = LoadTexture(ballTexturePath[i]);

    const char* adTextureHorPath[AD_TEXTURE_HOR_BANNER_CNT] = AD_TEXTURES_HOR_BANNER;
    adTexturesHorBanner.cnt = AD_TEXTURE_HOR_BANNER_CNT;
    adTexturesHorBanner.textures = malloc(sizeof(Texture2D) * AD_TEXTURE_HOR_BANNER_CNT);
    for (int i = 0; i < adTexturesHorBanner.cnt; i++)
        adTexturesHorBanner.textures[i] = LoadTexture(adTextureHorPath[i]);
    
    const char* adTextureVertPath[AD_TEXTURE_VERT_BANNER_CNT] = AD_TEXTURES_VERT_BANNER;
    adTexturesVertBanner.cnt = AD_TEXTURE_VERT_BANNER_CNT;
    adTexturesVertBanner.textures = malloc(sizeof(Texture2D) * AD_TEXTURE_VERT_BANNER_CNT);
    for (int i = 0; i < AD_TEXTURE_VERT_BANNER_CNT; i++)
        adTexturesVertBanner.textures[i] = LoadTexture(adTextureVertPath[i]);
    
    const char* adTextureRectPath[AD_TEXTURE_RECT_CNT] = AD_TEXTURES_RECT;
    adTexturesRect.cnt = AD_TEXTURE_RECT_CNT;
    adTexturesRect.textures = malloc(sizeof(Texture2D) * AD_TEXTURE_RECT_CNT);
    for (int i = 0; i < AD_TEXTURE_RECT_CNT; i++)
        adTexturesRect.textures[i] = LoadTexture(adTextureRectPath[i]);
    
    const char* adTextureExitBtnPath[AD_TEXTURE_EXIT_BUTTON_CNT] = AD_TEXTURES_EXIT_BUTTON;
    for (int i = 0; i < AD_TEXTURE_EXIT_BUTTON_CNT; i++)
        adTexturesExitButton[i] = LoadTexture(adTextureExitBtnPath[i]);

    const char* borderPath = BORDER_FILE; 
    border = LoadTexture(borderPath);
    
}

void InitFontAssets()
{
    const char* fontPaths[] = FONT_PATHS;
    for (int i = 0; i < FONT_STYLE_CNT; i++)
        fonts[i] = LoadFontEx(fontPaths[i], FONT_LOAD_SIZE, NULL, 0);
}

void AssetsPlaySound(enum SoundType soundType)
{
    if (IsAudioDeviceReady() == false) return;
    
    switch(soundType)
    {
        case SFX_WALL:
            PlaySound(wallSfx[GetRandomValue(0, WALL_SOUNDS_CNT-1)]);
            break;
        case SFX_RACKET:
            PlaySound(racketHitSfx[GetRandomValue(0, RACKETHIT_SOUNDS_CNT-1)]);
            break;
        default:
            printf("Sound type unrecognized!\n");
    }
}

Font GetFontByStyle(enum FontStyle style)
{
    switch (style)
    {
        case FONT_REG:
            return fonts[FONT_REG];
        case FONT_BOLD:
            return fonts[FONT_BOLD];
        case FONT_BOLD_ITALIC:
            return fonts[FONT_BOLD_ITALIC];
        default:
            fprintf(stderr, "[ERROR]: Unrecognized font style\n");
            return fonts[FONT_REG];
    }
}

TextureArray* GetBallTexture(enum EntityId ballId)
{
    if (ballId == ENTITY_BALL) return &ballTextures;

    fprintf(stderr, "[ERROR]: Could not get ball texture!\n");
    return NULL;
}

TextureArray* GetPlayerTexture(enum PlayerTypes playerType)
{
    switch (playerType)
    {
    case PLAYER_ONE:
        return &p1Textures;
    case PLAYER_TWO:
        return &p2Textures;
    default:
        fprintf(stderr, "[ERROR]: Could not get player texture!\n");
        return NULL;
    }
}

TextureArray* GetAdvertTexture(enum AdTypes adType)
{
    switch (adType)
    {
    case AD_HOR:
        return &adTexturesHorBanner;
    case AD_VERT_LEFT:
        return &adTexturesVertBanner;
    case AD_VERT_RIGHT:
        return &adTexturesVertBanner;
    case AD_RECT:
        return &adTexturesRect;
    default:
        fprintf(stderr, "[ERROR]: Could not get advert texture!\n");
        return NULL;
    }
}

Texture2D* GetBorderTexture() { return &border; }
Texture2D* GetCloseButtonTexture() { return adTexturesExitButton; }

void CloseAssets()
{
    for (int i = 0; i < WALL_SOUNDS_CNT; i++)
        if(IsSoundValid(wallSfx[i])) UnloadSound(wallSfx[i]);
    for (int i = 0; i < RACKETHIT_SOUNDS_CNT; i++)
        if(IsSoundValid(racketHitSfx[i])) UnloadSound(racketHitSfx[i]);
    
    for (int i = 0; i < FONT_STYLE_CNT; i++)
        if (IsFontValid(fonts[i])) UnloadFont(fonts[i]);
    
    for (int i = 0; i < PLAYER_TEXTURE_CNT; i++)
        if(IsTextureValid(p1Textures.textures[i])) 
            UnloadTexture(p1Textures.textures[i]);
    free(p1Textures.textures);

    for (int i = 0; i < PLAYER_TEXTURE_CNT; i++)
        if(IsTextureValid(p2Textures.textures[i])) 
            UnloadTexture(p2Textures.textures[i]);
    free(p2Textures.textures);    

    for (int i = 0; i < BALL_TEXTURE_CNT; i++)
        if (IsTextureValid(ballTextures.textures[i])) 
            UnloadTexture(ballTextures.textures[i]);
    free(ballTextures.textures);

    for (int i = 0; i < AD_TEXTURE_HOR_BANNER_CNT; i++)
        if (IsTextureValid(adTexturesHorBanner.textures[i])) 
            UnloadTexture(adTexturesHorBanner.textures[i]);
    free(adTexturesHorBanner.textures);
    
    for (int i = 0; i < AD_TEXTURE_VERT_BANNER_CNT; i++)
        if (IsTextureValid(adTexturesVertBanner.textures[i])) 
            UnloadTexture(adTexturesVertBanner.textures[i]);
    free(adTexturesVertBanner.textures);

    for (int i = 0; i < AD_TEXTURE_RECT_CNT; i++)
        if (IsTextureValid(adTexturesRect.textures[i])) 
            UnloadTexture(adTexturesRect.textures[i]);
    free(adTexturesRect.textures);

    for (int i = 0; i < AD_TEXTURE_RECT_CNT; i++)
        if (IsTextureValid(adTexturesExitButton[i])) UnloadTexture(adTexturesExitButton[i]);

    if (IsTextureValid(border)) UnloadTexture(border);
    
    CloseAudioDevice();
}