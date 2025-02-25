#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <stdio.h>

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y, float scaleFactor);
void animateText(SDL_Renderer* renderer, Uint32* lastTime, int* charCount, const char* dialogue, int x, int y, float scaleFactor);