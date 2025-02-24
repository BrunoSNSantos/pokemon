#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//variáveis globais
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool movingR = false;
bool movingL = false;
SDL_Texture *background = NULL;
SDL_Texture *barra = NULL;
TTF_Font *font = NULL;

typedef struct {
    char name[50];
    int hp, speed, attack, defense;
    SDL_Texture *sprite;
} Pokemon;

typedef struct {
    char name[50];
    int power;
} Move;

//dados do jogador, adversário e golpes armazenados em arrays
Pokemon player = {"Pikachu", 100, 30, 20 , 30, NULL};
Pokemon enemy = {"Blastoise", 120, 15, 30, 10, NULL};
Move choque_do_trovao = {"Choque do Trovao", 20};
Move hidro_canhao = {"Hidro Canhao", 30};
Move trovoada_de_choques = {"Trovoada de Choques", 25};
Move raio_congelante = {"Raio Congelante", 35};

//Função para carregar as texturas
SDL_Texture* load_texture(const char *path) {
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        printf("Failed to load image: %s\n", IMG_GetError());
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

//Função para o usuário escolher o golpe usado
void render();
void render_text(const char *text, int x, int y);  
Move player_choose_move() {
    SDL_Event e;
    bool move_chosen = false;
    Move selectedMove = choque_do_trovao;

    while(!move_chosen) {
        render();

        SDL_Rect moveBox = {50, 350, 540, 100};

        render_text("1 - Choque do Trovao", 60, 360);
        render_text("2 - Trovoada de Choques", 60, 390);

        SDL_RenderPresent(renderer);

        while (SDL_WaitEvent(&e)) {
        if (e.type == SDL_QUIT) exit(0);
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_1:
                        selectedMove = choque_do_trovao;
                        move_chosen = true;
                        break;
                    case SDLK_2:
                        selectedMove = trovoada_de_choques;
                        move_chosen = true;
                        break;
                }
                break;
            }
        }
    }
    return selectedMove;
}

//Função para randomizar os golpes utilizados pelo oponente
Move enemy_choose_move() {
    int choice = rand() % 2;
    if (choice == 0) {
        return hidro_canhao;
    } else {
        return raio_congelante;
    }
}

//função para renderizar texto
void render_text(const char *text, int x, int y) {
    if (!font) {
        printf("Font is not loaded!\n");
        return;
    }

    SDL_Color color = {0, 0, 0};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        printf("Failed to create text surface: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textRect = {x, y, surface->w, surface->h};
    textRect.w *=1.6;
    textRect.h *=1.6;
    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

//Função para inicializar o SDL
bool init_SDL() {
    //Tratamento de erro para a caso a janela não inicialize
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0 || IMG_Init(IMG_INIT_PNG) == 0) { //Em ordem, permitem a criação de janelas, renderização gráfica e po uso de imagens (IMG_INIT_PNG verifica se é possível usar PNG)
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }   
    window = SDL_CreateWindow("Pokemon battle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); //Cria uma janela chamada "Pokemon Battle" e, em ordem, os parametros garantem: posição ao centro da tela, medidas da janela e que a janela será visível
    if (!window) return false;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //Cria um renderizador para permitir a criação de imagens dentro da janela

    //inicializando o TTF
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        return false;
    }
    
    //carregando fonte
    font = TTF_OpenFont("assets/fonte.ttf", 24);
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return false;
    }

    //carregando os assets
    barra = load_texture("assets/barra.png");
    background = load_texture("assets/battle_backgrounds.png");
    player.sprite = load_texture("assets/pikachu.png");
    enemy.sprite = load_texture("assets/blastoise_enemy.png");
    
    return renderer != NULL && background != NULL && player.sprite != NULL && enemy.sprite != NULL;
}

//Função para calcular o dano dos ataques no jogo
void attack(Pokemon *attacker, Pokemon *defender, Move move) {
    int damage = move.power + (attacker->attack - defender->defense);
    if (damage<0) {
        damage=1;
    }
    defender->hp-=damage;
    if (defender->hp<0) {
        defender->hp = 0;
    }
    printf("%s used %s! %s took %d damage and has %d HP left.\n",
        attacker->name, move.name, defender->name, damage, defender->hp);
}

// Função para renderizar
void render() {
    SDL_RenderClear(renderer);
    SDL_Rect srcRect = {2,21,242,114};
    SDL_Rect destRectBackgroung = {0, -50, 640, 480};
    SDL_RenderCopy(renderer, background, &srcRect, &destRectBackgroung);
    SDL_Rect srcRectbarra = {297, 56, 240, 46};
    SDL_Rect destRectbarra = {0, 358, 640, 122};

    SDL_Rect src_rect = {0, 0, 640, 480};
    SDL_Rect player_position = {60, 250, 200, 200}; //Retangulo que representa a posição do jogador
    SDL_Rect enemy_position = {360, 40, 200, 200}; //Retangulo que representa a posição do inimigo
    SDL_RenderCopy (renderer, player.sprite, NULL, &player_position);
    SDL_RenderCopy (renderer, enemy.sprite, NULL, &enemy_position);
    SDL_RenderCopy (renderer, barra, &srcRectbarra, &destRectbarra);

    SDL_RenderPresent(renderer);
}

//loop do jogo
void game_loop() {
    SDL_Event e;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }
        render();
        if (player.speed>enemy.speed) {
            Move chosenMove = player_choose_move();
            attack(&player, &enemy, chosenMove);
            if (enemy.hp>0) {
                Move chosenMove = enemy_choose_move();
                attack(&enemy, &player, chosenMove);
            }
        } else {
            Move chosenMove = enemy_choose_move();
            attack(&enemy, &player, chosenMove);
            if (player.hp>0) {
                Move chosenMove = player_choose_move();
                attack(&player, &enemy, chosenMove);
            }
        }
        if (player.hp == 0 || enemy.hp == 0) {
            printf("Battle Over!");
            running = false;
        }

        SDL_Delay(1000);
    }
}

//Função para fechar a janela do jogo
void close_SDL() {
    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(player.sprite);
    SDL_DestroyTexture(enemy.sprite);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    if (!init_SDL()) return -1;
    game_loop();
    close_SDL();
    return 0;
}