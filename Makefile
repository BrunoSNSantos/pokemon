main: main.c inicio.c textures.c player.c text.c colisao.c personagens.c
	gcc main.c inicio.c textures.c player.c text.c colisao.c personagens.c -I SDL2\x86_64-w64-mingw32\include -L SDL2\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
