#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include "text.h"

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

SDL_Texture* load_texture(const char *path);
void render();
void render_text(const char *text, int x, int y);  
Move player_choose_move();
Move enemy_choose_move();
void renderHealthBar(int x, int y, int health, int displayed_health, int maxHealth);
void updateHealth (Pokemon *p);
bool init_SDL();
void createParticles(int x, int y, AttackType type);
void attack(Pokemon *attacker, Pokemon *defender, Move move);
void updateParticles();
void renderParticles();
void game_loop();
void close_SDL();
int skibidi(bool combate);