#include "colisao.h"

bool colisaoX(SDL_Rect* rect){
    if((rect->y > 244 && rect->y < 374) && rect->x ==306){
        return true;
    }
    return false;
}

bool colisaoY(SDL_Rect* rect){
    return false;
}