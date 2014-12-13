
#include "Surface.h"


Csurface::Csurface()
{
    
}



SDL_Surface * Csurface::OnLoad(char* file)
{
    SDL_Surface *Surf,*Surf_Return;
    
    if ((Surf = IMG_Load(file))==NULL){
        return NULL;
        
    }
    Surf_Return = SDL_DisplayFormat(Surf);
    SDL_FreeSurface(Surf);
    return Surf_Return;
    
}

bool Csurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y)
{
    if(Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
}
    
    SDL_Rect DestR;
    
    DestR.x = X;
    DestR.y = Y;
    
    SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);
    
    return true;
}

bool Csurface::OnDraw(SDL_Surface *Surf_Dest, SDL_Surface *Surf_Src,
                      int X, int Y, int X2, int Y2, int W, int H)
{
    if(Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    }
    
    SDL_Rect DestR;
    
    DestR.x = X;
    DestR.y = Y;
    
    SDL_Rect SrcR;
    
    SrcR.x = X2;
    SrcR.y = Y2;
    SrcR.w = W;
    SrcR.h = H;
    
    SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);
    
    return true;
    
}
bool Csurface::Transparent(SDL_Surface* Surf_Dest, int R, int G, int B) {
    if(Surf_Dest == NULL) {
        return false;
    }
    
    SDL_SetColorKey(Surf_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL,
                    SDL_MapRGB(Surf_Dest->format, R, G, B));
    
    return true;
}




