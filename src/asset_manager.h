#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#define PLAYER1_RACKET {"assets/sprites/racket_g_nohit.png", "assets/sprites/racket_g_hit.png"}
#define PLAYER2_RACKET {"assets/sprites/racket_p_nohit.png", "assets/sprites/racket_p_hit.png"}
#define PLAYER_TEXTURE_CNT 2

#define BALL_TEXTURES {"assets/sprites/ball_blue.png", "assets/sprites/ball_red.png", "assets/sprites/ball_yellow_1.png", "assets/sprites/ball_yellow_2.png"}
#define BALL_TEXTURE_CNT 4

#define AD_TEXTURES_HOR_BANNER {"assets/overlays/ads/hor_banner1", "assets/overlays/ads/hor_banner2"}
#define AD_TEXTURE_HOR_BANNER_CNT 2

#define WALL_SOUNDS {"assets/sounds/wall01.wav", "assets/sounds/wall02.wav", "assets/sounds/wall03.wav"}
#define WALL_SOUNDS_CNT 3
#define RACKETHIT_SOUNDS {"assets/sounds/racket01.wav", "assets/sounds/racket02.wav", "assets/sounds/racket03.wav"}
#define RACKETHIT_SOUNDS_CNT 3

#define FONT_PATHS {"assets/fonts/AvenirRegular.ttf", "assets/fonts/AvenirBlack.ttf", "assets/fonts/AvenirBlackItalic.ttf"}
#define FONT_LOAD_SIZE 240

#define BORDER_FILE "assets/overlays/border.png"

enum EntityId;
enum FontStyle {FONT_REG, FONT_BOLD, FONT_BOLD_ITALIC, FONT_STYLE_CNT};
enum SoundType {SFX_WALL, SFX_RACKET, SFX_CNT};

void InitAudioAssets();
void InitTextureAssets();
void InitFontAssets();

void AssetsPlaySound(enum SoundType soundType);

Font GetFontByStyle(enum FontStyle style);
Texture2D* GetEntityTextures(enum EntityId id);
Texture2D* GetBorderTexture();

void CloseAssets();