#include "asset_manager.h"
#include "entity_manager.h"

static Texture2D p1Textures[PLAYER_TEXTURE_CNT];
static Texture2D p2Textures[PLAYER_TEXTURE_CNT];
static Texture2D ballTextures[BALL_TEXTURE_CNT];
static Texture2D adTexturesHorBanner[AD_TEXTURE_HOR_BANNER_CNT];

static Texture2D border;

static Sound wallSfx[WALL_SOUNDS_CNT];
static Sound racketHitSfx[WALL_SOUNDS_CNT];

static Font fonts[FONT_STYLE_CNT];

void InitAudioAssets()
{
    InitAudioDevice();
    if (IsAudioDeviceReady() == false)
    {
        fprintf(stderr, "[ERROR]: Failed to init audio device!\n");
    }
    else
    {
        fprintf(stdout, "[INFO]: Audio device intialized!\n");
        
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
}

void InitTextureAssets()
{
    const char* p1TexturePath[PLAYER_TEXTURE_CNT] = PLAYER1_RACKET;
    const char* p2TexturePath[PLAYER_TEXTURE_CNT] = PLAYER2_RACKET;
    for (int i = 0; i < PLAYER_TEXTURE_CNT; i++)
        p1Textures[i] = LoadTexture(p1TexturePath[i]);
    for (int i = 0; i < PLAYER_TEXTURE_CNT; i++)
        p2Textures[i] = LoadTexture(p2TexturePath[i]);
    
    const char* ballTexturePath[BALL_TEXTURE_CNT] = BALL_TEXTURES;
    for (int i = 0; i < BALL_TEXTURE_CNT; i++)
    {
        ballTextures[i] = LoadTexture(ballTexturePath[i]);
        if (IsTextureValid(ballTextures[i]) == false)
            fprintf(stderr, "[ERROR]: Failed to load: %s\n", ballTexturePath[i]);
    }

    const char* adTexturePath[AD_TEXTURE_HOR_BANNER_CNT] = AD_TEXTURES_HOR_BANNER;
    for (int i = 0; i < AD_TEXTURE_HOR_BANNER_CNT; i++)
    {
        adTexturesHorBanner[i] = LoadTexture(adTexturePath[i]);
    } 
    
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

Texture2D* GetEntityTextures(enum EntityId id)
{
    switch(id)
    {
        case ENTITY_PLAYER1:
            return p1Textures;
        case ENTITY_PLAYER2:
            return p2Textures;
        case ENTITY_BALL:
            return ballTextures;
        case ENTITY_AD_HOR_BANNER:
            return adTexturesHorBanner;
        default:
            fprintf(stderr, "[ERROR]: Unknown entity id for texture!\n");
            return NULL;
    }
}

Texture2D* GetBorderTexture() { return &border; }

void CloseAssets()
{
    for (int i = 0; i < WALL_SOUNDS_CNT; i++)
        if(IsSoundValid(wallSfx[i])) UnloadSound(wallSfx[i]);
    for (int i = 0; i < RACKETHIT_SOUNDS_CNT; i++)
        if(IsSoundValid(racketHitSfx[i])) UnloadSound(racketHitSfx[i]);
    
    for (int i = 0; i < FONT_STYLE_CNT; i++)
        if (IsFontValid(fonts[i])) UnloadFont(fonts[i]);
    
    for (int i = 0; i < PLAYER_TEXTURE_CNT; i++)
        if(IsTextureValid(p1Textures[i])) UnloadTexture(p1Textures[i]);
    for (int i = 0; i < PLAYER_TEXTURE_CNT; i++)
        if(IsTextureValid(p2Textures[i])) UnloadTexture(p2Textures[i]);
    
    for (int i = 0; i < AD_TEXTURE_HOR_BANNER_CNT; i++)
        if (IsTextureValid(adTexturesHorBanner[i])) UnloadTexture(adTexturesHorBanner[i]);

    for (int i = 0; i < BALL_TEXTURE_CNT; i++)
        if (IsTextureValid(ballTextures[i])) UnloadTexture(ballTextures[i]);
    
    if (IsTextureValid(border)) UnloadTexture(border);
    
    CloseAudioDevice();
}