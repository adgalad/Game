
#include "Camara.h"

CCamera::CCamera() {
    X = Y = 0;
    
    TargetX = TargetY = NULL;
    
    TargetMode = TARGET_MODE_NORMAL;
}

void CCamera::OnMove(int MoveX, int MoveY) {
    X += MoveX;
    Y += MoveY;
}

int CCamera::GetX() {
    if(TargetX != NULL) {
        if(TargetMode == TARGET_MODE_CENTER) {
            
            return *TargetX - (1280 / 2);
        }
        
        return *TargetX;
    }
    
    return X;
}

int CCamera::GetY() {
    if(TargetY != NULL) {
        if(TargetMode == TARGET_MODE_CENTER) {
            return *TargetY - (1024 / 2);
        }
        
        return *TargetY;
    }
    
    return Y;
}

void CCamera::SetPos(int X, int Y) {
    this->X = X;
    this->Y = Y;
}

void CCamera::SetTarget(int* X, int* Y) {
    TargetX = X;
    TargetY = Y;
}