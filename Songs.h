#ifndef Songs_h
#define Songs_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
struct canciones{
    Mix_Music *cancion[10][10];
    Mix_Chunk *cascabel;
    Mix_Music *intro;
    Mix_Music *Win;
};
class Songs{
private:
    canciones mix1;
public:
    Songs();
    //inline Mix_Music *getSong(int val){return mix1.cancion[val];}
    inline Mix_Chunk* getCascabel(){return mix1.cascabel;}
    inline Mix_Music *getIntro(){return mix1.intro;}
    inline Mix_Music *getMenu(int val){return mix1.cancion[0][val];}
    inline Mix_Music *getName(int val){return mix1.cancion[1][val];}
    inline Mix_Music *getLevel(int level,int val){return mix1.cancion[level+1][val];}
    inline Mix_Music *getWins(){return mix1.Win;}
};
//Constructor que carga todas las canciones y sonidos
Songs::Songs()
{
    mix1.cancion[0][0]=Mix_LoadMUS("res/sfx/menu.mp3");
    mix1.cancion[1][0]=Mix_LoadMUS("res/sfx/name1.mp3");
    mix1.cancion[2][0]=Mix_LoadMUS("res/sfx/level10.mp3");
    mix1.cancion[3][0]=Mix_LoadMUS("res/sfx/level20.mp3");
    mix1.cancion[4][0]=Mix_LoadMUS("res/sfx/level30.mp3");

    mix1.cancion[0][1]=Mix_LoadMUS("res/sfx/menu2.mp3");
    mix1.cancion[1][1]=Mix_LoadMUS("res/sfx/name2.mp3");
    mix1.cancion[2][1]=Mix_LoadMUS("res/sfx/level11.mp3");
    mix1.cancion[3][1]=Mix_LoadMUS("res/sfx/level21.mp3");
    mix1.cancion[4][1]=Mix_LoadMUS("res/sfx/level31.mp3");

    mix1.cancion[0][2]=Mix_LoadMUS("res/sfx/menu3.mp3");
    mix1.cancion[1][2]=Mix_LoadMUS("res/sfx/name3.mp3");
    mix1.cancion[2][2]=Mix_LoadMUS("res/sfx/level12.mp3");
    mix1.cancion[3][2]=Mix_LoadMUS("res/sfx/level22.mp3");
    mix1.cancion[4][2]=Mix_LoadMUS("res/sfx/level32.mp3");

    mix1.cancion[0][3]=Mix_LoadMUS("res/sfx/menu4.mp3");
    mix1.cancion[1][3]=Mix_LoadMUS("res/sfx/name4.mp3");
    mix1.cancion[2][3]=Mix_LoadMUS("res/sfx/level13.mp3");
    mix1.cancion[3][3]=Mix_LoadMUS("res/sfx/level23.mp3");
    mix1.cancion[4][3]=Mix_LoadMUS("res/sfx/level33.mp3");

    mix1.cascabel=Mix_LoadWAV("res/sfx/Campanas.wav");
    mix1.intro=Mix_LoadMUS("res/sfx/intro.mp3");
    mix1.Win=Mix_LoadMUS("res/sfx/win.mp3");
}
#endif // Songs_h
