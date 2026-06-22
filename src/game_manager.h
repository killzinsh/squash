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

#define GAME_TXT {"REPLAY", "MENU"}
#define GAME_TXT_CNT 2

#define MENU_TXT {"MATCH (2 - PLAYER)", "GYM (1 - PLAYER)", "EXIT GAME"}
#define MENU_TXT_CNT 3

typedef struct Game
{
    bool resetBall;
    bool finished;
    int bounces;
    int curHits;
    int curGame;
    double resetStartTime;
} Game;

enum Scene {SCENE_MENU, SCENE_GAME, SCENE_GYM, SCENE_EXIT, SCENE_CNT};
enum MenuOption {MENU_GAME, MENU_GYM, MENU_EXIT, MENU_CNT};
enum GameOption {GAME_REPLAY, GAME_MENU, GAME_CNT};

void CreateGame();
Game InitGame();

void SceneManager(enum Scene initScene);
enum Scene MenuBrowser();
enum Scene MainGame();

void CloseGame();