#ifndef PANTALLA_RECORDS_H_INCLUDED
#define PANTALLA_RECORDS_H_INCLUDED

#include "Menu.h"
#include "Records.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>

class Pantalla_Records
{
private:
    Texture * titulo;
    Texture * nombres[5];
    Texture * puntos[5];
    Texture * fechas[5];
    LButton * regresar;
    Texture * escape;
    Texture * background;
    Mix_Music * main_music;
    Records * r;
public:
    Pantalla_Records(SDL_Renderer * Render);
    void render(SDL_Renderer * Render);
    ~Pantalla_Records();
    void start(SDL_Renderer * Render);
};
//Contiene las funciones para que hacer con los botones y para dibujar la pantalla
void Pantalla_Records::start(SDL_Renderer * Render)
{
    /// MUSIC
    Mix_HaltMusic();
    Mix_PlayMusic(main_music,0);


    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (regresar->handleEvent(&e))
            {
                quit = true;
            }
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        render(Render);
    }
}
//Dibuja la pantalla
void Pantalla_Records::render(SDL_Renderer * Render)
{
    //SDL_RenderClear(Render);
    background->print(Render);
    titulo->print(Render);
    for (int i = 0; i<5; i++)
    {
        nombres[i]->print(Render);
        puntos[i]->print(Render);
        fechas[i]->print(Render);
    }
    regresar->print(Render);
    escape->print(Render);
    SDL_RenderPresent(Render);
}
//Destructor
Pantalla_Records::~Pantalla_Records()
{
    delete r;
}
//Carga lo necesario para poder dibujar la pantalla
Pantalla_Records::Pantalla_Records(SDL_Renderer * Render)
{
    regresar = new LButton(Render);
    informacion aux;
    r = new Records;
    SDL_Color textColor = {0};
    TTF_Font * gFont = TTF_OpenFont("res/calibrili.ttf",200);
    char p[8];
    for (int i = 0; i<5; i++)
    {
        aux = r->getInformacion(i);
        SDL_Color fec = {255,255,255,255};
        nombres[i] = new Texture(aux.nombre,fec,gFont,Render);
        nombres[i]->setH(75);
        nombres[i]->setW(300);
        nombres[i]->setPos(100,250+80*i);
        itoa(aux.puntuacion,p,10);
        puntos[i] = new Texture(p,fec,gFont,Render);
        puntos[i]->setH(75);
        puntos[i]->setW(75);
        puntos[i]->setPos(500,250+80*i);
        fechas[i] = new Texture(aux.fecha,fec,gFont,Render);
        fechas[i]->setH(75);
        fechas[i]->setW(350);
        fechas[i]->setPos(650,250+80*i);
    }
    TTF_CloseFont(gFont);
    gFont = TTF_OpenFont("res/BubbleDub.ttf",1000);
    titulo = new Texture("RECORDS",textColor,gFont,Render);
    titulo->setW(650);
    titulo->setH(200);
    titulo->setPos(200,10);
    TTF_CloseFont(gFont);
    gFont = TTF_OpenFont("res/BubbleDub.ttf",30);
    main_music = Mix_LoadMUS("res/sfx/Doom.wav");
    textColor={255,255,255};
    escape = new Texture("MAIN MENU",textColor,gFont,Render);
    escape->setPos(63,662);
    regresar->setDimensions(escape->getW(),escape->getH(),1);
    regresar->setPosition(escape->getPositionX(),escape->getPositionY());
    background = new Texture("res/images/tenebrus.jpg",Render,1056,720,0,0);
    regresar->setSound("res/sfx/Campanas.wav");
}
#endif // PANTALLA_RECORDS_H_INCLUDED
