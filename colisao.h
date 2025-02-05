#include <SDL2/SDL.h>
#include <stdbool.h>

// funções para verificar colisões em cada direção de movimento
bool colisaoCima(SDL_Rect* rect); // nao pode se mover para cima
bool colisaoBaixo(SDL_Rect* rect); // nao pode se mover para baixo
bool colisaoEsquerda(SDL_Rect* rect); // nao pode se mover para a esquerda
bool colisaoDireita(SDL_Rect* rect); // nao pode se mover para a direita