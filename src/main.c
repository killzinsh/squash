/*
TODO: reklamas prototips
TODO: figure out how to check memory leaks
TODO: close reklamas
TODO: set spawning time

TODO: ad spawning sfx
TODO: ad closing sfx

TODO: gym mode

CODE IMPROVE: assetmanager get function combined texture and cnt
CODE IMPROVE: seperate all entities in respective source files
CODE IMPROVE: seperate all render manager to entities + overlay renderer
CODE IMPROVE: init all entities in single funciton call
CODE IMPROVE: set ball sprite in INIT call

TODO: backgorund images / fade between multiple (debesis, plava, jura, mezs, akmenains kalns)
TODO: active player white outline

TODO: swoosh skana raketei (un tad hitam butu janogaida bisku)
TODO: bumbas rotation

TODO: reset scrolling text after each amtch
TODO: brockhampton type beeps (berlin) prieks kickoff
TODO: make game music (priekks kick off + tad main loop)
TODO: hpye man count in
TODO: classic push in, fadout count in animation (davinci uztaisit)

TODO: Menu selection beeps
TODO: add menu music loop
TODO: end screen music loop
*/
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
