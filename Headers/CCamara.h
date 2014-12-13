//
//  Camara.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 5/1/14.
//  Copyright (c) 2014 Student. All rights reserved.
//

#ifndef CAMARA_H
#define CAMARA_H

#include "Define.h"

enum {
    TARGET_MODE_NORMAL = 0,
    TARGET_MODE_CENTER
};

class CCamera {
public:
    static CCamera CameraControl;
    

    int X;
    int Y;
    
    int * TargetX;
    int * TargetY;
    
public:
    int TargetMode;
    
public:
    CCamera();
    
public:
    void OnMove(int MoveX, int MoveY);
    
public:
    int GetX();
    int GetY();
    
public:
    void SetPos(int X, int Y);
    
    void SetTarget(int* X, int* Y);
};

CCamera::CCamera() {
    X = Y = 0;
    
    TargetX = TargetY = NULL;
    
    TargetMode = TARGET_MODE_NORMAL;
}

CCamera CCamera::CameraControl;

#endif
