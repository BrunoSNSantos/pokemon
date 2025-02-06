#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "textures.h"
#include "player.h"
#include "colisao.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("Could not initialize SDL: %s\n", SDL_GetError());
    }
    window = SDL_CreateWindow("Pokemon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
    if(window == NULL){
        printf("Could not create window: %s\n", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer == NULL){
        printf("Could not create renderer: %s\n", SDL_GetError());
    }
    if(IMG_Init(IMG_INIT_PNG) == 0){
        printf("Could not initialize the image module: %s\n", IMG_GetError());
    }
}

void moveCamera(SDL_Rect* srcRect, Player* jogador){
    if(jogador->movingR && srcRect->x < 550 && !colisaoDireita(srcRect)){
        srcRect->x += 1;
    }
    if(jogador->movingL && srcRect->x > 85 && !colisaoEsquerda(srcRect)){
        srcRect->x -= 1;
    }
    if(jogador->movingU && !colisaoCima(srcRect)){
        srcRect->y -= 1;
    }
    if(jogador->movingD && srcRect->y < 288 && !colisaoBaixo(srcRect)){
        srcRect->y += 1;
    }
}

void handleEvents(SDL_Event* event, bool* quit, Player* jogador){
    while(SDL_PollEvent(event)){
        if(event->type == SDL_QUIT){
            *quit = true;
        }
        if(event->type == SDL_KEYDOWN){
            if(event->key.keysym.sym == SDLK_RIGHT && !jogador->movingL && !jogador->movingU && !jogador->movingD){
                jogador->movingR = true;
            }
            else if(event->key.keysym.sym == SDLK_LEFT && !jogador->movingR && !jogador->movingU && !jogador->movingD){
                jogador->movingL = true;
            }
            else if(event->key.keysym.sym == SDLK_UP && !jogador->movingD && !jogador->movingR && !jogador->movingL){
                jogador->movingU = true;
            }
            else if(event->key.keysym.sym == SDLK_DOWN && !jogador->movingU && !jogador->movingR && !jogador->movingL){
                jogador->movingD = true;
            }
            else if(event->key.keysym.sym == SDLK_d && !jogador->movingL && !jogador->movingU && !jogador->movingD){
                jogador->movingR = true;
            }
            else if(event->key.keysym.sym == SDLK_a && !jogador->movingR && !jogador->movingU && !jogador->movingD){
                jogador->movingL = true;
            }
            else if(event->key.keysym.sym == SDLK_w && !jogador->movingD && !jogador->movingR && !jogador->movingL){
                jogador->movingU = true;
            }
            else if(event->key.keysym.sym == SDLK_s && !jogador->movingU && !jogador->movingR && !jogador->movingL){
                jogador->movingD = true;
            }
        }
        else if(event->type == SDL_KEYUP){
            if(event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym == SDLK_d){
                jogador->movingR = false;
                jogador->idleState = 0;
            }
            else if(event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym == SDLK_a){
                jogador->movingL = false;
                jogador->idleState = 2;
            }
            else if(event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_w){
                jogador->movingU = false;
                jogador->idleState = 1;
            }
            else if(event->key.keysym.sym == SDLK_DOWN || event->key.keysym.sym == SDLK_s){
                jogador->movingD = false;
                jogador->idleState = 3;
            }
        }
    }
}

int main(int argc, char* argv[]){
    init();
    SDL_Event event;
    bool quit = false;
    SDL_Texture* backs = loadIMG(renderer, "Game Boy Advance - Pokemon Ruby Sapphire - Petalburg City.png");
    Player jogador;
    initializePlayer(&jogador, renderer);
    SDL_Rect srcRect, destRect, destRectc;
    srcRect.x = 407;
    srcRect.y = 128;
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
    int cFrame = 0;
    Uint32 lastTime = SDL_GetTicks();
    while(!quit){
        handleEvents(&event, &quit, &jogador);
        SDL_RenderClear(renderer);
        moveCamera(&srcRect, &jogador);
        SDL_RenderCopy(renderer, backs, &srcRect, &destRect);
        animatePlayer(&jogador, renderer, &cFrame, &destRectc, &lastTime);
        printf("%d %d\n", srcRect.x, srcRect.y);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}
