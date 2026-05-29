#include <stdio.h>
#include <stdlib.h>

#include "game_manager.h"

int main(void)
{
    Player player[2];
    Ball ball;
    
    CreateGame();
    SceneManager(player, &ball, SCENE_MENU);
    CloseGame();

    return EXIT_SUCCESS;
}