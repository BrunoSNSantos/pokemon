#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "inicio.h"
#include "textures.h"
#include "player.h"
#include "colisao.h"
#include "text.h"
#include "personagens.h"

//variáveis globais
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool dentro = true;
bool dialogoAtivado = false;
bool musicaTocando = true;

void init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("Could not initialize SDL: %s\n", SDL_GetError());
    }
    if(TTF_Init() == -1){
        printf("Erro na inicialização do TTF: %s\n", TTF_GetError());
    }
    //Cria a janela
    window = SDL_CreateWindow("Pokemon",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1280,720,0);
    if(window == NULL){
        printf("Could not create window: %s\n", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer == NULL){
        printf("Could not create renderer: %s\n", SDL_GetError());
    }
    //Inicia a biblioteca de imagens do SDL
    if(IMG_Init(IMG_INIT_PNG) == 0){
        printf("Could not initialize the image module: %s\n", IMG_GetError());
    }
}

void mudarCenario(SDL_Texture** city,SDL_Rect* camera,bool state){
    if(state){
        *city = loadIMG(renderer, "Sootopolis Cityy.png");
        camera->x = 413;
        camera->y = 720;
    }else{
        *city = loadIMG(renderer, "cidade.png");
        camera->x = 328;
        camera->y = 9;
    }
    
}

//Função que move o jogador
bool moveCameraFora(SDL_Rect* srcRect, Player* jogador){
    if(jogador->movingR && srcRect->x < 550 && !colisaoDireita(srcRect)){
        srcRect->x += 1;
    }
    if(jogador->movingL && srcRect->x > 85 && !colisaoEsquerda(srcRect)){
        srcRect->x -= 1;
    }
    if(jogador->movingU && !colisaoCima(srcRect)){
        srcRect->y -= 1;
        if(srcRect->x > 315 && srcRect->x < 336 && srcRect->y == -1){
            return true;
        }
    }
    if(jogador->movingD && srcRect->y < 288 && !colisaoBaixo(srcRect)){
        srcRect->y += 1;
    }
    return false;
}

bool moveCameraDentro(SDL_Rect* srcRect, Player* jogador){
    if(!dialogoAtivado){
        if(jogador->movingR && !colisaoDireitaG(srcRect)){
            srcRect->x += 1;
        }
        if(jogador->movingL && !colisaoEsquerdaG(srcRect)){
            srcRect->x -= 1;
        }
        if(jogador->movingU && !colisaoCimaG(srcRect)){
            srcRect->y -= 1;
            if(srcRect->y <= 390){
                dialogoAtivado = true;
            }
        }
        if(jogador->movingD && !colisaoBaixoG(srcRect)){
            srcRect->y += 1;
            if(srcRect->x >=401 && srcRect->x <=425 && srcRect->y == 727){
                return true;
            }
        }
    }
    return false;
}

//Função que lida com eventos
void handleEvents(SDL_Event* event, bool* quit, Player* jogador, Mix_Music* music ){
    while(SDL_PollEvent(event)){
        //Evento para fechar o jogo
        if(event->type == SDL_QUIT){
            *quit = true;
            break;
        }
        
        //Evento ao pressionar tecla
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
            else if (event -> key.keysym.sym == SDLK_m) {
                musicaTocando = !musicaTocando;
                if (musicaTocando) {
                    Mix_PlayMusic(music, -1);
                } else {
                    Mix_HaltMusic();
                }
            }
        }
        //Evento ao soltar tecla
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

//Função principal
int main(int argc, char* argv[]){
    iniciar();

    SDL_Window* window1 = SDL_CreateWindow(
        "Pokemon Ruby",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720, SDL_WINDOW_SHOWN
    );

    if (!window1) {
        printf("Erro ao criar janela: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer1 = SDL_CreateRenderer(window1, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer1) {
        printf("Erro ao criar renderizador: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return 1;
    }

    // Chama a função da tela de início e verifica se o jogador deseja iniciar
    if (!telainicio(window1, renderer1)) {
        printf("Saindo do jogo...\n");
        SDL_DestroyRenderer(renderer1);
        SDL_DestroyWindow(window1);
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 0;
    }

    // tela de selecao de personagem
    int choice = telaSelecaoPersonagem(window1, renderer1);

    // Libera os recursos do jogo
    SDL_DestroyRenderer(renderer1);
    SDL_DestroyWindow(window1);
    init();
    Mix_Music* musicaprincipal = Mix_LoadMUS("main.mp3");
    if (musicaprincipal) {
        Mix_PlayMusic(musicaprincipal, -1);
    } else {
        printf("Erro ao carregar música: %s\n", Mix_GetError());
    }
    SDL_Event event;
    bool quit = false;
    SDL_Texture* backs = loadIMG(renderer, "cidade.png");
    SDL_Texture* dialogo = loadIMG(renderer,"dialogo.png");
    const char* textoDialogo1 = "Parabens por chegar ate aqui! Mas sera que consegue";
    const char* textoDialogo2 = "vencer meu time? Vamos descobrir!";
    int charCount1 = 0;
    int charCount2 = 0;
    Player jogador;
    initializePlayer(&jogador, renderer, !choice);
    SDL_Rect srcRect, destRect, destRectc;
    SDL_Rect destRectDialogo;
    destRectDialogo.x = 240;
    destRectDialogo.y = 570;
    destRectDialogo.w = 700;
    destRectDialogo.h = 150;
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
    Uint32 lastTimePlayer = SDL_GetTicks();
    Uint32 lastTimeText = SDL_GetTicks();
    float scaleFactor = 2.0f;
    while(!quit){
        handleEvents(&event, &quit, &jogador, musicaprincipal);;
        SDL_RenderClear(renderer);
        if(dentro){
            if(moveCameraFora(&srcRect, &jogador)){
                mudarCenario(&backs,&srcRect,true);
                dentro = false;
                srcRect.w = 220;
            }
        }else{
            if(moveCameraDentro(&srcRect, &jogador)){
                mudarCenario(&backs,&srcRect,false);
                dentro = true;
                srcRect.w = 270;
            }
        }
        SDL_RenderCopy(renderer, backs, &srcRect, &destRect);
        animatePlayer(&jogador, renderer, &cFrame, &destRectc, &lastTimePlayer);
        if(dialogoAtivado){
            SDL_RenderCopy(renderer,dialogo,NULL,&destRectDialogo);
            animateText(renderer, &lastTimeText, &charCount1, textoDialogo1, 280, 600, scaleFactor);
            if(charCount1 == strlen(textoDialogo1)){
                animateText(renderer, &lastTimeText, &charCount2, textoDialogo2, 280, 650, scaleFactor);
            }
        }
        printf("%d %d\n", srcRect.x, srcRect.y);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}