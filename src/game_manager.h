#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"

#include "renderer/render_manager.h"
#include "asset_manager.h"
#include "entities/entity_manager.h"

#define TITLE "SQUASH!"

#define FPS 60

#define MIN_HIT_DIFF 20

#define BALL_BOUNCE_CNT 3
#define SPEED_INCREASE_THRESHOLD 5
#define SPEED_PLAYER_INCREASE 0.25f
#define SPEED_BALL_INCREASE 1.0f
#define SPEED_MAX_INCREASE 4

#define RESET_TIME 2.0f
#define WINNING_SCORE 3

enum Scene {SCENE_MENU, SCENE_GYM, SCENE_GAME, SCENE_P1_WON, SCENE_P2_WON, SCENE_EXIT, SCENE_CNT, SCENE_NOCHANGE};

#define END_MENU_TXT {"REPLAY", "MENU"}
#define END_MENU_SCENES {SCENE_GAME, SCENE_MENU}
#define END_MENU_CNT 2

#define START_MENU_TXT {"MATCH (2 - PLAYER)", "GYM (1 - PLAYER)", "EXIT GAME"}
#define START_MENU_SCENES {SCENE_GAME, SCENE_GYM, SCENE_EXIT}
#define START_MENU_CNT 3

#define MAX_MENU_OPTION_CNT 3

typedef struct 
{
    int optionCnt;
    char* optionTxt[MAX_MENU_OPTION_CNT];
    enum Scene scenes[MAX_MENU_OPTION_CNT];
} MenuOptions;

void CreateGame();

void SceneManager(enum Scene initScene);

enum Scene MenuBrowser(MenuOptions menu);
enum Scene StartMenu();
enum Scene GameOver();
enum Scene MainGame();

void CloseGame();