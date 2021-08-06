//INTEGRANTES:
// Daniel Tzoali Arroyo Valdivia
// Omar Arturo Ruiz Bernal
// David Isai Zarate Robles

#include "Texture.h"
#include <iostream>
#include <string>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <algorithm>
#include <queue>
#include <fstream>
#include "Game.h"
#include "Songs.h"
#include "Menu.h"

using namespace std;

int main(int argv, char** args)
{
    srand(time(0));
    float dtInput = 0;
    Uint64 Start = 0;
    Uint64 End = 0;
    Uint64 Frequency = SDL_GetPerformanceFrequency();
    Uint32 Delay = 0;
    Uint32 DelayStart = SDL_GetTicks();
    Uint32 DelayEnd = 0;

    bool running=true;
    SDL_Init(SDL_INIT_EVERYTHING);
    const Uint8 *keyState;
    if(TTF_Init() == -1)
    {
        SDL_Log("%s\n", TTF_GetError());
        return(-1);
    }
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Window* Win = SDL_CreateWindow("Bubble Shooter",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1056, 720,
                                       SDL_WINDOW_SHOWN);
    SDL_Surface *logo;
    logo = SDL_LoadBMP("res/images/bubble.bmp");
    SDL_SetWindowIcon(Win,
                       logo);
    SDL_FreeSurface(logo);
    SDL_Renderer* Render = SDL_CreateRenderer(Win, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(Render, SDL_BLENDMODE_BLEND);

    menu m(Render,Delay);
    char nombre[1000]={0};
    int tam=0;
    SDL_Event Events;
    bool read=0;
    Delay=0;
    while(running && m.start(Render,keyState,Delay,Events,nombre,&tam,&read))
    {
        while(SDL_PollEvent(&Events))
        {
            if(Events.type==SDL_QUIT)
             {
                running = false;
             }
             if(read)
             {
                if(Events.type==SDL_TEXTINPUT || Events.type==SDL_KEYDOWN)
                 {
                     if(Events.type==SDL_KEYDOWN && Events.key.keysym.sym==SDLK_BACKSPACE  && tam>0)
                     {
                         nombre[--tam]='\0';

                     }
                     else if((*(Events.text.text)>='a' && *(Events.text.text)<='z' || *(Events.text.text)>='A' && *(Events.text.text)<='Z' || *(Events.text.text)>='0' && *(Events.text.text)<='9') && tam<=25)
                     {
                         nombre[tam]=*(Events.text.text);
                         nombre[++tam]='\0';
                     }
                 }
             }
        }
        keyState=SDL_GetKeyboardState(NULL);
        SDL_RenderPresent(Render);
        End = SDL_GetPerformanceCounter();
        Uint64 Elapsed = End - Start;
        dtInput = (float)Elapsed/(float)Frequency;
        Start = End;
        DelayEnd = SDL_GetTicks();
        Delay += DelayEnd - DelayStart;
        DelayStart = DelayEnd;

    }

    return 0;
}
