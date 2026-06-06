#pragma once

#include <stdbool.h>
#include <math.h>

#include "advert_entity.h"
#include "../asset_manager.h"

#include "raylib.h"
#include "raymath.h"

#define PLAYER_HITBOX_W 120
#define PLAYER_HITBOX_H 170
#define PLAYER_HITBOX (Vector2){PLAYER_HITBOX_W, PLAYER_HITBOX_H}
#define PLAYER_HIT_COOLDOWN 0.75f

#define BALL_R 20

enum EntityId {ENTITY_PLAYER1 = 0, ENTITY_PLAYER2 = 1, ENTITY_BALL, ENTITY_AD, ENTITY_CNT};
enum BallWallColType {COL_NOHIT, COL_LHIT, COL_RHIT, COL_UHIT, COL_DHIT};
enum AdSize {AD_HOR_BANNER, AD_VERT_BANNER, AD_SMALL_BOX, AD_BIG_BOX, AD_CNT};

typedef struct {
    enum EntityId id;
    Vector2 pos;
    Vector2 vel;
    float speed;
} Entity;

typedef struct {
    int active;
    double animTime;
    Texture2D* texture;
} Sprite;

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
    Entity obj;
    Sprite sprite;
    ControlLayout ctrl;
} Player;

typedef struct
{
    Entity obj;
    Sprite sprite;
    enum BallWallColType wallHitType;
} Ball;

typedef struct
{
    Entity obj;
    Sprite closeBox;
    Sprite adImage;
} Advert;

void InitPlayer(Player* p, enum EntityId id, ControlLayout ctrls, double curTime);
void InitPlayerPosition(Player* p, Vector2 pos, float spd);
void InitBall(Ball* ball);
void InitBallPosition(Ball* b, Vector2 pos, float minAng, float maxAng, float spd);
void InitAdverts(Advert* ads[], int adCnt);

Advert* CreateAdvert(enum AdSize adSize, Rectangle playArea);

void PlayerInputHandler(Player* p, Rectangle playArea, double curTime);

int BallFrameCnt(Ball* ball, Rectangle playArea, const int bounceCnt);
bool BallKinematics(Ball* b, Vector2 pCenter, Rectangle playArea, bool pHit);
Vector2 GetBallCollisionAgainstPlayArea(Vector2 futurePos, Rectangle playArea);
void SetCollisionAgainstWallType(Ball* ball, Rectangle playArea);
