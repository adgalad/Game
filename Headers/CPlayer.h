//
//  CPlayer.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 5/4/14.
//  Copyright (c) 2014 Student. All rights reserved.
//

#ifndef HelloSDL_CPlayer_h
#define HelloSDL_CPlayer_h

#include "CEntity.h"

class CPlayer : public CEntity {
public:
    CPlayer();
    
    bool OnLoad(std::string File, int Width, int Height, int MaxFrames);
    
    void OnLoop();
    
    void OnRender(SDL_Surface* Surf_Display);
    
    void OnCleanup();
    
    void OnAnimate();
    
    void OnCollision(CEntity* Entity);
};


CPlayer::CPlayer() {
}

bool CPlayer::OnLoad(std::string File , int Width, int Height, int MaxFrames) {
    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
        return false;
    }
    
    return true;
}

void CPlayer::OnLoop() {
    //CEntity::OnLoop();
}

void CPlayer::OnRender(SDL_Surface* Surf_Display) {
    CEntity::OnRender(Surf_Display);
}

void CPlayer::OnCleanup() {
    CEntity::OnCleanup();
}

void CPlayer::OnAnimate() {
    if(SpeedX != 0) {
        Anim_Control.MaxFrames = 8;
    }else{
        Anim_Control.MaxFrames = 0;
    }
    
    CEntity::OnAnimate();
}

void CPlayer::OnCollision(CEntity* Entity) {
}

#endif
