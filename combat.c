#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include "text.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//variáveis globais
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool movingR = false;
bool movingL = false;
SDL_Texture *background = NULL;
SDL_Texture *barra = NULL;
SDL_Texture* barra1 = NULL;
TTF_Font *font = NULL;
bool battleIsOver = false;

//variáveis para o efeito de balançar durante o combate
int shakeOffset = 0;
int shakeDuration = 0;

typedef struct {
    char name[50];
    int hp, displayed_hp, speed, attack, defense;
    SDL_Texture *sprite;
} Pokemon;

typedef enum {
    TYPE_ELETRIC,
    TYPE_ICE,
    TYPE_WATER,
} AttackType;

typedef struct {
    char name[50];
    int power;
    AttackType type;
} Move;

typedef struct {
    int x, y;
    int dx, dy;
    int lifetime;
    Uint8 r, g, b;
} Particle;

#define MAX_PARTICLES 20
Particle particles[MAX_PARTICLES];

Move pastMovePlayer = {"hi", 0};
Move pastMoveEnemy = {"hi",0};

//dados do jogador, adversário e golpes armazenados em arrays
Pokemon player = {"Pikachu", 250, 250, 30, 20 , 30, NULL};
Pokemon enemy = {"Blastoise", 270, 270, 15, 30, 10, NULL};
Move choque_do_trovao = {"Choque do Trovao", 20, TYPE_ELETRIC};
Move hidro_canhao = {"Hidro Canhao", 30, TYPE_WATER};
Move trovoada_de_choques = {"Trovoada de Choques", 35, TYPE_ELETRIC};
Move raio_congelante = {"Raio Congelante", 30, TYPE_ICE};


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

        render_text("1 - Choque do Trovao", 400, 390);
        render_text("2 - Trovoada de Choques", 400, 420);
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
        pastMoveEnemy = hidro_canhao;
        return hidro_canhao;
    } else {
        pastMoveEnemy = raio_congelante;
        return raio_congelante;
    }
}

void renderHealthBar(SDL_Renderer *renderer, int x, int y, int health, int displayed_health, int maxHealth) {
    // Health bar background
    SDL_Rect backgroundRect = {x, y, 157, 14};
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);  // Dark grey
    SDL_RenderFillRect(renderer, &backgroundRect);

    // Health bar foreground (based on current health)
    SDL_Rect healthRect = {x, y, (displayed_health * 157) / maxHealth, 13};
    if(displayed_health >= maxHealth/2){
        SDL_SetRenderDrawColor(renderer,0,255,0,255);
    }else{
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
    } // Red
    SDL_RenderFillRect(renderer, &healthRect);
}

//função para o hp diminuir gradualmente
void updateHealth (Pokemon *p) {
    if (p->displayed_hp > p->hp) {
        p->displayed_hp -= 2;  // Decresce gradualmente
        if (p->displayed_hp < p->hp) p->displayed_hp = p->hp; 
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
    font = TTF_OpenFont("assets/fonte.ttf", 12);
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return false;
    }

    //carregando os assets
    barra = load_texture("assets/barra.png");
    barra1 = load_texture("assets/barra1.png");
    background = load_texture("assets/battle_backgrounds.png");
    player.sprite = load_texture("assets/pikachu.png");
    enemy.sprite = load_texture("assets/blastoise_enemy.png");
    
    return renderer != NULL && background != NULL && player.sprite != NULL && enemy.sprite != NULL;
}

void createParticles(int x, int y, AttackType type) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].x = x + rand() % 20 - 10;
        particles[i].y = y + rand() % 20 - 10;
        particles[i].dx = (rand() % 5) - 2; 
        particles[i].dy = (rand() % 5) - 2;
        particles[i].lifetime = 10 + rand() % 10; 

        //definindo cor com base no tipo do ataque
        switch (type) {
            case TYPE_ELETRIC:
                particles[i].r=255;
                particles[i].g=255;
                particles[i].b=0; //amarelo
                break;
            case TYPE_ICE:
                particles[i].r=173;
                particles[i].g=216;
                particles[i].b=230; //azul
                break;
            case TYPE_WATER:
                particles[i].r=0;
                particles[i].g=0;
                particles[i].b=255; //azul claro
                break;
            default:
                particles[i].r=255;
                particles[i].g=255;
                particles[i].b=255;
                break;
        }
    }
}

//Função para calcular o dano dos ataques no jogo
void attack(Pokemon *attacker, Pokemon *defender, Move move) {
    int damage = move.power + (attacker->attack - defender->defense);
    if (damage<0) damage = 1;
    
    if(!battleIsOver){
        defender->hp-=damage;
        createParticles ((defender == &enemy) ? 460 : 100, (defender == &enemy) ? 80 : 260, move.type); //cria particulas
    }
    if (defender->hp<0) defender->hp = 0;

    shakeDuration = 10;
}

void updateParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].lifetime > 0) {
            particles[i].x += particles[i].dx;
            particles[i].y += particles[i].dy;
            particles[i].lifetime--;
        }
    }
}

void renderParticles(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255); 
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].lifetime > 0) {
            SDL_SetRenderDrawColor(renderer, particles[i].r, particles[i].g, particles[i].b, 255);
            SDL_Rect rect = {particles[i].x, particles[i].y, 4, 4};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

// Função para renderizar
int charCount = 0;
const char* textoDialoogo = "teste";
void render() {
    SDL_RenderClear(renderer);

    //criando efeito de balançar ao levar dano
    if (shakeDuration>0) {
        shakeOffset = (rand() % 6) - 3;
        shakeDuration--;
    } else {
        shakeOffset = 0;
    }

    SDL_Rect srcRect = {2,21,242,114};
    SDL_Rect destRectBackgroung = {0, -80, 640, 480};
    SDL_RenderCopy(renderer, background, &srcRect, &destRectBackgroung);
    SDL_Rect srcRectbarra = {297, 56, 240, 46};
    SDL_Rect srcRectvida = {3,3,93,27};
    SDL_Rect destRectbarra = {0, 358, 640, 122};
    SDL_Rect destRectvida = {5, 125, 300, 80};
    SDL_Rect destRectvida2 = {345, 280, 300, 80};
    SDL_Rect destRectbarra2 = {0, 0, 320, 122};

    SDL_Rect src_rect = {0, 0, 640, 480};
    SDL_Rect player_position = {60 + shakeOffset, 220, 200, 200}; //Retangulo que representa a posição do jogador
    SDL_Rect enemy_position = {360 + shakeOffset, 10, 200, 200}; //Retangulo que representa a posição do inimigo
    SDL_RenderCopy (renderer, player.sprite, NULL, &player_position);
    SDL_RenderCopy (renderer, enemy.sprite, NULL, &enemy_position);
    updateHealth(&player);
    updateHealth(&enemy);
    SDL_RenderCopy (renderer, barra, &srcRectbarra, &destRectbarra);
    SDL_RenderCopy (renderer, barra, &srcRectvida, &destRectvida);
    SDL_RenderCopy (renderer, barra, &srcRectvida, &destRectvida2);
    SDL_RenderCopy (renderer, barra1, &srcRectbarra, &destRectbarra2);

    if (pastMovePlayer.power != 0 && !battleIsOver) {
        char playerMoveText[100];
        sprintf(playerMoveText, "Pikachu usou %s!", pastMovePlayer.name);
        render_text(playerMoveText, 20, 400);

        char enemyDamageText[100];
        sprintf(enemyDamageText, "Blastoise tomou %d dano.", pastMovePlayer.power + 10);
        render_text(enemyDamageText, 20, 430);
    }

    if (pastMoveEnemy.power != 0 && !battleIsOver) {
        char enemyMoveText[100];
        sprintf(enemyMoveText, "Blastoise usou %s!", pastMoveEnemy.name);
        render_text(enemyMoveText, 20, 30);

        char playerDamageText[100];
        sprintf(playerDamageText, "Pikachu tomou %d dano.", pastMoveEnemy.power);
        render_text(playerDamageText, 20, 60);
    }
    
    renderHealthBar(renderer, 130, 172, enemy.hp, enemy.displayed_hp, 270);
    renderHealthBar(renderer,469,328,player.hp, player.displayed_hp, 250);
    if(battleIsOver){
        if(player.hp == 0){
            render_text("Blastoise ganhou", 20, 400);
        }
        else{
            render_text("Pikachu ganhou", 20, 400);
        }
    }
    updateParticles();
    renderParticles(renderer);

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
            pastMovePlayer = chosenMove;
            
            while (enemy.displayed_hp>enemy.hp) {
                render();
                SDL_Delay(10);
            }

            if (enemy.hp>0) {
                Move chosenMove = enemy_choose_move();
                attack(&enemy, &player, chosenMove);
                pastMoveEnemy = chosenMove;

                while (player.displayed_hp>player.hp) {
                    render();
                    SDL_Delay(10);
                }
            }
        } else {
            Move chosenMove = enemy_choose_move();
            attack(&enemy, &player, chosenMove);
            pastMoveEnemy = chosenMove;

            while (player.displayed_hp>player.hp) {
                render();
                SDL_Delay(10);
            }

            if (player.hp>0) {
                Move chosenMove = player_choose_move();
                attack(&player, &enemy, chosenMove);
                pastMovePlayer = chosenMove;

                while (enemy.displayed_hp>enemy.hp) {
                    render();
                    SDL_Delay(10);
                }

            }
        }
        if (player.hp == 0 || enemy.hp == 0) {
            if(player.hp == 0 ) printf("PIkachu lost\n");
            else printf("Blastoise lost\n");
            printf("Battle Over!");
            battleIsOver = true;
        }

        SDL_Delay(16);
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