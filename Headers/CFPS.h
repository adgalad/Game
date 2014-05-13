//
//  CFPS.cpp
//  HelloSDL
//
//  Created by Carlos Spaggiari on 5/4/14.
//  Copyright (c) 2014 Student. All rights reserved.
//


#ifndef _CFPS_H_
#define _CFPS_H_

#include <SDL/SDL.h>

class CFPS {
public:
    static CFPS FPSControl;
    
private:
    int     OldTime;
    int     LastTime;
    
    float     SpeedFactor;
    
    int    NumFrames;
    int     Frames;
    
public:
    CFPS();
    
    void    OnLoop();
    
public:
    int     GetFPS();
    
    float   GetSpeedFactor();
};

#endif

CFPS CFPS::FPSControl;

CFPS::CFPS() {
    OldTime     = 0;
    LastTime    = 0;
    
    SpeedFactor    = 0;
    
    Frames      = 0;
    NumFrames   = 0;
}

void CFPS::OnLoop() {
    if(OldTime + 1000 < SDL_GetTicks()) {
        OldTime = SDL_GetTicks();
        
        NumFrames = Frames;
        
        Frames = 0;
    }
    
    SpeedFactor = ((SDL_GetTicks() - LastTime) / 1000.0f) * 32.0f;
    
    LastTime = SDL_GetTicks();
    
    Frames++;
}

int CFPS::GetFPS() {
    return NumFrames;
}

float CFPS::GetSpeedFactor() {
    return SpeedFactor;
}