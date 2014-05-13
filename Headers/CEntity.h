//
//  Entity.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 4/30/14.
//  Copyright (c) 2014 Student. All rights reserved.
//
#ifndef _CENTITY_H_
#define _CENTITY_H_

#include <vector>

#include "CArea.h"
#include "CAnimation.h"
#include "Camara.h"
#include "CFPS.h"
#include "Surface.h"
#include "CEntityCol.h"


/*

enum {
    ENTITY_TYPE_GENERIC = 0,
    
    ENTITY_TYPE_PLAYER
};

enum {
    ENTITY_FLAG_NONE     = 0,
    
    ENTITY_FLAG_GRAVITY    = 0x00000001,
    ENTITY_FLAG_GHOST    = 0x00000002,
    ENTITY_FLAG_MAPONLY    = 0x00000004
};



//* CLASS //

class CEntity {
public:
    static std::vector<CEntity*>    EntityList;
    
protected:
    CAnimation      Anim_Control;
    
    
    
public:
    SDL_Surface*    Surf_Entity;
    int           X;
    int           Y;
    float           Xd; // remove
    float           Yd; // remove
    
    int             Width;
    int             Height;
    
    bool        Dimension;
    bool        MoveLeft;
    bool        MoveRight;
    bool        MoveUp;
    bool        MoveDown;
    
public:
    int        Type;
    
    bool        Dead;
    int         Flags;
    int         AnimState; // remove
    bool        Anim;       // remove
    
protected:
    float        SpeedX;
    float        SpeedY;
    
    float        AccelX;
    float        AccelY;
    
public:
    float        MaxSpeedX;
    float        MaxSpeedY;
    
protected:
    int             CurrentFrameCol;
    int             CurrentFrameRow;
    
protected:
    int        Col_X;
    int        Col_Y;
    int        Col_Width;
    int        Col_Height;
    
public:
    CEntity();
    
    virtual ~CEntity();
    
public:
    virtual bool OnLoad(std::string File, int Width, int Height, int MaxFrames);
    
    virtual void OnLoop();
    
    virtual void OnRender(SDL_Surface* Surf_Display);
    
    virtual void OnCleanup();
    
    virtual void OnAnimate();
    
    virtual void OnCollision(CEntity *Entity);
    
public:
    void    OnMove(float MoveX, float MoveY);
    
    void     StopMove();
    
public:
    bool    Collides(int oX, int oY, int oW, int oH);
    
private:
    bool     PosValid(int NewX, int NewY);
    
    bool     PosValidTile(CTile* Tile);
    
    bool     PosValidEntity(CEntity* Entity, int NewX, int NewY);
};


std::vector<CEntity*> CEntity::EntityList;

//* CONSTRUCTOR //



CEntity::CEntity() {
    Surf_Entity = NULL;
    
    X = 0;
    Y = 0;
    Xd= Yd= 0;
    AnimState=0;
    Anim=false;
    Width     = 0;
    Height     = 0;
    
    Dimension = true;
    MoveLeft  = false;
    MoveRight = false;
    MoveDown  = false;
    MoveUp = false;
    
    Type =     ENTITY_TYPE_GENERIC;
    
    Dead = false;
    Flags = ENTITY_FLAG_GRAVITY;
    
    SpeedX = 0;
    SpeedY = 0;
    
    AccelX = 0;
    AccelY = 0;
    
    MaxSpeedX = 10;
    MaxSpeedY = 10;
    
    CurrentFrameCol = 0;
    CurrentFrameRow = 0;
    
    Col_X = 0;
    Col_Y = 0;
    
    Col_Width  = 0;
    Col_Height = 0;
}

CEntity::~CEntity() {
}



//* ENTITY COLISION //
class CEntityCol {
public:
    static std::vector<CEntityCol>    EntityColList;
    
public:
    CEntity* EntityA;
    CEntity* EntityB;
    
public:
    CEntityCol();
};



std::vector<CEntityCol> CEntityCol::EntityColList;

CEntityCol::CEntityCol() {
    EntityA = NULL;
    EntityB = NULL;
}




//* IMPLEMENTACION //


bool CEntity::OnLoad(std::string File, int Width, int Height, int MaxFrames) {
    File=path+File;
    std::cout <<File +"\n";
    if((Surf_Entity = Csurface::OnLoad(&File[0])) == NULL) {
        return false;
    }
    
    Csurface::Transparent(Surf_Entity, 255,100, 200);
    
    this->Width = Width;
    this->Height = Height;
    
    Anim_Control.MaxFrames = MaxFrames;
    
    return true;
}


void CEntity::OnAnimate() {
    if(MoveLeft) {
        CurrentFrameCol = 0;
    }
    else if(MoveRight) {
        CurrentFrameCol = 1;
        }
    
    Anim_Control.OnAnimate();
}

void CEntity::OnMove(float MoveX, float MoveY) {
    if(MoveX == 0 && MoveY == 0) return;
  
    double NewX = 0;
    double NewY = 0;
    
    MoveX *= CFPS::FPSControl.GetSpeedFactor();
    MoveY *= CFPS::FPSControl.GetSpeedFactor();
    
    if(MoveX != 0) {
        if(MoveX >= 0)     NewX =  CFPS::FPSControl.GetSpeedFactor();
        else             NewX = -CFPS::FPSControl.GetSpeedFactor();
    }
    
    if(MoveY != 0) {
        if(MoveY >= 0)     NewY =  CFPS::FPSControl.GetSpeedFactor();
        else             NewY = -CFPS::FPSControl.GetSpeedFactor();
    }
    
    while(true) {
        if(Flags & ENTITY_FLAG_GHOST) {
            PosValid((int)(X + NewX), (int)(Y + NewY)); //We don't care about collisions, but we need to send events to other entities
            
            X += NewX;
            Y += NewY;
            
        }else{
            if(PosValid((int)(X + NewX), (int)(Y))) {
                X += NewX;
                // printf("entra  %d, %d \n",X, Y);
            }else{
                SpeedX = 0;
            }
            
            if(PosValid((int)(X), (int)(Y + NewY))) {
                Y += NewY;
                //printf("entra2  %d, %d \n",X, Y);
            }else{
                
                SpeedY = 0;
            }
        }
        
        MoveX += -NewX;
        MoveY += -NewY;
        
        if(NewX > 0 && MoveX <= 0) NewX = 0;
        if(NewX < 0 && MoveX >= 0) NewX = 0;
        
        if(NewY > 0 && MoveY <= 0) NewY = 0;
        if(NewY < 0 && MoveY >= 0) NewY = 0;
        
        if(MoveX == 0) NewX = 0;
        if(MoveY == 0) NewY = 0;
        
        if(MoveX == 0 && MoveY     == 0)     break;
        if(NewX  == 0 && NewY     == 0)     break;
    }
}
void CEntity::StopMove() {
    if(SpeedX > 0) {
        AccelX = -1;
    }
    
    if(SpeedX < 0) {
        AccelX =  1;
    }
    
    if(SpeedX < 2.0f && SpeedX > -2.0f) {
        AccelX = 0;
        SpeedX = 0;
    }
}

bool CEntity::PosValid(int NewX, int NewY) {
    bool Return = true;
    
    int StartX     = (NewX + Col_X) / TILE_SIZE;
    int StartY     = (NewY + Col_Y) / TILE_SIZE;
    
    int EndX    = ((NewX + Col_X) + Width - Col_Width - 1)         / TILE_SIZE;
    int EndY    = ((NewY + Col_Y) + Height - Col_Height - 1)    / TILE_SIZE;
    
    for(int iY = StartY;iY <= EndY;iY++) {
        for(int iX = StartX;iX <= EndX;iX++) {
            CTile* Tile = CArea::AreaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE);
            
            if(PosValidTile(Tile) == false) {
                Return = false;
            }
        }
    }
    
    if(Flags & ENTITY_FLAG_MAPONLY) {
    }else{
        for(int i = 0;i < EntityList.size();i++) {
            if(PosValidEntity(EntityList[i], NewX, NewY) == false) {
                Return = false;
            }
        }
    }
    
    return Return;
}

bool CEntity::PosValidEntity(CEntity* Entity, int NewX, int NewY) {
    if(this != Entity && Entity != NULL && Entity->Dead == false &&
       Entity->Flags ^ ENTITY_FLAG_MAPONLY &&
       Entity->Collides(NewX + Col_X, NewY + Col_Y, Width - Col_Width - 1, Height - Col_Height - 1) == true) {
        
        CEntityCol EntityCol;
        
        EntityCol.EntityA = this;
        EntityCol.EntityB = Entity;
        
        CEntityCol::EntityColList.push_back(EntityCol);
        
        return false;
    }
    
    return true;
}

bool CEntity::PosValidTile(CTile* Tile) {
    if(Tile == NULL) {
        return true;
    }
    
    if(Tile->TypeID == TILE_TYPE_BLOCK) {
        return false;
    }
    
    return true;
}

bool CEntity::Collides(int oX, int oY, int oW, int oH) {
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;
    
    int tX = (int)X + Col_X;
    int tY = (int)Y + Col_Y;
    
    left1 = tX;
    left2 = oX;
    
    right1 = left1 + Width - 1 - Col_Width;
    right2 = oX + oW - 1;
    
    top1 = tY;
    top2 = oY;
    
    bottom1 = top1 + Height - 1 - Col_Height;
    bottom2 = oY + oH - 1;
    
    
    if (bottom1 < top2) return false;
    if (top1 > bottom2) return false;
    
    if (right1 < left2) return false;
    if (left1 > right2) return false;
    
    return true;
}


void CEntity::OnLoop() {
    
    if (Dimension)
    {
        //We're not Moving
        if(MoveLeft == false && MoveRight == false ) {
            StopMove();
        }
    // Anim_Control.OnAnimate();
        if(MoveLeft) {
            AccelX = -0.5;
        }else
        
        if(MoveRight) {
            AccelX = 0.5;
        }
        
        if(Flags & ENTITY_FLAG_GRAVITY) {
            AccelY = 0.75f;
        }
        
        SpeedX += AccelX * (CFPS::FPSControl.GetSpeedFactor()+10);
        SpeedY += AccelY * (CFPS::FPSControl.GetSpeedFactor()+10);
        
        if(SpeedX > MaxSpeedX)  SpeedX =  MaxSpeedX;
        if(SpeedX < -MaxSpeedX) SpeedX = -MaxSpeedX;
        if(SpeedY > MaxSpeedY)  SpeedY =  MaxSpeedY;
        if(SpeedY < -MaxSpeedY) SpeedY = -MaxSpeedY;
        
        if ( SpeedX != 0 && SpeedY !=0)
        {
            printf("Hola");
            OnAnimate();
            OnMove(SpeedX, SpeedY);
        }
    }
    
    
    else
    {
        //We're not Movingif
        if (MoveLeft == false && MoveRight == false && MoveDown == false && MoveUp == false)
        {
            StopMove();
        }
        if(MoveLeft) {
            AccelX = -0.5;
        }else
            
            if(MoveRight) {
                AccelX = 0.5;
            }

        if(Flags & ENTITY_FLAG_GRAVITY) {
            AccelY = 0.75f;
        }

        SpeedX += AccelX * (CFPS::FPSControl.GetSpeedFactor()+10);
        SpeedY += AccelY * (CFPS::FPSControl.GetSpeedFactor()+10);

         if(SpeedX > MaxSpeedX)  SpeedX =  MaxSpeedX;
         if(SpeedX < -MaxSpeedX) SpeedX = -MaxSpeedX;
         if(SpeedY > MaxSpeedY)  SpeedY =  MaxSpeedY;
         if(SpeedY < -MaxSpeedY) SpeedY = -MaxSpeedY;
        if ( SpeedX != 0 && SpeedY !=0)
        {
        printf("Hola");
            OnAnimate();
            OnMove(SpeedX, SpeedY);
        }
    }
}



void CEntity::OnRender(SDL_Surface* Surf_Display) {
    if(Surf_Entity == NULL || Surf_Display == NULL) return;
    
    Csurface::OnDraw(Surf_Display, Surf_Entity, X , Y , AnimState * Width, (Anim_Control.GetCurrentFrame()) * Height, Width, Height);
}


void CEntity::OnCleanup() {
    if(Surf_Entity) {
        SDL_FreeSurface(Surf_Entity);
    }
    
    Surf_Entity = NULL;
}

void CEntity::OnCollision(CEntity* Entity)
{
    
}































*/



//* FLAGS //

enum {
    ENTITY_TYPE_GENERIC = 0,
    
    ENTITY_TYPE_PLAYER
};

enum {
    ENTITY_FLAG_NONE     = 0,
    
    ENTITY_FLAG_GRAVITY    = 0x00000001,
    ENTITY_FLAG_GHOST    = 0x00000002,
    ENTITY_FLAG_MAPONLY    = 0x00000004
};



//* CLASS //

class CEntity {
public:
    static std::vector<CEntity*>    EntityList;
    
protected:
    CAnimation      Anim_Control;
    

    
public:
        SDL_Surface*    Surf_Entity;
    float           X;
    float           Y;
    float           Xd;
    float           Yd;
    
    int             Width;
    int             Height;
    

    
public:
    int        Type;
    
    bool        Dead;
    int         Flags;
    
protected:
    float        SpeedX;
    float        SpeedY;
    
    float        AccelX;
    float        AccelY;
    
public:
    float        MaxSpeedX;
    float        MaxSpeedY;
    
protected:
    int         AnimState;
    bool        Dimension;
    bool        Anim;
    bool        player;
    

    
public:
    CEntity();
    
    virtual ~CEntity();
    
public:
    virtual bool OnLoad(std::string File, int Width, int Height, int MaxFrames);
    
    virtual void OnLoop();
    
    virtual void OnRender(SDL_Surface* Surf_Display);
    
    virtual void OnCleanup();
    
    virtual void OnAnimate();
    
    virtual void OnCollision(CEntity *Entity);
    
public:
    void    OnMove(SDLKey key);
    
    void     StopMove();
    
public:
    bool    Collides(int oX, int oY, int oW, int oH);
    void    setPlayerMode(bool b);
private:
    bool     PosValid(int NewX, int NewY);
    
    bool     PosValidTile(CTile* Tile);
    
    bool     PosValidEntity(CEntity* Entity, int NewX, int NewY);
};


std::vector<CEntity*> CEntity::EntityList;

//* CONSTRUCTOR //


void CEntity::setPlayerMode(bool b)
{
    player = b;
}
CEntity::CEntity() {
    Surf_Entity = NULL;
    
    X = 0;
    Y = 0;
    Xd= Yd= 0;
    AnimState=1;
    Width     = 0;
    Height     = 0;

    
    Type =     ENTITY_TYPE_GENERIC;
    
    Dead = false;
    Flags = ENTITY_FLAG_GRAVITY;
    
    SpeedX = 5;
    SpeedY = 5;
    
    AccelX = 0;
    AccelY = 0;
    
    MaxSpeedX = 5;
    MaxSpeedY = 5;

    player = false;
}

CEntity::~CEntity() {
}



//* ENTITY COLISION //
class CEntityCol {
public:
    static std::vector<CEntityCol>    EntityColList;
    
public:
    CEntity* EntityA;
    CEntity* EntityB;
    
public:
    CEntityCol();
};



std::vector<CEntityCol> CEntityCol::EntityColList;

CEntityCol::CEntityCol() {
    EntityA = NULL;
    EntityB = NULL;
}




//* IMPLEMENTACION //


bool CEntity::OnLoad(std::string File, int Width, int Height, int MaxFrames) {
    File=path+File;
    std::cout <<File +"\n";
    if((Surf_Entity = Csurface::OnLoad(&File[0])) == NULL) {
        return false;
    }
    
     Csurface::Transparent(Surf_Entity, 255,100, 200);
    
    this->Width = Width;
    this->Height = Height;
    
    Anim_Control.MaxFrames = MaxFrames;
    
    return true;
}



bool CEntity::PosValid(int NewX, int NewY) {

    CTile * Tile = NULL;
    int camX=CCamera::CameraControl.GetX() + X;
    int camY=CCamera::CameraControl.GetY() + Y;



    for(int iY = 4;iY <= Height-4;iY++) {
        for(int iX = 4;iX <= Width-4;iX++) {
            Tile = CArea::AreaControl.GetTile(camX + NewX + iX , camY + NewY + iY );
            
            if(PosValidTile(Tile) == false) {
                return  false;
            }
        }
    }
    
 

 /*
    if(Flags & ENTITY_FLAG_MAPONLY) {
    }else{
        for(int i = 0;i < EntityList.size();i++) {
            if(PosValidEntity(EntityList[i], NewX, NewY) == false) {
                return false;
            }
        }
    } */
    return true;
}

bool CEntity::PosValidEntity(CEntity* Entity, int NewX, int NewY) {
    /*
    if(this != Entity && Entity != NULL && Entity->Dead == false &&
       Entity->Flags ^ ENTITY_FLAG_MAPONLY &&
       Entity->Collides(NewX + Col_X, NewY + Col_Y, Width - Col_Width - 1, Height - Col_Height - 1) == true) {
        
        CEntityCol EntityCol;
        
        EntityCol.EntityA = this;
        EntityCol.EntityB = Entity;
        
        CEntityCol::EntityColList.push_back(EntityCol);
        
        return false;
    }
    
    return true;*/
}

bool CEntity::PosValidTile(CTile* Tile) {
    if(Tile == NULL) {
        return true;
    }
    if(Tile->TypeID == TILE_TYPE_BLOCK || Tile->TypeID == TILE_TYPE_NONE) {
        
        return false;
    }
    
    return true;
}

bool CEntity::Collides(int oX, int oY, int oW, int oH) {
    /*
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;
    
    int tX = (int)X + Col_X;
    int tY = (int)Y + Col_Y;
    
    left1 = tX;
    left2 = oX;
    
    right1 = left1 + Width - 1 - Col_Width;
    right2 = oX + oW - 1;
    
    top1 = tY;
    top2 = oY;
    
    bottom1 = top1 + Height - 1 - Col_Height;
    bottom2 = oY + oH - 1;
    
    
    if (bottom1 < top2) return false;
    if (top1 > bottom2) return false;
    
    if (right1 < left2) return false;
    if (left1 > right2) return false;
    
    return true;*/
}


void CEntity::OnAnimate()
{

                    
}

void CEntity::OnMove(SDLKey key)
{
    if(player)
        {
        Anim = true;
        if (key == SDLK_DOWN )
            {
            AnimState = 1;
            if ( PosValid(  0, (int)(SpeedY)) )
                {
                if (CCamera::CameraControl.GetY() < MAP_HEIGHT*32  )
                    {
                    if ( Yd+SpeedY >= 0)
                        {
                        CCamera::CameraControl.OnMove( 0 ,SpeedY);
                        }
                    else
                        {
                        Y+=SpeedY;
                        Yd+=SpeedY;
                        }
                    }
                else
                    {
                    CCamera::CameraControl.OnMove(0, SpeedY);
                    }
                }
            }
        if (key == SDLK_LEFT )
            {
            AnimState = 2;
            if (PosValid((int)-SpeedX, 0))
                {
                if (CCamera::CameraControl.GetX() <= 0)
                    {
                    
                    if ( Xd-SpeedX <=  MAP_HEIGHT*32 && false)
                        {
                        CCamera::CameraControl.OnMove(-SpeedX, 0);
                        }
                    else
                        {
                        X-=SpeedX;
                        Xd-=SpeedX;
                        }
                    }
                else
                    {
                    CCamera::CameraControl.OnMove(-SpeedX, 0);
                    }
                }
            }
        if (key == SDLK_RIGHT )
            {
            AnimState = 3;
            if (PosValid( (int)(SpeedX), 0))
                {
                if (CCamera::CameraControl.GetX() < MAP_HEIGHT*32 )
                    {
                        if ( Xd+SpeedX >= 0)
                            {
                            CCamera::CameraControl.OnMove(SpeedX, 0);
                            }
                        else
                            {
                            X+=SpeedX;
                            Xd+=SpeedX;
                            }
                    }
                else
                    {
                    CCamera::CameraControl.OnMove(SpeedX, 0);
                    }
               }
            }
        if (key == SDLK_UP)
            {
            AnimState = 4;
            if (PosValid(0 , (int)-SpeedY))
                {
                if (CCamera::CameraControl.GetY() < 0)
                    {
                    if ( Yd-SpeedY <=  MAP_HEIGHT*32 && false)
                        {
                        CCamera::CameraControl.OnMove( 0 , -SpeedY);
                        }
                    else
                        {
                        Y-=SpeedY;
                        Yd-=SpeedY;
                        }
                    }
                else
                    {
                    CCamera::CameraControl.OnMove(0, -SpeedY);
                    }
                }
            }
        }
    else
        {
        
            Anim = true;
            if (key == SDLK_DOWN )
                {
                AnimState = 1;
                if ( PosValid(  0, (int)(SpeedY)) )
                    {
                    Y+=1;
                    Y-=1;
                    }
                }
            if (key == SDLK_LEFT )
                {
                AnimState = 2;
                if (PosValid((int)-SpeedX, 0))
                    {
                    X-=1;
                    X+=1;
                    }
                }
            if (key == SDLK_RIGHT )
                {
                AnimState = 3;
                if (PosValid( (int)(SpeedX), 0))
                    {
                    X+=1;
                    X-=1;
                    }
                }
            if (key == SDLK_UP)
                {
                AnimState = 4;
                if (PosValid(0 , (int)-SpeedY))
                    {
                    Y-=1;
                    Y+=1;
                    }
                }
        }
    
}
void CEntity::StopMove()
{
    Anim = false;
}

void CEntity::OnLoop() {
    Anim_Control.OnAnimate();

        
}



void CEntity::OnRender(SDL_Surface* Surf_Display) {
    if(Surf_Entity == NULL || Surf_Display == NULL) return;

    if (Anim){
        Csurface::OnDraw(Surf_Display, Surf_Entity, X, Y, Anim_Control.GetCurrentFrame()*Width,(AnimState -1) * Height, Width, Height);
        
    }
    else
        Csurface::OnDraw(Surf_Display, Surf_Entity, X, Y, Width,(AnimState - 1) * Height, Width, Height);

}



void CEntity::OnCleanup() {
    if(Surf_Entity) {
        SDL_FreeSurface(Surf_Entity);
    }
    
    Surf_Entity = NULL;
}

void CEntity::OnCollision(CEntity* Entity)
{
    
}

#endif
 
 
