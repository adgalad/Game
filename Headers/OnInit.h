//
//  OnInit.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 4/26/14.
//  Copyright (c) 2014 Student. All rights reserved.
//

#include "Game.h"
#include <fstream>
bool Game::Fread()
{
    std::string File = path+"loadEntities.txt";
    FILE *load = fopen(&File[0], "r");
    if (load == NULL)
        return false;
    
    int numEnt;
    fscanf(load,"%d\n",&numEnt);
    char *img = new char;
    int w,h,mf,x,y;
    for (int i=0;i<numEnt;i++)
        {
        CEntity::EntityList.push_back(new CEntity());
        
        std::string str;
        fscanf(load, "%s %d %d %d %d %d\n",img,&w,&h,&mf,&x,&y);
        str.assign(img);
        CEntity::EntityList[i]->OnLoad(str, w, h, mf);
        CEntity::EntityList[i]->X = x;
        CEntity::EntityList[i]->Y = y;
        }
    
    
    return true;
}

bool Game::OnInit()
{
    
    /* Init SDL */
    if (SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        return false;
    }
    const SDL_VideoInfo *VideoInfo;
    VideoInfo = SDL_GetVideoInfo();
    int h=VideoInfo->current_h;
    int w=VideoInfo->current_w;
       /* Set Video Mode */
    if ((screen=SDL_SetVideoMode(w,h, 32, SDL_HWSURFACE|SDL_DOUBLEBUF))==NULL)
    {
        return false;
    }
    
    /* Set Unicode Translate */
    SDL_EnableUNICODE(1);
    
    /* Enable Key Repeat */
    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
    
    
    /* LOAD MAP */

    if(CArea::AreaControl.OnLoad("1.area") == false) {
        return false;
    }
    
    /* LOAD ENTITIES */

    Efis = CEntity();
    if(Efis.OnLoad("Efis.png", 32, 32, 2) == false) {
        return false;
    }


    Fread();
    Efis.setPlayerMode(true);
    Efis.X=w/2-16 ;
    Efis.Y=h/2-16;

    CCamera::CameraControl.SetPos(32*0, 32*0);
    //  CCamera::CameraControl.SetPos((int)Efis.X,(int)Efis.Y);
    //  CCamera::CameraControl.SetTarget(&Efis.X,&Efis.Y);
    
    



    /*
    
    if(Player.OnLoad("yoshi.png", 64, 64, 8) == false) {
        return false;
    }
    
    if(Player2.OnLoad("yoshi.png", 64, 64, 8) == false) {
        return false;
    }
    
    Player2.X = 100;
    Player.Flags = Player.Flags & ENTITY_FLAG_GHOST;
    
      */
    //CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
    //CCamera::CameraControl.SetTarget(&Player.X, &Player.Y);
   

    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if ( !CEntity::EntityList[i] ) continue;
        
        CEntity::EntityList[i]->OnRender(screen);
        
    }

    SDL_Flip(screen);

    return 0;

    
    return true;
}
