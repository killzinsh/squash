#include "game_manager.h"

static MenuOptions startMenu;
static MenuOptions endMenu;
static int selection;


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

    startMenu.optionCnt = START_MENU_CNT;
    const char* startMenuTxt[START_MENU_CNT] = START_MENU_TXT;
    int startMenuScenes[START_MENU_CNT] = START_MENU_SCENES;
    for (int i = 0; i < START_MENU_CNT; i++)
    {
        startMenu.optionTxt[i] = startMenuTxt[i];
        startMenu.scenes[i] = startMenuScenes[i];
    }

    endMenu.optionCnt = END_MENU_CNT;
    endMenu.optionTxt[0] = "REPLAY";
    endMenu.scenes[0] = SCENE_GAME;
    endMenu.optionTxt[1] = "MAIN MENU";
    endMenu.scenes[1] = SCENE_MENU;
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
                curScene = StartMenu();
                break;
            case SCENE_GYM:
                return;
                break;
            case SCENE_P1_WON:
                curScene = GameOver(PLAYER_ONE);
                break;
            case SCENE_P2_WON:
                curScene = GameOver(PLAYER_TWO);
                break;
            case SCENE_EXIT:
                return;
            default:
                fprintf(stderr, "[ERROR]: Scene unrecognized!\n");
                return;    
        }
    }
}

enum Scene MenuBrowser(MenuOptions menu)
{
    if (IsKeyPressed(KEY_DOWN))
    {
        AssetsPlaySound(SFX_BEEP);
        selection++;
        selection %= menu.optionCnt;
    }
    
    else if (IsKeyPressed(KEY_UP))
    {
        AssetsPlaySound(SFX_BEEP);
        if (selection <= 0) selection = menu.optionCnt-1;
        else selection--;
    }
    
    else if (GetKeyPressed() == KEY_ENTER)
    {
        AssetsPlaySound(SFX_SELECT);
        return menu.scenes[selection];
    }
    
    return SCENE_NOCHANGE;
}

enum Scene StartMenu()
{
    selection = 0;
    while(!WindowShouldClose())
    {
        enum Scene returnScene = MenuBrowser(startMenu);
        if (returnScene != SCENE_NOCHANGE) return returnScene;
        RenderStartMenu(selection, startMenu.optionCnt, startMenu.optionTxt);   
    }

    return SCENE_EXIT;
}

enum Scene GameOver(enum PlayerTypes winner)
{
    selection = 0;
    while (!WindowShouldClose())
    {
        enum Scene returnScene = MenuBrowser(endMenu);
        if (returnScene != SCENE_NOCHANGE) return returnScene;

        char buff[TXT_BUFF];
        if (winner == PLAYER_ONE) strcpy(buff, "GREEN RACKET WINS!");
        else strcpy(buff, "PURPLE RACKET WINS!");

        RenderGameEnd(buff, selection, endMenu.optionCnt, endMenu.optionTxt);
    }

    return SCENE_EXIT;
}

enum Scene MainGame()
{
    Rectangle playArea = GetActivePlayArea();
   
    Player player1;
    Player player2;
    Ball ball;
    AdvertArray adArr;

    Game game = InitEntities(&player1, &player2, &ball, &adArr);
    ResetEntities(&player1, &player2, &ball, &adArr, &game, playArea);

    while (!WindowShouldClose() && game.finished == false)
    {
        double curTime = GetTime();
       
        if (game.resetBall && curTime - game.resetStartTime > RESET_TIME)
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
                UpdateScore(&player1, &player2, activePlayer, &game);
                ResetEntities(&player1, &player2, &ball, &adArr, &game, playArea);
                                
                if (player1.score == WINNING_SCORE || player2.score == WINNING_SCORE) game.finished = true;
            }
        }
       
        if (game.resetBall) RenderGameStart(&player1, &player2, (float)game.resetStartTime, game.curHits);
        else RenderGame(&player1, &player2, &ball, &adArr, game.curHits);
    }

    CloseEntities(&adArr);

    if (player1.score == WINNING_SCORE) return SCENE_P1_WON;
    else if (player2.score == WINNING_SCORE) return SCENE_P2_WON;

    return SCENE_EXIT;
}

void CloseGame()
{
    CloseAssets();
    CloseWindow();
}