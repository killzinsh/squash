#include "game_manager.h"

static Player player1;
static Player player2;
static Ball ball;
static AdvertArray adArr;

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
    InitEntities(&player1, &player2, &ball, &adArr);
}

Game InitGame()
{
    double initTime = GetTime();
    Game game = {.resetBall = true, .finished = false, 
                 .bounces = 0, .curHits = 0, .curGame = 0,
                 .resetStartTime = initTime};
    return game;
}

void SceneManager(enum Scene initScene)
{
    enum Scene curScene = initScene;
    
    while (!WindowShouldClose())
    {
        switch (curScene)
        {
            case SCENE_GAME:
                curScene = MainGame();
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

enum Scene MainGame()
{
    Rectangle playArea = GetActivePlayArea();
    Game game = InitGame();
    ResetEntities(&player1, &player2, &ball, &adArr, playArea);
    int selection = 0;

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
       
        else if (game.resetBall && curTime - game.resetStartTime > RESET_TIME)
        {
            ResetBorderAnimation(BallFrameCnt(&ball, playArea, BALL_BOUNCE_CNT));
            adArr.spawnTimer = GetTime();
            game.resetBall = false;
        }
        
        else if (game.resetBall == false)
        {
            int activePlayer = (game.curHits+game.curGame)%2;
            UpdateEntities(&player1, &player2, activePlayer, &ball, &adArr, playArea);

            if (ball.hitType == COL_PLAYER_HIT)
            { 
                game.curHits++;
                game.bounces = 0;
                
                if (game.curHits % SPEED_INCREASE_THRESHOLD == 0 &&
                    game.curHits <= SPEED_INCREASE_THRESHOLD*SPEED_MAX_INCREASE) 
                {
                    UpgradeEntityStats(&player1, &player2, &ball, SPEED_PLAYER_INCREASE, SPEED_BALL_INCREASE);
                }
                
                AssetsPlaySound(SFX_RACKET);
                ResetBorderAnimation(BallFrameCnt(&ball, playArea, BALL_BOUNCE_CNT));
            }

            if (ball.hitType != COL_NOHIT)
            {
                game.bounces++;
                if (ball.hitType != COL_PLAYER_HIT)
                    AssetsPlaySound(SFX_WALL);
            }

            if (game.bounces > BALL_BOUNCE_CNT) 
            {   
                UpdatePlayerScore(&player1, &player2, activePlayer);
                ResetEntities(&player1, &player2, &ball, &adArr, playArea);
                
                game.curGame++;
                game.curHits = 0;
                game.bounces = 0;
                game.resetBall = true;
                game.resetStartTime = curTime;
                
                if (player1.score == WINNING_SCORE || player2.score == WINNING_SCORE) game.finished = true;
            }
        }

        const char* tmpTxt[] = GAME_TXT;        
        if (game.finished) RenderGameEnd(&player1, &player2, game.curHits, selection, tmpTxt, GAME_TXT_CNT);
        else if (game.resetBall) RenderGameStart(&player1, &player2, game.resetStartTime, game.curHits);
        else RenderGame(&player1, &player2, &ball, &adArr, game.curHits);
    }

    return SCENE_EXIT;
}

void CloseGame()
{
    CloseEntities(&adArr);
    CloseAssets();
    CloseWindow();
}