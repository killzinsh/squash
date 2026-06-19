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
    bool hit;
    unsigned score;
    double hitTime;
    double hitCooldown;
    Entity obj;
    Sprite sprite;
    ControlLayout ctrl;
} Player;

void InitPlayer(Player* p, enum EntityId id, ControlLayout ctrls, double cooldownTime, double curTime);
void InitPlayerPosition(Player* p, Vector2 pos, float spd);

void PlayerInputHandler(Player* p, Rectangle playArea, double curTime);