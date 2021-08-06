#ifndef INSTRUCCIONES_H_INCLUDED
#define INSTRUCCIONES_H_INCLUDED

#include "Menu.h"

class instrucciones
{
private:
    Texture * imagen;
    Texture * escape;
    LButton * salir;
public:
    instrucciones(SDL_Renderer * gRender);
    void dibujar(SDL_Renderer * gRender);
    void start(SDL_Renderer * gRender);
};
//Contiene las funciones para que hacer con los botones y para dibujar la pantalla
void instrucciones::start(SDL_Renderer * gRender)
{
    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            if (salir->handleEvent(&e))
            {
                quit = true;
            }
        }
        dibujar(gRender);
    }
}
//Constructor de la clase
instrucciones::instrucciones(SDL_Renderer * gRender)
{
    imagen = new Texture("res/images/instrucciones.png",gRender,1056,720);
    SDL_Color text = {255,255,255};
    TTF_Font * gFont = TTF_OpenFont("res/BubbleDub.ttf",30);
    escape = new Texture("MAIN MENU",text,gFont,gRender);
    escape->setPos(60,29);
    salir = new LButton(gRender);
    salir->setDimensions(escape->getW(),escape->getH(),1);
    salir->setPosition(escape->getPositionX(),escape->getPositionY());
    salir->setSound("res/sfx/Campanas.wav");
    TTF_CloseFont(gFont);
}
//Dibuja la pantalla
void instrucciones::dibujar(SDL_Renderer * gRender)
{
    imagen->print(gRender);
    salir->print(gRender);
    escape->print(gRender);
    SDL_RenderPresent(gRender);
}

#endif // INSTRUCCIONES_H_INCLUDED
