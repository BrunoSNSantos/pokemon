#include "inicio.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "personagens.h"
#include "text.h" 

int telaSelecaoPersonagem(SDL_Window* window, SDL_Renderer* renderer1) {
    // carregar as imagens
    SDL_Surface* bgSurface = IMG_Load("selecaopersonagem/fundoEscolha.png");
    if (!bgSurface) {
        printf("Erro ao carregar imagem de fundo: %s\n", IMG_GetError());
    }

    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer1, bgSurface);
    SDL_FreeSurface(bgSurface);

    if (!bgTexture) {
        printf("Erro ao criar textura a partir da superfície: %s\n", SDL_GetError());
    }

    SDL_Surface* boySurface = IMG_Load("selecaopersonagem/menino.png");
    if (!boySurface) {
        printf("Erro ao carregar a imagem do menino: %s\n", IMG_GetError());
        SDL_DestroyTexture(bgTexture);
    }

    SDL_Texture* boyTexture = SDL_CreateTextureFromSurface(renderer1, boySurface);
    SDL_FreeSurface(boySurface);

    if (!boyTexture) {
        printf("Erro ao criar textura da imagem do menino: %s\n", SDL_GetError());
        SDL_DestroyTexture(bgTexture);
    }

    SDL_Surface* girlSurface = IMG_Load("selecaopersonagem/menina.png");
    if (!girlSurface) {
        printf("Erro ao carregar a imagem da menina: %s\n", IMG_GetError());
        SDL_DestroyTexture(boyTexture);
        SDL_DestroyTexture(bgTexture);
    }

    SDL_Texture* girlTexture = SDL_CreateTextureFromSurface(renderer1, girlSurface);
    SDL_FreeSurface(girlSurface);

    if (!girlTexture) {
        printf("Erro ao criar textura da imagem da menina: %s\n", SDL_GetError());
        SDL_DestroyTexture(boyTexture);
        SDL_DestroyTexture(bgTexture);
    }

    SDL_Surface* arrowSurface = IMG_Load("selecaopersonagem/seta.png");
    if (!arrowSurface) {
        printf("Erro ao carregar a imagem da seta: %s\n", IMG_GetError());
        SDL_DestroyTexture(girlTexture);
        SDL_DestroyTexture(boyTexture);
        SDL_DestroyTexture(bgTexture);
    }

    SDL_Texture* arrowTexture = SDL_CreateTextureFromSurface(renderer1, arrowSurface);
    SDL_FreeSurface(arrowSurface);

    if (!arrowTexture) {
        printf("Erro ao criar textura da seta: %s\n", SDL_GetError());
        SDL_DestroyTexture(girlTexture);
        SDL_DestroyTexture(boyTexture);
        SDL_DestroyTexture(bgTexture);
    }

    // posições iniciais das imagens e seta
    SDL_Rect boyRect = {200, 100, 200, 400};
    SDL_Rect girlRect = {200, 100, 200, 400};
    SDL_Rect arrowRect = {775, 340, 45, 45};

    TTF_Font* font = TTF_OpenFont("fonte.ttf", 96); 
    if (!font) {
        printf("Erro ao carregar a fonte: %s\n", TTF_GetError());
        SDL_DestroyTexture(arrowTexture);
        SDL_DestroyTexture(girlTexture);
        SDL_DestroyTexture(boyTexture);
        SDL_DestroyTexture(bgTexture);
    }

    const char* textoLinha1 = "Voce e menino?";
    const char* textoLinha2 = "Ou voce e menina?";
    const char* textoMenino = "menino";
    const char* textoMenina = "menina";

    SDL_Event event;
    bool running = true;
    int arrowPosition = 0; // 0 = menino, 1 = menina
    float boyX = 200, girlX = -200;
    float transitionSpeed = 4.0f; // velocidade da transição

    Uint32 lastTime = 0;
    int charCount1 = 0;
    int charCount2 = 0;

    float scaleFactor = 3.5f; // fator de escala para aumentar o tamanho do texto

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN) {
                    running = false;
                }
                if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
                    if (arrowPosition == 0) { 
                        arrowPosition = 1;
                        arrowRect.y = 410;
                    }
                }
                if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
                    if (arrowPosition == 1) {
                        arrowPosition = 0;
                        arrowRect.y = 340;
                    }
                }
            }
        }

        SDL_RenderClear(renderer1);
        SDL_RenderCopy(renderer1, bgTexture, NULL, NULL);

        // transição das imagens de acordo com a posição da seta
        if (arrowPosition == 0) { // "menino"
            if (boyX < 200) boyX += transitionSpeed; // move o menino para a direita
            if (girlX > -200) girlX -= transitionSpeed; // move a menina para a esquerda
        } else { // "menina"
            if (girlX < 200) girlX += transitionSpeed; // move a menina para a direita
            if (boyX > -200) boyX -= transitionSpeed; // move o menino para a esquerda
        }

        boyRect.x = boyX;
        girlRect.x = girlX;

        SDL_RenderCopy(renderer1, boyTexture, NULL, &boyRect);
        SDL_RenderCopy(renderer1, girlTexture, NULL, &girlRect);

        // animação do texto
        animateText(renderer1, &lastTime, &charCount1, textoLinha1, 100, 550, scaleFactor);

        if (charCount1 >= strlen(textoLinha1)) {
            animateText(renderer1, &lastTime, &charCount2, textoLinha2, 100, 625, scaleFactor);
        }

        SDL_Color black = {0, 0, 0, 255};
        renderText(renderer1, font, textoMenino, black, 825, 330, scaleFactor); 
        renderText(renderer1, font, textoMenina, black, 825, 400, scaleFactor);
        SDL_RenderCopy(renderer1, arrowTexture, NULL, &arrowRect);
        SDL_RenderPresent(renderer1);
    }

    SDL_DestroyTexture(arrowTexture);
    SDL_DestroyTexture(girlTexture);
    SDL_DestroyTexture(boyTexture);
    SDL_DestroyTexture(bgTexture);
    TTF_CloseFont(font);

    return arrowPosition;
}