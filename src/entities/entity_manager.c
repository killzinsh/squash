#include "entity_manager.h"

void InitEntities(Player* p1, Player* p2, Ball* ball, AdvertArray* adArr)
{
    InitPlayer(p1, ENTITY_PLAYER1, PLAYER1_CTRLS, PLAYER_HIT_COOLDOWN);
    InitPlayer(p2, ENTITY_PLAYER2, PLAYER2_CTRLS, PLAYER_HIT_COOLDOWN);
    InitBall(ball);
    InitAdverts(adArr, MAX_ADVERT_CNT, AD_SPAWNTIME_COOLDOWN);
}

void ResetEntities(Player* p1, Player* p2, Ball* ball, AdvertArray* adArr, Rectangle playArea)
{
    double curTime = GetTime();
    ResetPlayer(p1, PLAYER1_POS(playArea.width, playArea.height, playArea.y), PLAYER_INIT_SPEED, curTime);
    ResetPlayer(p2, PLAYER2_POS(playArea.width, playArea.height, playArea.y), PLAYER_INIT_SPEED, curTime);
    ResetBall(ball, BALL_POS(playArea.width, playArea.height, playArea.y), INIT_ANGLE_MIN, INIT_ANGLE_MAX, BALL_INIT_SPEED);
    ResetAdverts(adArr, curTime);
}

bool UpdateEntities(Player* p1, Player* p2, int activePlayerIndex, Ball* ball, AdvertArray* adArr, Rectangle playArea)
{
    double curTime = GetTime();

    p1->obj.curHitbox = (Rectangle){p1->obj.pos.x, p1->obj.pos.y, PLAYER_HITBOX_W, PLAYER_HITBOX_H};
    p2->obj.curHitbox = (Rectangle){p2->obj.pos.x, p2->obj.pos.y, PLAYER_HITBOX_W, PLAYER_HITBOX_H};

    PlayerInputHandler(p1, playArea, curTime);
    PlayerInputHandler(p2, playArea, curTime);

    ball->hitType = GetCollisionAgainstWallType(Vector2Add(ball->obj.pos, ball->obj.vel), playArea);
    
    Player* activePlayer;
    if (activePlayerIndex == 0) activePlayer = p1;
    else activePlayer = p2;

    bool isHit = IsBallHit(activePlayer, ball);

    BallKinematics(ball, Vector2Add(activePlayer->obj.pos, (Vector2){PLAYER_HITBOX_W / 2, PLAYER_HITBOX_H / 2}), playArea, isHit);

    AdvertPlayerCollision(adArr, p1->obj.curHitbox, p1->hit);
    AdvertPlayerCollision(adArr, p2->obj.curHitbox, p2->hit);

    if (curTime - adArr->spawnTimer > adArr->spawnTimeCooldown)
    {
        SpawnAdvert(adArr, playArea);
        adArr->spawnTimer = curTime;
    }
}

void UpgradeEntityStats(Player* p1, Player* p2, Ball* ball, int playerSpeedIncrease, int ballSpeedIncrease)
{
    p1->obj.speed += playerSpeedIncrease;
    p2->obj.speed += playerSpeedIncrease;
    UpgradeBall(ball, ballSpeedIncrease);
}

void UpdatePlayerScore(Player* p1, Player* p2, int activePlayerIndex)
{
    Player* activePlayer;
    if (activePlayerIndex == 0) activePlayer = p1;
    else activePlayer = p2;

    activePlayer->score++;
}

bool IsBallHit(Player* activePlayer, Ball* ball)
{


    bool colWithBall = CheckCollisionCircleRec(ball->obj.pos, BALL_R, activePlayer->obj.curHitbox);
    if (colWithBall && activePlayer->hit) 
    {
        ball->hitType = COL_PLAYER_HIT;
        return true;
    }
    return false;
}

void CloseEntities(AdvertArray* adArr)
{
    FreeAdverts(adArr);
}