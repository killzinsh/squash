#include "entity_manager.h"

void InitEntities(Player* p, Ball* ball, AdvertArray* adArr, double curTime)
{
    InitPlayer(&p[0], ENTITY_PLAYER1, PLAYER1_CTRLS, PLAYER_HIT_COOLDOWN, curTime);
    InitPlayer(&p[1], ENTITY_PLAYER2, PLAYER2_CTRLS, PLAYER_HIT_COOLDOWN, curTime);
    InitBall(ball);
    InitAdverts(adArr, MAX_ADVERT_CNT);
}

void ResetEntities(Player* p, Ball* ball, Rectangle playArea)
{
    InitPlayerPosition(&p[0], PLAYER1_POS(playArea.width, playArea.height, playArea.y), PLAYER_INIT_SPEED);
    InitPlayerPosition(&p[1], PLAYER2_POS(playArea.width, playArea.height, playArea.y), PLAYER_INIT_SPEED);
    InitBallPosition(ball, BALL_POS(playArea.width, playArea.height, playArea.y), INIT_ANGLE_MIN, INIT_ANGLE_MAX, BALL_INIT_SPEED);
}