main: main.c
<<<<<<< HEAD
<<<<<<< HEAD
gcc main.c textures.c player.c colisao.c -I SDL2\x86_64-w64-mingw32\include -L SDL2\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
gcc combat.c -I SDL2\x86_64-w64-mingw32\include -L SDL2\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf //Bruno
=======
	gcc main.c textures.c player.c text.c colisao.c -I SDL2\x86_64-w64-mingw32\include -L SDL2\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
>>>>>>> 4358121e5694803c300805d643065d5d2f25eca4
=======
	gcc main.c inicio.c textures.c player.c text.c colisao.c -I SDL2\x86_64-w64-mingw32\include -L SDL2\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer


combate: combat.c
	gcc combat.c -I SDL2\x86_64-w64-mingw32\include -L SDL2\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

>>>>>>> ea1c958ef0c5ecfc8b2fead24a26f1ab3e33881e
