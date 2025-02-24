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

bool colisaoCimaG(SDL_Rect* camera) {
    if ((camera->y == 672 && intervaloX(camera->x, 412, 459)) ||
        (camera->y == 690 && intervaloX(camera->x, 440, 470)) ||
        (camera->y == 720 && intervaloX(camera->x, 430, 440)) ||
        (camera->y == 670 && intervaloX(camera->x, 350, 400)) ||
        (camera->y == 720 && intervaloX(camera->x, 360, 385)) ||
        (camera->y == 595 && intervaloX(camera->x, 381, 400)) ||
        (camera->y == 607 && intervaloX(camera->x, 414, 430)) ||
        (camera->y == 513 && intervaloX(camera->x, 350, 400)) ||
        (camera->y == 513 && intervaloX(camera->x, 412, 470)) ||
        (camera->y == 543 && intervaloX(camera->x, 365, 380)) ||
        (camera->y == 417 && intervaloX(camera->x, 318, 400)) ||
        (camera->y == 442 && intervaloX(camera->x, 394, 413)) ||
        (camera->y == 445 && intervaloX(camera->x, 462, 479)) ||
        (camera->y == 415 && intervaloX(camera->x, 410, 490))
        ) {
        return true;
    }
    return false;
}

bool colisaoBaixoG(SDL_Rect* camera) {
    if ((camera->y == 727 && intervaloX(camera->x, 350, 400)) ||
        (camera->y == 727 && intervaloX(camera->x, 420, 461)) ||
        (camera->y == 681 && intervaloX(camera->x, 365, 385)) ||
        (camera->y == 681 && intervaloX(camera->x, 430, 444)) ||
        (camera->y == 632 && intervaloX(camera->x, 412, 427)) ||
        (camera->y == 615 && intervaloX(camera->x, 381, 398)) ||
        (camera->y == 550 && intervaloX(camera->x, 345, 398)) ||
        (camera->y == 540 && intervaloX(camera->x, 410, 430)) ||
        (camera->y == 550 && intervaloX(camera->x, 430, 470)) ||
        (camera->y == 520 && intervaloX(camera->x, 365, 380)) ||
        (camera->y == 472 && intervaloX(camera->x, 410, 500)) ||
        (camera->y == 462 && intervaloX(camera->x, 442, 462)) ||
        (camera->y == 472 && intervaloX(camera->x, 334, 400)) ||
        (camera->y == 458 && intervaloX(camera->x, 318, 334)) ||
        (camera->y == 428 && intervaloX(camera->x, 398, 413)) ||
        (camera->y == 425 && intervaloX(camera->x, 460, 479))
    ) {
        return true;
    }
    return false;
}

bool colisaoDireitaG(SDL_Rect* camera) {
    if ((camera->x == 458 && intervaloX(camera->y, 672, 727)) ||
        (camera->x == 444 && intervaloX(camera->y, 672, 683)) ||
        (camera->x == 360 && intervaloX(camera->y, 685, 715)) ||
        (camera->x == 425 && intervaloX(camera->y, 685, 715)) ||
        (camera->x == 410 && intervaloX(camera->y, 632, 670)) ||
        (camera->x == 410 && intervaloX(camera->y, 540, 608)) ||
        (camera->x == 425 && intervaloX(camera->y, 600, 632)) ||
        (camera->x == 460 && intervaloX(camera->y, 500, 550)) ||
        (camera->x == 361 && intervaloX(camera->y, 525, 540)) ||
        (camera->x == 410 && intervaloX(camera->y, 473, 510)) ||
        (camera->x == 442 && intervaloX(camera->y, 462, 472)) ||
        (camera->x == 394 && intervaloX(camera->y, 428, 442)) ||
        (camera->x == 460 && intervaloX(camera->y, 427, 444)) ||
        (camera->x == 490 && intervaloX(camera->y, 415, 472)) ||
        (camera->x == 410 && intervaloX(camera->y, 380, 415))

         ) {
        return true;
    }
    return false;
}

bool colisaoEsquerdaG(SDL_Rect* camera) {
    if ((camera->x == 352 && intervaloX(camera->y, 660, 728)) ||
        (camera->x == 447 && intervaloX(camera->y, 690, 720)) ||
        (camera->x == 385 && intervaloX(camera->y, 680, 715)) ||
        (camera->x == 400 && intervaloX(camera->y, 615, 670)) ||
        (camera->x == 381 && intervaloX(camera->y, 590, 615)) ||
        (camera->x == 400 && intervaloX(camera->y, 555, 590)) ||
        (camera->x == 350 && intervaloX(camera->y, 500, 570)) ||
        (camera->x == 382 && intervaloX(camera->y, 520, 540)) ||
        (camera->x == 430 && intervaloX(camera->y, 540, 560)) ||
        (camera->x == 400 && intervaloX(camera->y, 472, 510)) ||
        (camera->x == 460 && intervaloX(camera->y, 462, 472)) ||
        (camera->x == 334 && intervaloX(camera->y, 458, 472)) ||
        (camera->x == 318 && intervaloX(camera->y, 417, 458)) ||
        (camera->x == 413 && intervaloX(camera->y, 428, 442)) ||
        (camera->x == 479 && intervaloX(camera->y, 427, 445)) ||
        (camera->x == 400 && intervaloX(camera->y, 380, 417)) 
        
        ) {
        return true;
    }
    return false;
}
