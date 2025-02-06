#include "inicio.h"
#include <stdbool.h>
    
    //função para iniciar o SDL e bibliotecas
    void iniciar(){
    
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
    //função da tela de início
    void exibirImagem(bool skibidi, SDL_Renderer* renderer){

        if(skibidi){
        SDL_Surface* bgSurface = IMG_Load("inicial.png");

        Mix_Music* musicainicio = Mix_LoadMUS("Tela_de_inicio.mp3");
        Mix_PlayMusic(musicainicio, -1);

        SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
        SDL_FreeSurface(bgSurface);

        TTF_Font* font = TTF_OpenFont("fonte.ttf", 72);
        SDL_Color textColor = {209, 202, 188}; // Branco
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Press ENTER to start", textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        textSurface->w = 320;
        textSurface->h = 63;

        SDL_Rect textRect;
        textRect.x = 480;
        textRect.y = 520;
        textRect.w = textSurface->w;
        textRect.h = textSurface->h;

        SDL_FreeSurface(textSurface);

        SDL_RenderCopy(renderer, bgTexture, NULL, NULL);

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        }

    }
int main(int argc, char* argv[]) {
    iniciar();

    // Cria a janela
    SDL_Window* window = SDL_CreateWindow(
        "Pokemon Ruby",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280, 720,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Erro ao criar janela: %s\n", SDL_GetError());
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Cria o renderizador
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        printf("Erro ao criar renderizador: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Carrega uma imagem de fundo
    SDL_Surface* bgSurface = IMG_Load("inicial.png");
    if (!bgSurface) {
        printf("Erro ao carregar imagem de fundo: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    // Carrega o audio da Tela de Inicio
    Mix_Music* musicainicio = Mix_LoadMUS("Tela_de_inicio.mp3");
    if (!musicainicio) {
    printf("Erro ao carregar música: %s\n", Mix_GetError());
    } 
    else {
    Mix_PlayMusic(musicainicio, -1);  // Tocar música em loop infinito
    }
    //play e pause da musica
    bool m = true;
    

    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);

    // Configura a fonte
    TTF_Font* font = TTF_OpenFont("fonte.ttf", 72);
    if (!font) {
        printf("Erro ao carregar fonte: %s\n", TTF_GetError());
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Renderiza o texto "Pressione Enter para começar"
    SDL_Color textColor = {209, 202, 188}; // Branco
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Press ENTER to start", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textSurface->w = 320;
    textSurface->h = 63;

    SDL_Rect textRect;
    textRect.x = 480;
    textRect.y = 520;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;

    SDL_FreeSurface(textSurface);

    // Loop principal da tela de início
    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0; // Sai do programa
            }

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
                running = 0; // Sai da tela de início (simulando transição para o jogo)
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m) {
                m = !m;
                if(!m){
                    Mix_HaltMusic();
                }
                else{
                    Mix_PlayMusic(musicainicio, -1);
                }
                
            }
        }
        
    

        // Renderiza o fundo
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bgTexture, NULL, NULL);

        // Renderiza o texto
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        // Atualiza a tela
        SDL_RenderPresent(renderer);
    }

    // Libera recursos
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(bgTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeMusic(musicainicio);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
