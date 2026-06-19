/*
TODO: reklamas prototips
TODO: figure out how to check memory leaks

TODO: ad spawning sfx
TODO: ad closing sfx
TODO: ad roundededges
TODO: ad cool close (round edges)

TODO: fix reklamu graphics
TODO: wipe all ads before restarting

TODO: gym mode

CODE IMPROVE: assetmanager get function combined texture and cnt
CODE IMPROVE: seperate all render manager to entities + overlay renderer
CODE IMPROVE: UpdateEntity call
CODE IMPROVE: game is also an entity
CODE IMPROVE: all game entities are created in the game manager

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
    CreateGame();
    SceneManager(SCENE_MENU);
    CloseGame();

    return EXIT_SUCCESS;
}
