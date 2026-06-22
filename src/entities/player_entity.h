#pragma once

#include "raylib.h"
#include "raymath.h"

#include "entity.h"
#include "../asset_manager.h"

#define PLAYER_HITBOX_W 120
#define PLAYER_HITBOX_H 170
#define PLAYER_HITBOX (Vector2){PLAYER_HITBOX_W, PLAYER_HITBOX_H}

typedef struct {
    KeyboardKey left;
    KeyboardKey right;
    KeyboardKey up;
    KeyboardKey down;
    KeyboardKey hit;
} ControlLayout;

typedef struct
{
    enum PlayerTypes playerType;
    bool hit;
    int score;
    double hitTime;
    double hitCooldown;
    Entity obj;
    Sprite sprite;
    ControlLayout ctrl;
} Player;

void InitPlayer(Player* p, enum PlayerTypes idPlayer, ControlLayout ctrls, double cooldownTime);
void ResetPlayer(Player* p, Vector2 pos, float spd, double curTime);

void PlayerInputHandler(Player* p, Rectangle playArea, double curTime);