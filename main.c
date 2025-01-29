#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

//variáveis globais
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool movingR = false;
bool movingL = false;

//funções para inicializar o SDL
void init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("Could not initialize SDL: %s\n", SDL_GetError());
    }
    window = SDL_CreateWindow("Pokemon",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1280,720,0);
    if(window == NULL){
        printf("Could not create window: %s\n",SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window,-1,0);
    if(renderer == NULL){
        printf("Could not create renderer: %s\n",SDL_GetError());
    }
    if(IMG_Init(IMG_INIT_PNG) == 0){
        printf("Could not initialize the image module:%s\n",IMG_GetError());
    }
}

//carregar a textura no SDL 
SDL_Texture* loadImg(const char* path){
    SDL_Texture *texture = IMG_LoadTexture(renderer,path);
    return texture;
}

void moveCamera(SDL_Rect* srcRect){
    if(movingR && srcRect->x < 505){
        srcRect->x += 1;
    }
    if(movingL && srcRect->x > 8){
        srcRect->x -= 1;
    }
}

void handleEvents(SDL_Event* event, bool* quit){
    while(SDL_PollEvent(event)){
        if(event->type == SDL_QUIT){
            *quit = true;
        }
        if(event->type == SDL_KEYDOWN){
            if(event->key.keysym.sym == SDLK_d && movingL == false){
                movingR = true;
            }
            else if(event->key.keysym.sym = SDLK_a && movingR == false){
                movingL = true;
            }
        }
        else if(event->type == SDL_KEYUP){
            if(event->key.keysym.sym == SDLK_d){
                movingR = false;
            }
            else if(event->key.keysym.sym == SDLK_a){
                movingL = false;
            }
        }
    }
}

int main(int argc, char* argv[]){
    init();
    SDL_Event event;
    bool quit = false;
    SDL_Texture* backs = loadImg("backs.png");
    SDL_Texture* idle = loadImg("IdleR.png");
    SDL_Rect srcRect, destRect, destRectc;
    srcRect.x = 217;
    srcRect.y = 361;
    srcRect.w = 270;
    srcRect.h = 180;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = 1280;
    destRect.h = 720;
    destRectc.x = 500;
    destRectc.y = 500;
    destRectc.w = 96;
    destRectc.h = 90;
    while(!quit){
        handleEvents(&event,&quit);
        SDL_RenderClear(renderer);
        moveCamera(&srcRect);
        SDL_RenderCopy(renderer,backs,&srcRect,&destRect);
        printf("%d ",srcRect.x);
        printf("%d\n",srcRect.y);
        SDL_RenderCopy(renderer,idle,NULL,&destRectc);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}