#include "inicio.h"
#include <stdbool.h>


void iniciar() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erro ao inicializar SDL_image: %s\n", IMG_GetError());
        SDL_Quit();
    }

    if (TTF_Init() == -1) {
        printf("Erro ao inicializar SDL_ttf: %s\n", TTF_GetError());
        IMG_Quit();
        SDL_Quit();
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erro ao inicializar SDL_mixer: %s\n", Mix_GetError());
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }
}

// Função para exibir a tela de início
bool telainicio(SDL_Window* window, SDL_Renderer* renderer) {
    // Carrega a imagem de fundo
    SDL_Surface* bgSurface = IMG_Load("inicial.png");
    if (!bgSurface) {
        printf("Erro ao carregar imagem de fundo: %s\n", IMG_GetError());
        return false;
    }
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);

    // Carrega e toca a música da tela de início
    Mix_Music* musicainicio = Mix_LoadMUS("start.mp3");
    if (musicainicio) {
        Mix_PlayMusic(musicainicio, -1);
    } else {
        printf("Erro ao carregar música: %s\n", Mix_GetError());
    }

    // Configuração da fonte e do texto
    TTF_Font* font = TTF_OpenFont("fonte.ttf", 72);
    if (!font) {
        printf("Erro ao carregar fonte: %s\n", TTF_GetError());
        SDL_DestroyTexture(bgTexture);
        return false;
    }
        SDL_Color textColor = {209, 202, 188}; // Branco
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Press ENTER to start", textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        textSurface->w = 320;
        textSurface->h = 63;

    SDL_Rect textRect = {480, 520, textSurface->w, textSurface->h};
    SDL_FreeSurface(textSurface);

    bool running = true;
    bool iniciarJogo = false;
    bool musicaTocando = true;
    SDL_Event event;

    // Loop da tela de início
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN) {
                    iniciarJogo = true;
                    running = false;
                }
                if (event.key.keysym.sym == SDLK_m) {
                    musicaTocando = !musicaTocando;
                    if (musicaTocando) {
                        Mix_PlayMusic(musicainicio, -1);
                    } else {
                        Mix_HaltMusic();
                    }
                }
            }
        }

        // Renderiza a tela de início
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bgTexture, NULL, NULL);
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_RenderPresent(renderer);
    }

    // Libera os recursos da tela de início
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(bgTexture);
    TTF_CloseFont(font);
    Mix_FreeMusic(musicainicio);

    return iniciarJogo;
}

