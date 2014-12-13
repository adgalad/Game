
#include "Game.h"



int Game::OnRender()
{
    CArea::AreaControl.OnRender(screen, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());
    
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        
        if (CCamera::CameraControl.GetX() <= CEntity::EntityList[i]->X &&
            CEntity::EntityList[i]->X <= CCamera::CameraControl.GetX() + 1280 &&
            CEntity::EntityList[i]->Y >= CCamera::CameraControl.GetY() &&
            CEntity::EntityList[i]->Y <= CCamera::CameraControl.GetY() + 1024 );
        CEntity::EntityList[i]->OnRender(screen);
        
    }
    Efis.OnRender(screen);
    
    SDL_Flip(screen);
    return 0;
}