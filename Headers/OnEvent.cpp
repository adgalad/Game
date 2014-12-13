
#include "Game.h"


bool Game::OnEvent(SDL_Event *Event)
{
    
    switch (Event->type) {
            
        case SDL_KEYDOWN:
            
            if (Event->key.keysym.sym == SDLK_ESCAPE)
            {
                running=false;
            }
            else if (Event->key.keysym.unicode == 'c')
            {
                SDL_EnableKeyRepeat(0, SDL_DEFAULT_REPEAT_INTERVAL / 3);
                printf("%d \n",CurrentCharSurface);
                ++CurrentCharSurface;
                if ( CurrentCharSurface >= CEntity::EntityList.size() )
                    CurrentCharSurface = 0;
                if (CurrentCharSurface != 0)
                    Efis.Surf_Entity = CEntity::EntityList[CurrentCharSurface]->Surf_Entity;
                else
                    Efis.OnLoad("Efis.png", 32, 32, 3);
                SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
            }
            else {
                Efis.OnMove(Event->key.keysym.sym);
                
            }
            break;
        case SDL_KEYUP:
            
            Efis.StopMove();
            
            
            break;
        case SDL_QUIT:
            running=false;
            break;
        default:
            
            break;
    }
    
    return 0;
}