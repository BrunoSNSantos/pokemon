#include <SDL2/SDL.h>
#include <stdbool.h>

// funções para verificar colisões em cada direção de movimento
bool colisaoCima(SDL_Rect* rect); // nao pode se mover para cima
bool colisaoBaixo(SDL_Rect* rect); // nao pode se mover para baixo
bool colisaoEsquerda(SDL_Rect* rect); // nao pode se mover para a esquerda
bool colisaoDireita(SDL_Rect* rect); // nao pode se mover para a direita
bool colisaoCimaG(SDL_Rect* rect); // nao pode se mover para cima no ginásio
bool colisaoBaixoG(SDL_Rect* rect); // nao pode se mover para baixo no ginásio
bool colisaoEsquerdaG(SDL_Rect* rect); // nao pode se mover para a esquerda no ginásio
bool colisaoDireitaG(SDL_Rect* rect); // nao pode se mover para a direita no ginásio