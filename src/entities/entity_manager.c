#include "entity_manager.h"

Game InitEntities(Player* p1, Player* p2, Ball* ball, AdvertArray* adArr)
{
    InitPlayer(p1, PLAYER_ONE, PLAYER1_CTRLS, PLAYER_HIT_COOLDOWN);
    InitPlayer(p2, PLAYER_TWO, PLAYER2_CTRLS, PLAYER_HIT_COOLDOWN);
    InitBall(ball);
    InitAdverts(adArr, MAX_ADVERT_CNT, AD_SPAWNTIME_COOLDOWN);

    return (Game){.resetBall = true, .finished = false, 
                 .bounces = 0, .curHits = 0, .curGame = 0,
                 .resetStartTime = GetTime()};
}

void ResetEntities(Player* p1, Player* p2, Ball* ball, AdvertArray* adArr, Game* game, Rectangle playArea)
{
    double curTime = GetTime();
    ResetPlayer(p1, PLAYER1_POS(playArea.width, playArea.height, playArea.y), PLAYER_INIT_SPEED, curTime);
    ResetPlayer(p2, PLAYER2_POS(playArea.width, playArea.height, playArea.y), PLAYER_INIT_SPEED, curTime);
    ResetBall(ball, BALL_POS(playArea.width, playArea.height, playArea.y), INIT_ANGLE_MIN, INIT_ANGLE_MAX, BALL_INIT_SPEED);
    ResetAdverts(adArr, curTime);

    game->curHits = 0;
    game->bounces = 0;
    game->resetBall = true;
    game->resetStartTime = curTime;
}

void UpdateEntities(Player* p1, Player* p2, int activePlayerIndex, Ball* ball, AdvertArray* adArr, Rectangle playArea)
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

    ClearAdvertSelection(adArr);
    AdvertPlayerCollision(adArr, p1->obj.curHitbox, p1->hit);
    AdvertPlayerCollision(adArr, p2->obj.curHitbox, p2->hit);

    if (curTime - adArr->spawnTimer > adArr->spawnTimeCooldown)
    {
        SpawnAdvert(adArr, playArea);
        adArr->spawnTimer = curTime;
    }
}

void UpgradeEntityStats(Player* p1, Player* p2, Ball* ball, float playerSpeedIncrease, float ballSpeedIncrease)
{
    p1->obj.speed += playerSpeedIncrease;
    p2->obj.speed += playerSpeedIncrease;
    UpgradeBall(ball, ballSpeedIncrease);
}

void UpdateScore(Player* p1, Player* p2, int activePlayerIndex, Game* game)
{
    Player* activePlayer;
    if (activePlayerIndex == 0) activePlayer = p1;
    else activePlayer = p2;

    activePlayer->score += game->curHits;
    game->curGame++;
}

bool IsBallHit(Player* activePlayer, Ball* ball)
{
    bool colWithBall = CheckCollisionCircleRec(ball->obj.pos, BALL_R, activePlayer->obj.curHitbox);
    if (colWithBall && activePlayer->hit) 
    {
        ball->hitType = COL_PLAYER_HIT;
        AssetsPlaySound(SFX_RACKET);

        return true;
    }
    return false;
}

void CloseEntities(AdvertArray* adArr)
{
    FreeAdverts(adArr);
}