
#include "Game.h"

void Game::OnLoop()
{
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if ( !CEntity::EntityList[i] ) continue;
        
        CEntity::EntityList[i]->OnLoop();
        printf("%f \n",CEntity::EntityList[0]->Y);
        
    }
    Efis.OnLoop();
    
    
}