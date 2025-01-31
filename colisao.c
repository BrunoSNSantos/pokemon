#include "colisao.h"

bool colisaoX(SDL_Rect* camera){
    if((camera->y > 244 && camera->y < 374) && camera->x ==306){
        return true;
    }
    if((camera->y > 285 && camera->y < 366) && camera->x == 475){
        return true;
    }
    if((camera->y > 125 && camera->y < 177) && camera->x == 306){
        return true;
    }
    return false;
}

bool colisaoY(SDL_Rect* camera){
    return false;
}