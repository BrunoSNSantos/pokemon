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
#include "combate.h"

//variáveis globais
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool dentro = true;
bool dentroCasa = false;
bool dialogoAtivado1 = false;
bool dialogoAtivado2 = false;
bool dialogoAtivado3 = false;
bool musicaTocando = true;
bool jaLutou = false;
int charCount3 = 0;
int charCount4 = 0;
int charCount5 = 0;

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

void mudarCenario(SDL_Texture** city,SDL_Rect* camera,int state,SDL_Rect* destRect){
    if(state == 1){
        *city = loadIMG(renderer, "assets/Sootopolis_City.png");
        camera->x = 413;
        camera->y = 720;
        Mix_Music* musicagym = Mix_LoadMUS("ginasio.mp3");
        Mix_PlayMusic(musicagym,-1);

    }
    else if(state == 0){
        *city = loadIMG(renderer, "assets/cidade.png");
        if(!dentroCasa){
            camera->x = 328;
            camera->y = 9;
        }else{
            camera->x = 410;
            camera->y = 135;
        }
        Mix_Music* musicaprincipal = Mix_LoadMUS("main.mp3");
        Mix_PlayMusic(musicaprincipal,-1);
    }
    else if(state == 3){
        *city = loadIMG(renderer,"assets/backs.png");
        camera->w = 240;
        camera->h = 160;
        camera->x = 263;
        camera->y = 130;
    }
    
}

//Função que move o jogador
int moveCameraFora(SDL_Rect* srcRect, Player* jogador){
    if(jogador->movingR && srcRect->x < 550 && !colisaoDireita(srcRect)){
        srcRect->x += 1;
    }
    if(jogador->movingL && srcRect->x > 85 && !colisaoEsquerda(srcRect)){
        srcRect->x -= 1;
    }
    if(jogador->movingU && !colisaoCima(srcRect)){
        srcRect->y -= 1;
        if(srcRect->x > 315 && srcRect->x < 336 && srcRect->y == -1){
            return 1;
        }
        if(srcRect->x > 398 && srcRect->x < 417 && srcRect->y == 127){
            return 2;
        }
    }
    if(jogador->movingD && srcRect->y < 288 && !colisaoBaixo(srcRect)){
        srcRect->y += 1;
    }
    return 0;
}

bool moveCameraDentro(SDL_Rect* srcRect, Player* jogador){
    if(!dialogoAtivado1 && !dialogoAtivado2){
        if(jogador->movingR && !colisaoDireitaG(srcRect)){
            srcRect->x += 1;
        }
        if(jogador->movingL && !colisaoEsquerdaG(srcRect)){
            srcRect->x -= 1;
        }
        if(jogador->movingU && !colisaoCimaG(srcRect)){
            srcRect->y -= 1;
            if(srcRect->y <= 390){
                dialogoAtivado1 = true;
            }
        }
        if(jogador->movingD && !colisaoBaixoG(srcRect)){
            srcRect->y += 1;
            if((srcRect->x > 399 && srcRect->x < 429) && srcRect->y > 726){
                printf("Returned true");
                return true;
            }
        }
    }
    return false;
}

bool moveCameraDentroCasa(SDL_Rect* srcRect, Player* jogador){
    if(!dialogoAtivado1 && !dialogoAtivado2 && !dialogoAtivado3){
        if(jogador->movingR){
            srcRect->x += 1;
        }
        if(jogador->movingL){
            srcRect->x -= 1;
        }
        if(jogador->movingU && !colisaCimaC(srcRect)){
            srcRect->y -= 1;  
            if(srcRect->x >235 && srcRect->x < 287 && srcRect->y < 95){
                dialogoAtivado3 = true;
            }
        }
        printf("%d %d\n", srcRect->x, srcRect->y);
        if(jogador->movingD){
            srcRect->y += 1;
            if(srcRect->x >250 && srcRect->x < 280 && srcRect->y > 127){
                return true;
            }
        }
    }
    return false;
}

//Função que lida com eventos
void handleEvents(SDL_Event* event, bool* quit, Player* jogador, Mix_Music* music, int charCount){
    while(SDL_PollEvent(event)){
        //Evento para fechar o jogo
        if(event->type == SDL_QUIT){
            *quit = true;
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
            else if(event->key.keysym.sym == SDLK_RETURN){
                if(charCount == 33 && !jaLutou){
                    Mix_Music* musicaBatalha = Mix_LoadMUS("battle.mp3");
                    Mix_Music* musicaVitoria = Mix_LoadMUS("vitoria.mp3");
                    Mix_PlayMusic(musicaBatalha, -1);
                    iniciarCombate(true);
                    Mix_PlayMusic(musicaVitoria, -1);
                    dialogoAtivado1 = false;
                    dialogoAtivado2 = true;
                    jaLutou = true;
                }
                if(charCount3 == 25 ){
                    dialogoAtivado2 = false;
                }
                if(charCount4 == 45){
                    dialogoAtivado3 = false;
                    charCount4 = 0;
                }
                if(charCount5 == 50){
                    dialogoAtivado1 = false;
                    charCount5 = 0;
                }
            }
            else if (event -> key.keysym.sym == SDLK_m) {
                musicaTocando = !musicaTocando;
                if (musicaTocando) {
                    if(dentro){
                        Mix_PlayMusic(music, -1);
                    }
                    else{
                        Mix_Music* musicagym = Mix_LoadMUS("ginasio.mp3");
                        Mix_PlayMusic(musicagym, -1);
                    }
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
    SDL_Texture* backs = loadIMG(renderer, "assets/cidade.png");
    SDL_Texture* dialogo = loadIMG(renderer,"assets/dialogo.png");
    const char* textoDialogo1 = "Parabens por chegar ate aqui! Mas sera que consegue";
    const char* textoDialogo2 = "vencer meu time? Vamos descobrir!";
    const char* textoDialogo3 = "parabens por me derrotar!";
    const char* textoDialogo4 = "Voce ja ouviu a lenda do treinador da cidade?";
    const char* textoDialogo5 = "Voce realmente derrotou o lendario treinador?";
    const char* textoDialogo6 = "Parabens, ainda nao acredito que voce me derrotou!";
    int charCount1 = 0;
    int charCount2 = 0;
    Player jogador;
    initializePlayer(&jogador, renderer,choice);
    SDL_Rect srcRect, destRect, destRectc;
    SDL_Rect destRectDialogo;
    destRectDialogo.x = 240;
    destRectDialogo.y = 570;
    destRectDialogo.w = 700;
    destRectDialogo.h = 150;
    srcRect.x = 406;
    srcRect.y = 143;
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
    while(!quit){
        handleEvents(&event, &quit, &jogador, musicaprincipal,charCount2);;
        SDL_RenderClear(renderer);
        if(dentro){
            if(!dentroCasa){
                int mudar = moveCameraFora(&srcRect, &jogador);
                if(mudar == 1){
                    mudarCenario(&backs,&srcRect,1,&destRect);
                    dentro = false;
                    srcRect.w = 220;
                }else if(mudar == 2){
                    mudarCenario(&backs,&srcRect,3,&destRect);
                    dentroCasa = true;
                }
                }
                if(dentroCasa){
                    if(moveCameraDentroCasa(&srcRect,&jogador)){
                        mudarCenario(&backs,&srcRect,0,&destRect);
                        dentroCasa = false;
                        srcRect.w = 270;
                        srcRect.h = 180;
                    }
                }
            }else{
            if(moveCameraDentro(&srcRect, &jogador)){
                mudarCenario(&backs,&srcRect,0,&destRect);
                dentro = true;
                srcRect.w = 270;
            }
        }
        SDL_RenderCopy(renderer, backs, &srcRect, &destRect);
        animatePlayer(&jogador, renderer, &cFrame, &destRectc, &lastTimePlayer);

        //Três condicionais que verificam se algum dos diálogos está ativado para exibir eles na tela
        if(dialogoAtivado1){
            SDL_RenderCopy(renderer,dialogo,NULL,&destRectDialogo);
            if(!jaLutou){
                animateText(renderer, &lastTimeText,&charCount1,textoDialogo1,280,600,2.0);
                if(charCount1 == strlen(textoDialogo1)){
                    animateText(renderer, &lastTimeText,&charCount2,textoDialogo2,280, 650,2.0);
            }
            }else{
                animateText(renderer, &lastTimeText,&charCount5,textoDialogo6,280,600,2.0);
            }
        }
        if(dialogoAtivado2){
            SDL_RenderCopy(renderer,dialogo,NULL,&destRectDialogo);
            animateText(renderer,&lastTimeText,&charCount3,textoDialogo3,280,600,2.0);
        }
        if(dialogoAtivado3){
            SDL_RenderCopy(renderer,dialogo,NULL,&destRectDialogo);
            if(!jaLutou){
                animateText(renderer,&lastTimeText,&charCount4,textoDialogo4,280,600,2.0);
            }else{
                animateText(renderer,&lastTimeText,&charCount4,textoDialogo5,280,600,2.0);
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}
