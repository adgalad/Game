//
//  Interface.h
//  HelloSDL
//
//  Created by Carlos Spaggiari on 4/22/14.
//  Copyright (c) 2014 Student. All rights reserved.
//

#ifndef HelloSDL_Interface_h
#define HelloSDL_Interface_h

#include "CEntity.h"
#include "Define.h"
#include "CArea.h"
#include "Camara.h"
#include "CPlayer.h"



class Game
{
private:
    SDL_Surface *screen;
    bool running;
    bool FullScreen;
    bool dale;
    
    CEntity Efis;
    CEntity Chara;
    CEntity Fira;
    CEntity Brure;
    int     CurrentCharSurface;
    CMap    Map;
    CCamera Camara;
     
    CPlayer Player;
    CPlayer Player2;
    
public:
    Game();                                             // Constructor
    int SurfMenu(int option);                           // Cambiar Superficie del menu
    int OnExecute(SDL_Event *Event_Menu);               // Ciclo principal de la aplicacion

    int  OnGame();                                      // Ciclo principal del juego
    bool OnInit();                                      // Inicializar modulos de SDL
    bool OnEvent(SDL_Event *Event);                     // Acciones a tomar cuando ocurre un Evento
    void OnLoop();                                      // Acciones a tomar si no ocurre un Evento
    int  OnRender();                                    // Renderizar todos objetos
    void OnCleanup();                                   // Cerrar y Limpiar aputadores de SDL
    bool Fread();
};
Game::Game()
{
    dale=true;
    running = true;
    FullScreen=false;
    CurrentCharSurface = 0;
}

void Game::OnCleanup()
{
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if(!CEntity::EntityList[i]) continue;
        
        CEntity::EntityList[i]->OnCleanup();
    }
    
    CEntity::EntityList.clear();
    CArea::AreaControl.OnCleanup();
    SDL_FreeSurface(screen);
    SDL_Quit();
}

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


int Game::SurfMenu(int option)
{
    
    return 0;
}



int Game::OnExecute(SDL_Event *Event_Menu)
{
    OnInit();
    OnGame();
    SDL_Quit();
    return 0;
}


int Game::OnGame()
{
    
    SDL_Event Event;
    while(running)
    {
        while(SDL_PollEvent(&Event)){
            OnEvent(&Event);
        }
        OnLoop();
        OnRender();
    }
    return 0;
}


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
        
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if ( !CEntity::EntityList[i] ) continue;
        
        CEntity::EntityList[i]->OnRender(screen);
        
    }
    
    SDL_Flip(screen);
    
    return 0;
    
    
    return true;
}


void Game::OnLoop()
{
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if ( !CEntity::EntityList[i] ) continue;
        
        CEntity::EntityList[i]->OnLoop();
        
    }
    Efis.OnLoop();
    
    
}

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

#endif