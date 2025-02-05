#include "colisao.h"

bool colisaoCima(SDL_Rect* camera) {
    if ((camera->y == 128) && (camera->x >= 378 && camera->x <= 451)) {
        return true;
    }
    if ((camera->y == 128) && (camera->x >= 345 && camera->x <= 368)) {
        return true;
    }
    if ((camera->y == 63) && (camera->x >= 457 && camera->x <= 521)) {
        return true;
    }
    if ((camera->y == -4) && (camera->x >= 384 && camera->x <= 492)) {
        return true;
    }
    if ((camera->y == -1) && (camera->x >= 275 && camera->x <= 370)) {
        return true;
    }
    if ((camera->y == 14) && (camera->x >= 201 && camera->x <= 273)) {
        return true;
    }
    if ((camera->y == 15) && (camera->x >= 110 && camera->x <= 148)) {
        return true;
    }
    if ((camera->y >= 178 && camera->y <= 190) && (camera->x == 294)) {
        return true;
    }
    if ((camera->x >= 378 && camera->x <= 451) && camera->y == 128) {
        return true;
    }
    if ((camera->x >= 345 && camera->x <= 368) && camera->y == 128) {
        return true;
    }
    if ((camera->x == 367) && (camera->y >= 32 && camera->y <= 32)) {
        return true;
    }
    if ((camera->x >= 275 && camera->x <= 370) && (camera->y == -1)) {
        return true;
    }
    if ((camera->x == 268) && (camera->y == 14)) {
        return true;
    }
    if ((camera->x >= 550 && camera->x <= 522) && camera->y == 111) {
        return true;
    }
    if ((camera->x >= 522 && camera->x <= 456) && camera->y == 66) {
        return true;
    }
    if ((camera->x >= 384 && camera->x <= 370) && camera->y == 19) {
        return true;
    }
    if ((camera->x >= 367 && camera->x <= 346) && camera->y == 32) {
        return true;
    }
    if ((camera->x >= 111 && camera->x <= 70) && camera->y == 45) {
        return true;
    }

    return false;
}

bool colisaoBaixo(SDL_Rect* camera) {
    if ((camera->y == 54) && (camera->x >= 405 && camera->x <= 424)) {
        return true;
    }
    if ((camera->y == 61) && (camera->x >= 433 && camera->x <= 453)) {
        return true;
    }
    if ((camera->y == 61) && (camera->x >= 378 && camera->x <= 396)) {
        return true;
    }
    if ((camera->y == 63) && (camera->x >= 198 && camera->x <= 225)) {
        return true;
    }
    if ((camera->y >= 71 && camera->y <= 112) && (camera->x == 225)) {
        return true;
    }
    if ((camera->y >= 100 && camera->y <= 177) && (camera->x == 294)) {
        return true;
    }
    if ((camera->y == 225) && (camera->x >= 281 && camera->x <= 306)) {
        return true;
    }
    if ((camera->y == 291) && (camera->x == 306)) {
        return true;
    }

    if ((camera->x >= 405 && camera->x <= 424) && camera->y == 54) {
        return true;
    }
    if ((camera->x >= 433 && camera->x <= 453) && camera->y == 61) {
        return true;
    }
    if ((camera->x >= 378 && camera->x <= 396) && camera->y == 61) {
        return true;
    }
    if ((camera->y == 63) && (camera->x >= 198 && camera->x <= 225)) {
        return true;
    }
    if ((camera->y >= 71 && camera->y <= 112) && (camera->x == 225)) {
        return true;
    }
    if ((camera->x >= 75 && camera->x <= 111) && camera->y == 65) {
        return true;
    }
    if ((camera->x >= 194 && camera->x <= 227) && camera->y == 65) {
        return true;
    }
    if ((camera->x >= 193 && camera->x <= 109) && camera->y == 69) {
        return true;
    }

    return false;
}

bool colisaoDireita(SDL_Rect* camera) {
    if ((camera->x == 345) && (camera->y >= 103 && camera->y <= 124)) {
        return true;
    }
    if ((camera->x == 378) && (camera->y >= 54 && camera->y <= 126)) {
        return true;
    }
    if ((camera->x == 394) && (camera->y >= 54 && camera->y <= 62)) {
        return true;
    }
    if ((camera->y == 63) && (camera->x >= 521 && camera->x <= 538)) {
        return true;
    }
    if ((camera->x == 457) && (camera->y >= -3 && camera->y <= 63)) {
        return true;
    }
    if ((camera->x == 492) && (camera->y >= -5 && camera->y <= 0)) {
        return true;
    }
    if ((camera->x >= 521 && camera->x <= 538) && (camera->y == 63)) {
        return true;
    }
    if ((camera->x >= 457 && camera->x <= 521) && camera->y == 63) {
        return true;
    }
    if ((camera->x == 457) && (camera->y >= -3 && camera->y <= 63)) {
        return true;
    }
    if ((camera->x == 492) && (camera->y >= -5 && camera->y <= 0)) {
        return true;
    }
    if ((camera->x >= 384 && camera->x <= 492) && (camera->y == -4)) {
        return true;
    }
    if ((camera->x >= 521 && camera->x <= 538) && (camera->y == 63)) {
        return true;
    }
    if ((camera->x == 522) && (camera->y >= 106 && camera->y <= 66)) {
        return true;
    }
    if ((camera->x == 456) && (camera->y >= 57 && camera->y <= -2)) {
        return true;
    }

    return false;
}

bool colisaoEsquerda(SDL_Rect* camera) {
    if ((camera->x == 433) && (camera->y >= 54 && camera->y <= 62)) {
        return true;
    }
    if ((camera->x == 388) && (camera->y >= -4 && camera->y <= 17)) {
        return true;
    }
    if ((camera->x == 374) && (camera->y >= 17 && camera->y <= 32)) {
        return true;
    }
    if ((camera->x >= 194 && camera->x <= 274) && (camera->y == 213)) {
        return true;
    }
    if ((camera->x == 388) && (camera->y >= -4 && camera->y <= 17)) {
        return true;
    }
    if ((camera->x == 374) && (camera->y >= 17 && camera->y <= 32)) {
        return true;
    }
    if ((camera->x >= 367 && camera->x <= 344) && (camera->y == 32)) {
        return true;
    }
    if ((camera->x == 275) && (camera->y == 14)) {
        return true;
    }
    if ((camera->x >= 274 && camera->x <= 274) && (camera->y >= -1 && camera->y <= 16)) {
        return true;
    }
    if ((camera->x == 147) && (camera->y >= -4 && camera->y <= 15)) {
        return true;
    }
    if ((camera->x == 112) && (camera->y >= 15 && camera->y <= 45)) {
        return true;
    }
    
    return false;
}
