#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

//variáveis globais
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool movingR = false;
bool movingL = false;

//dados do jogador, adversário e golpes armazenados em arrays
Pokemon player = {"Pikachu", 100, 30, 20 , 30};
Pokemon enemy = {"Blastoise", 120, 15, 30, 10};
Move choque_do_trovao = {"Choque do Trovão", 20};
Move hidro_canhao = {"Hidro Canhão", 30};

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
    printf("%s used %s! %s took %d damage", attacker->name, move.name, defender->hp, move.damage);
}

//loop do jogo
void game_loop() {
    SDL_Event e;
    while (running) {
        while (SDL_PoolEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running == false;
            }
        }
        if (player.speed>enemy.speed) {
            attack(&player, &enemy, choque_do_trovao);
            if (enemy.hp>0) {
                attack(&enemy, &player, hidro_canhao);
            }
        } else {
            attack(&enemy, &player, hidro_canhao);
            if (player.hp>0) {
                attack(&player, &enemy, choque_do_trovao);
            }
        }

        if (player.hp == 0 || enemy.hp == 0) {
            printf("Battle Over!");
        }

        SDL_Delay(1000);
    }
}

