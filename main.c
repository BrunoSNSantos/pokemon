#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "textures.h"
#include "player.h"
#include "colisao.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;



//funções para inicializar o SDL
void init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("Could not initialize SDL: %s\n", SDL_GetError());
    }
    //Cria a janela
    window = SDL_CreateWindow("Pokemon",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1280,720,0);
    if(window == NULL){
        printf("Could not create window: %s\n",SDL_GetError());
    }
    //Cria o renderizador
    renderer = SDL_CreateRenderer(window,-1,0);
    if(renderer == NULL){
        printf("Could not create renderer: %s\n",SDL_GetError());
    }
    //Inicia a biblioteca de imagens do SDL
    if(IMG_Init(IMG_INIT_PNG) == 0){
        printf("Could not initialize the image module:%s\n",IMG_GetError());
    }
}

//Função para movimento
void moveCamera(SDL_Rect* srcRect,Player* jogador){
    //Movimento para a direita
    if(jogador->movingR && srcRect->x < 505 && !colisaoX(srcRect)){
        srcRect->x += 1;
    }
    //Movimento para a esquerda
    if(jogador->movingL && srcRect->x > 8){
        srcRect->x -= 1;
    }
    //Movimento para cima
    if(jogador->movingU){
        srcRect->y -= 1;
    }
    //Movimento para baixo
    if(jogador->movingD){
        srcRect->y += 1;
    }
}

//Função para lidar com eventos
void handleEvents(SDL_Event* event, bool* quit,Player* jogador){
    //Loop para lidar com os eventos à medida que eles acontecem
    while(SDL_PollEvent(event)){
        //Evento para fechar o jogo
        if(event->type == SDL_QUIT){
            *quit = true;
        }
        //Evento ao pressionar tecla
        if(event->type == SDL_KEYDOWN){
            //Checa se a letra D foi pressionada
            if(event->key.keysym.sym == SDLK_d && !jogador->movingL && !jogador->movingU && !jogador->movingD){
                jogador->movingR = true;
            }
            //Checa se a letra A foi pressionada
            else if(event->key.keysym.sym == SDLK_a && !jogador->movingR && !jogador->movingU && !jogador->movingD){
                jogador->movingL = true;
            }
            //Checa se a letra W foi pressionada
            else if(event->key.keysym.sym == SDLK_w && !jogador->movingD && !jogador->movingR && !jogador->movingL){
                jogador->movingU = true;
            }
            //Checa se a letra S foi pressionada
            else if(event->key.keysym.sym == SDLK_s && !jogador->movingU && !jogador->movingR && !jogador->movingL){
                jogador->movingD = true;
            }
        }
        //Evento ao soltar tecla
        else if(event->type == SDL_KEYUP){
            //Checa se a letra D foi solta
            if(event->key.keysym.sym == SDLK_d){
                jogador->movingR = false;
                jogador->idleState = 0;
            }
            //Checa se a letra A foi solta
            else if(event->key.keysym.sym == SDLK_a){
                jogador->movingL = false;
                jogador->idleState = 2;
            }
            //Checa se a letra W foi solta
            else if(event->key.keysym.sym == SDLK_w){
                jogador->movingU = false;
                jogador->idleState = 1;
            }
            //Checa se a letra S foi solta
            else if(event->key.keysym.sym == SDLK_s){
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
    SDL_Texture* backs = loadIMG(renderer,"backs.png");
    Player jogador;
    initializePlayer(&jogador,renderer);
    SDL_Rect srcRect, destRect, destRectc;
    srcRect = (SDL_Rect){217,355,270,180};
    destRect = (SDL_Rect){0,0,1280,720};
    destRectc = (SDL_Rect){500,500,96,96};
    int cFrame = 0;
    Uint32 lastTime = SDL_GetTicks();
    while(!quit){
        handleEvents(&event,&quit,&jogador);
        SDL_RenderClear(renderer);
        moveCamera(&srcRect,&jogador);
        SDL_RenderCopy(renderer,backs,&srcRect,&destRect);
        animatePlayer(&jogador,renderer,&cFrame,&destRectc,&lastTime);
        printf("%d %d\n",srcRect.x,srcRect.y);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}