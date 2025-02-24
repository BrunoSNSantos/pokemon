#include "inicio.h"
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    iniciar();

    SDL_Window* window = SDL_CreateWindow(
        "Pokemon Ruby",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720, SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Erro ao criar janela: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erro ao criar renderizador: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return 1;
    }

    // Chama a função da tela de início e verifica se o jogador deseja iniciar
    if (!telainicio(window, renderer)) {
        printf("Saindo do jogo...\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 0;
    }

    // Aqui iniciaria o jogo após a tela de início
    printf("Iniciando o jogo...\n");

    // Libera os recursos do jogo
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
