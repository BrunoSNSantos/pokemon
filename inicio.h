#ifndef INICIO_H
#define INICIO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>

// Declaração correta da função
void iniciar();
bool telainicio(SDL_Window* window, SDL_Renderer* renderer);

#endif

