/*
TODO: add menu music loop
CODE IMPROVE: make unified menu call
TODO: swoosh skana raketei (un tad hitam butu janogaida bisku)
TODO: ad closing sfx

TODO: slow menu option fade, fade in main game
TODO: slow moving rackets, fade in while counting in

TODO: sound manager
TODO: texture manager
TODO: text manager

TODO: figure out how to check memory leaks

TODO: ad spawning sfx
TODO: ad cool close (round edges)

TODO: gym mode

TODO: backgorund images / fade between multiple (debesis, plava, jura, mezs, akmenains kalns)
TODO: active player white outline

TODO: bumbas rotation

TODO: reset scrolling text after each match
TODO: brockhampton type beeps (berlin) prieks kickoff
TODO: make game music (priekks kick off + tad main loop)
TODO: hpye man count in
TODO: classic push in, fadout count in animation (davinci uztaisit)

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
