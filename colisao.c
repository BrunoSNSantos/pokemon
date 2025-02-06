#include "colisao.h"

// funçao o intervalo de x
bool intervaloX(int x, int min, int max) {
    return x >= min && x <= max;
}

// funçao intervalo de y
bool intervaloY(int y, int min, int max) {
    return y >= min && y <= max;
}

bool colisaoCima(SDL_Rect* camera) {
    if ((camera->y == 128 && intervaloX(camera->x, 371, 344)) ||
        (camera->y == 63 && intervaloX(camera->x, 457, 521)) ||
        (camera->y == -4 && intervaloX(camera->x, 384, 492)) ||
        (camera->y == -1 && intervaloX(camera->x, 275, 370)) ||
        (camera->y == 14 && intervaloX(camera->x, 201, 147)) ||
        (camera->y == 15 && intervaloX(camera->x, 110, 148)) ||
        (camera->y >= 178 && camera->y <= 190 && camera->x == 294) ||
        (camera->y == 32 && camera->x == 367) ||
        (camera->y == 19 && camera->x >= 370 && camera->x <= 384) ||
        (camera->y == 45 && intervaloX(camera->x, 70, 111)) ||
        (camera->y == 110 && intervaloX(camera->x, 522, 550)) ||
        (camera->y == 30 && intervaloX(camera->x, 370, 346)) ||
        (camera->y == 66 && intervaloX(camera->x, 456, 522)) ||
        (camera->y == 127 && intervaloX(camera->x, 344, 373)) ||
        (camera->y == 127 && intervaloX(camera->x, 378, 446)) ||
        (camera->y == 239 && intervaloX(camera->x, 363, 379)) ||
        (camera->y == 257 && intervaloX(camera->x, 383, 450)) ||
        (camera->y == 240 && intervaloX(camera->x, 450, 475)) ||
        (camera->y == 178 && intervaloX(camera->x, 194, 292)) ||
        (camera->y == 17 && intervaloX(camera->x, 112, 270)) ||
        (camera->y == 33 && intervaloX(camera->x, 345, 371))) {
        return true;
    }
    return false;
}

bool colisaoBaixo(SDL_Rect* camera) {
    if ((camera->y == 54 && intervaloX(camera->x, 400, 429)) ||
        (camera->y == 102 && intervaloX(camera->x, 372, 345)) ||
        (camera->y == 61 && intervaloX(camera->x, 378, 453)) ||
        (camera->y == 63 && intervaloX(camera->x, 198, 225)) ||
        (camera->y >= 71 && camera->y <= 112 && camera->x == 225) ||
        (camera->y >= 100 && camera->y <= 177 && camera->x == 294) ||
        (camera->y == 225 && intervaloX(camera->x, 281, 306)) ||
        (camera->y == 291 && camera->x == 306) ||
        (camera->y == 65 && (intervaloX(camera->x, 75, 111) || intervaloX(camera->x, 194, 227))) ||
        (camera->y == 69 && intervaloX(camera->x, 109, 193)) ||
        (camera->y == 102 && intervaloX(camera->x, 344, 373)) ||
        (camera->y == 160 && intervaloX(camera->x, 495, 550)) ||
        (camera->y == 175 && intervaloX(camera->x, 363, 492)) ||
        (camera->y == 225 && intervaloX(camera->x, 274, 298)) ||
        (camera->y == 213 && intervaloX(camera->x, 194, 274)) ||
        (camera->y == 102 && intervaloX(camera->x, 228, 292))) {
        return true;
    }
    return false;
}

bool colisaoDireita(SDL_Rect* camera) {
    if ((camera->x == 345 && intervaloY(camera->y, 103, 124)) ||
        (camera->x == 378 && intervaloY(camera->y, 61, 126)) ||
        (camera->x == 394 && intervaloY(camera->y, 54, 62)) ||
        (camera->y == 63 && intervaloX(camera->x, 521, 538)) ||
        (camera->x == 457 && intervaloY(camera->y, -3, 63)) ||
        (camera->x == 492 && intervaloY(camera->y, -5, 0)) ||
        (camera->y == -5 && intervaloX(camera->x, 384, 492)) ||
        (camera->x == 522 && intervaloY(camera->y, 66, 106)) ||
        (camera->x == 456 && intervaloY(camera->y, -2, 57)) ||
        (camera->y == 63 && intervaloX(camera->x, 521, 538)) ||
        (camera->x == 492 && intervaloY(camera->y, 163, 175)) ||
        (camera->x == 362 && intervaloY(camera->y, 180, 239)) ||
        (camera->x == 379 && intervaloY(camera->y, 239, 257)) ||
        (camera->x == 475 && intervaloY(camera->y, 240, 288)) ||
        (camera->x == 346 && intervaloY(camera->y, -1, 30))) {
        return true;
    }
    return false;
}

bool colisaoEsquerda(SDL_Rect* camera) {
    if ((camera->x == 433 && intervaloY(camera->y, 53, 62)) ||
        (camera->x == 388 && intervaloY(camera->y, -4, 17)) ||
        (camera->x == 374 && intervaloY(camera->y, 17, 29)) ||
        (camera->x == 367 && camera->y == 32) ||
        (camera->x == 275 && camera->y == 14) ||
        (camera->x == 147 && intervaloY(camera->y, -4, 15)) ||
        (camera->x == 275 && intervaloY(camera->y, -1, 13)) ||
        (camera->x == 112 && intervaloY(camera->y, 15, 45)) ||
        (camera->x >= 194 && camera->x <= 274 && camera->y == 213) ||
        (camera->x == 452 && camera->y >= 61 && camera->y <= 126) ||
        (camera->x == 274 && intervaloY(camera->y, 213, 225)) ||
        (camera->x == 194 && intervaloY(camera->y, 178, 210)) ||
        (camera->x == 292 && intervaloY(camera->y, 102, 178)) ||
        (camera->x == 228 && intervaloY(camera->y, 67, 101)) ||
        (camera->x == 372 && intervaloY(camera->y, 104, 128)) ||
        (camera->x == 307 && intervaloY(camera->y, 228, 288))) {
        return true;
    }
    return false;
}
