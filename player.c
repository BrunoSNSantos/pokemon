#include "player.h"

void initializePlayer(Player* player, SDL_Renderer* renderer, bool isBoy) {
    player->movingR = false;
    player->movingL = false;
    player->movingU = false;
    player->movingD = false;

    if (!isBoy) {
        // menino
        player->right = loadIMG(renderer, "assets/WalkR.png");
        player->left = loadIMG(renderer, "assets/WalkL.png");
        player->up = loadIMG(renderer, "assets/WalkU.png");
        player->down = loadIMG(renderer, "assets/WalkD.png");
    } else {
        // menina
        player->right = loadIMG(renderer, "assets/WalkR - G.png");
        player->left = loadIMG(renderer, "assets/WalkL - G.png");
        player->up = loadIMG(renderer, "assets/WalkU - G.png");
        player->down = loadIMG(renderer, "assets/WalkD - G.png");
    }

    player->idleState = 0;
}

void animatePlayer(Player* player,SDL_Renderer* renderer, int* cFrame,SDL_Rect* destRect,Uint32* lastTime){
    if(!player->movingL && !player->movingR && !player->movingU && !player->movingD){
        if(player->idleState == 0){
            SDL_Rect srcRect = {0, 0, 64, 60};
            SDL_RenderCopy(renderer,player->right,&srcRect,destRect);
        }
        else if(player->idleState == 1){
            SDL_Rect srcRect = {0, 0, 64, 60};
            SDL_RenderCopy(renderer,player->up,&srcRect,destRect);
        }
        else if(player->idleState == 2){
            SDL_Rect srcRect = {0, 0, 64, 60};
            SDL_RenderCopy(renderer,player->left,&srcRect,destRect);
        }
        else if(player->idleState == 3){
            SDL_Rect srcRect = {0, 0, 64, 60};
            SDL_RenderCopy(renderer,player->down,&srcRect,destRect);
        }
    }
    else if(player->movingR){
        if(SDL_GetTicks() - *lastTime > 100){
            *cFrame = (*cFrame + 1)%4;
            *lastTime = SDL_GetTicks();
        }
        SDL_Rect srcRect = {*cFrame * 64, 0, 64, 60};
        SDL_RenderCopy(renderer,player->right,&srcRect,destRect);
    }
    else if(player->movingL){
        if(SDL_GetTicks() - *lastTime > 100){
            *cFrame = (*cFrame + 1)%4;
            *lastTime = SDL_GetTicks();
        }
        SDL_Rect srcRect = {*cFrame * 64, 0, 64, 60};
        SDL_RenderCopy(renderer,player->left,&srcRect,destRect);
    }
    else if(player->movingU){
        if(SDL_GetTicks() - *lastTime > 100){
            *cFrame = (*cFrame + 1)%4;
            *lastTime = SDL_GetTicks();
        }
        SDL_Rect srcRect = {*cFrame * 64, 0, 64, 60};
        SDL_RenderCopy(renderer,player->up,&srcRect,destRect);
    }
    else if(player->movingD){
        if(SDL_GetTicks() - *lastTime > 100){
            *cFrame = (*cFrame + 1)%4;
            *lastTime = SDL_GetTicks();
        }
        SDL_Rect srcRect = {*cFrame * 64, 0, 64, 60};
        SDL_RenderCopy(renderer,player->down,&srcRect,destRect);
    }
}