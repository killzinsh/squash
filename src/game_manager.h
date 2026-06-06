#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"

#include "render_manager.h"
#include "asset_manager.h"
#include "entity_manager.h"

#define TITLE "SQUASH!"

#define FPS 60

#define PLAYER1_POS(offsetY) (Vector2){WIDTH/4*3 - PLAYER_HITBOX_W/2, HEIGHT/2 + offsetY - SPRITE_PLAYER_RATIO*SPRITE_PLAYER_H / 2}
#define PLAYER1_CTRLS (ControlLayout){.left = KEY_J, .right = KEY_L, .up = KEY_I, .down = KEY_K, .hit = KEY_U}
#define PLAYER2_POS(offsetY) (Vector2){WIDTH/4 - PLAYER_HITBOX_W/2, HEIGHT/2 + offsetY - SPRITE_PLAYER_RATIO*SPRITE_PLAYER_H / 2}
#define PLAYER2_CTRLS (ControlLayout){.left = KEY_A, .right = KEY_D, .up = KEY_W, .down = KEY_S, .hit = KEY_E}
#define PLAYER_INIT_SPEED 6

#define BALL_X (WIDTH/2)
#define BALL_Y(offsetY) (HEIGHT/2 + offsetY)
#define BALL_INIT_SPEED 8

#define INIT_ANGLE_MIN 0
#define INIT_ANGLE_MAX 360
#define MIN_HIT_DIFF 20

#define BALL_BOUNCE_CNT 3
#define SPEED_INCREASE_THRESHOLD 5
#define SPEED_PLAYER_INCREASE 0.25f
#define SPEED_MAX_INCREASE 4

#define MAX_ADVERT_CNT 5

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
    unsigned bounces;
    unsigned curHits;
    unsigned curGame;
    double resetStartTime;
} Game;

enum Scene {SCENE_MENU, SCENE_GAME, SCENE_GYM, SCENE_EXIT, SCENE_CNT};
enum MenuOption {MENU_GAME, MENU_GYM, MENU_EXIT, MENU_CNT};
enum GameOption {GAME_REPLAY, GAME_MENU, GAME_CNT};

void CreateGame();
Game InitGame(Player* p, Ball* ball, Advert* ads[], int adCnt, Rectangle playArea, enum Scene scene);

void SceneManager(Player* p, Ball* ball, enum Scene initScene);
enum Scene MenuBrowser();
enum Scene MainGame(Player* p, Ball* ball);

void CloseGame();