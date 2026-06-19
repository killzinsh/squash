#include "game_manager.h"

void CreateGame()
{
    InitWindow(WIDTH, HEIGHT, TITLE);    
    if(IsWindowReady() == false)
    {
        fprintf(stderr, "[ERROR]: Failed to initialize window!\n");
        exit(EXIT_FAILURE);
    }
    SetTargetFPS(FPS);
    SetRandomSeed((unsigned)time(NULL));

    InitAudioAssets();
    InitRenderer();
}

Game InitGame(Player* p, Ball* ball, AdvertArray* ads, Rectangle playArea)
{
    double initTime = GetTime();
    Game game = {.resetBall = true, .finished = false, 
                 .bounces = 0, .curHits = 0, .curGame = 0,
                 .resetStartTime = initTime};
    
    InitEntities(p, ball, ads, initTime);
    ResetEntities(p, ball, playArea);

    return game;
}

void SceneManager(Player* p, Ball* ball, enum Scene initScene)
{
    enum Scene curScene = initScene;
    
    while (!WindowShouldClose())
    {
        switch (curScene)
        {
            case SCENE_GAME:
                curScene = MainGame(p, ball);
                break;
            case SCENE_MENU:
                curScene = MenuBrowser();
                break;
            case SCENE_EXIT:
                return;
        }
    }
}

enum Scene MenuBrowser()
{
    int select = 0;
    
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_DOWN))
        {
            select++;
            select %= MENU_CNT;
        }
        
        else if (IsKeyPressed(KEY_UP))
        {
            if (select <= 0) select = MENU_CNT-1;
            else select--;
        }
        
        else if (GetKeyPressed() == KEY_ENTER)
        {
            switch(select)
            {
                case MENU_GAME:
                    return SCENE_GAME;
                case MENU_EXIT:
                    return SCENE_EXIT;
            }
        }
        
        const char* tmpTxt[] = MENU_TXT; 
        RenderMenu(select, tmpTxt, MENU_TXT_CNT);
    }
    
    return SCENE_EXIT;
}

enum Scene MainGame(Player* p, Ball* ball)
{
    Rectangle playArea = GetActivePlayArea();
    
    AdvertArray adArr;
    Game game = InitGame(p, ball, &adArr, playArea);

    int selection = 0;

    SpawnAdvert(&adArr, playArea);

    while (!WindowShouldClose())
    {
        double curTime = GetTime();
        
        if (game.finished)
        {
            if (IsKeyPressed(KEY_RIGHT))
            {
                selection++;
                selection %= GAME_CNT;
            }
            
            else if (IsKeyPressed(KEY_LEFT))
            {
                if (selection <= 0) selection = GAME_CNT-1;
                else selection--;
            }
            
            else if (GetKeyPressed() == KEY_ENTER)
            {
                switch(selection)
                {
                    case GAME_REPLAY:
                        return SCENE_GAME;
                    case GAME_MENU:
                        return SCENE_MENU;
                }
            }
        }
       
        else if (game.resetBall)
        {
            if(curTime - game.resetStartTime > RESET_TIME)
            {
                RenderBallReset(ball, BallFrameCnt(ball, playArea, BALL_BOUNCE_CNT));
                game.resetBall = false;
            }
        }
        
        else
        {
            PlayerInputHandler(&(p[0]), playArea, curTime);
            PlayerInputHandler(&(p[1]), playArea, curTime);
            
            unsigned pIndex = (game.curHits+game.curGame)%2;
            
            Player tmpP = p[pIndex]; 

            bool tmpCol = CheckCollisionCircleRec(ball->obj.pos, BALL_R, (Rectangle){tmpP.obj.pos.x, tmpP.obj.pos.y, PLAYER_HITBOX_W, PLAYER_HITBOX_H});

            if (tmpCol && tmpP.hit)
            { 
                game.curHits++;
                game.bounces = 0;
                
                if (game.curHits % SPEED_INCREASE_THRESHOLD == 0 &&
                    game.curHits <= SPEED_INCREASE_THRESHOLD*SPEED_MAX_INCREASE) 
                {   
                    p[0].obj.speed += SPEED_PLAYER_INCREASE;
                    p[1].obj.speed += SPEED_PLAYER_INCREASE;
                    ball->obj.speed++;

                    UpdateBallSprite(ball);
                }
                
                AssetsPlaySound(SFX_RACKET);
                UpdateBorderAnim(BallFrameCnt(ball, playArea, BALL_BOUNCE_CNT));
            }
            
            ball->wallHitType = GetCollisionAgainstWallType(Vector2Add(ball->obj.pos, ball->obj.vel), playArea);
            bool isBounced = BallKinematics(ball, Vector2Add(tmpP.obj.pos, (Vector2){PLAYER_HITBOX_W / 2, PLAYER_HITBOX_H / 2}), playArea, tmpP.hit&&tmpCol);
            game.bounces += isBounced;
            
            if (isBounced) AssetsPlaySound(SFX_WALL);
            
            if (game.bounces > BALL_BOUNCE_CNT) 
            {   
                p[pIndex].score++;
                
                ResetEntities(p, ball, playArea);
                
                game.curGame++;
                game.curHits = 0;
                game.bounces = 0;
                game.resetBall = true;
                game.resetStartTime = curTime;
                
                if (p[pIndex].score == WINNING_SCORE) game.finished = true;
            }
        }

        const char* tmpTxt[] = GAME_TXT;        
        if (game.finished) RenderGame(p, ball, &adArr, &game, selection, tmpTxt, GAME_TXT_CNT, STATE_END);
        else if (game.resetBall) RenderGame(p, ball, &adArr, &game, selection, tmpTxt, GAME_TXT_CNT, STATE_START);
        else RenderGame(p, ball, &adArr, &game, selection, tmpTxt, GAME_TXT_CNT, STATE_GAME);
    }
    
    FreeAdverts(&adArr);

    return SCENE_EXIT;
}

void CloseGame()
{
    CloseAssets();
    CloseWindow();
}