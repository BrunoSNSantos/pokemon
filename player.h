#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <stdbool.h>
#include "textures.h"

typedef struct{
    bool movingR;
    bool movingL;
    bool movingU;
    bool movingD;
    int idleState;
    SDL_Texture* idle;
    SDL_Texture* right;
    SDL_Texture* left;
    SDL_Texture* up;
    SDL_Texture* down;
} Player;

void initializePlayer(Player* player, SDL_Renderer* renderer, bool isBoy);;
void animatePlayer(Player* player,SDL_Renderer* renderer, int* cFrame,SDL_Rect* destRect,Uint32* lastTime);
