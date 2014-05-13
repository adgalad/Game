#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "OnExecute.h"



int SDL_main (int argc, char **argv)
{
    
    Game game;
    SDL_Event Event_Menu;
    return game.OnExecute(&Event_Menu);
}
