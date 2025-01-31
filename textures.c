#include "textures.h"

SDL_Texture* loadIMG(SDL_Renderer* renderer,const char* path){
    SDL_Texture* texture = IMG_LoadTexture(renderer,path);
    return texture;
}