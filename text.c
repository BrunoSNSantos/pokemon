#include "text.h"

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y){
    if(!text || strlen(text) == 0) return;
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if(!surface){
        printf("Falha ao renderizar o texto: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!texture){
        printf("Falha ao criar a texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }
    SDL_Rect dst = {x,y,surface->w,surface->h};
    dst.w *= 2;
    dst.h *= 2;
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void animateText(SDL_Renderer* renderer, Uint32* lastTime, int* charCount, const char* dialogue, int x, int y){
    TTF_Font* font = TTF_OpenFont("fonte.ttf", 32);
    int text_length = strlen(dialogue);
    SDL_Color black = { 0, 0, 0, 255 };
    Uint32 currentTime = SDL_GetTicks();
    if(currentTime > *lastTime + 80 && *charCount < text_length){
        (*charCount)++;
        *lastTime = currentTime;
    }
    if(charCount > 0){
        char tempText[256] = {0};
        strncpy(tempText, dialogue, *charCount);
        tempText[*charCount] = '\0';
        renderText(renderer, font, tempText, black, x , y);
    }
}