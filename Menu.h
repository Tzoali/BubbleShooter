#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "Songs.h"
#include "Game.h"
#include "Pantalla_Records.h"
#include "Instrucciones.h"
class LButtonP
{
protected:
    SDL_Point mPosition;
    Mix_Chunk * sound;
    Texture *texture;
public:
    LButtonP(SDL_Renderer * renderer);
    ~LButtonP();
    void render(SDL_Renderer * renderer);
    void setPosition(int x, int y);
    virtual bool handleEvent(SDL_Event * e)=0;
    void setDimensions(int w, int h);
    int getPositionX();
    int getPositionY();
    int getButtonWidht();
    int getButtonHeight();
    void setSound(string ruta);
};

class boton_esfera : public LButtonP
{
private:
    int cont;
    Mix_Music * musica;
public:
    boton_esfera(SDL_Renderer *renderer);
    bool handleEvent(SDL_Event * e);
};

class rodolfo_boton : public LButtonP
{
private:
    int cont;
public:
    rodolfo_boton(SDL_Renderer *renderer);
    bool handleEvent(SDL_Event * e);
};
//Constructor
LButtonP::LButtonP(SDL_Renderer * renderer)
{
    texture= new Texture("res/images/boton.png",renderer,0,0,0,0);
    mPosition.x = 0;
    mPosition.y = 0;
}
//Destructor
LButtonP::~LButtonP()
{
    texture->free();
    //Mix_FreeChunk(sound);
    //sound = NULL;
}
//Establece la posicion del boton
void LButtonP::setPosition(int x, int y)
{
    texture->setPos(x,y);
    mPosition.x = x;
    mPosition.y = y;
}
//Imprime el boton
void LButtonP::render(SDL_Renderer * renderer)
{
    texture->print(renderer);
}
//Establece las dimensiones del boton
void LButtonP::setDimensions(int w, int h)
{
    texture->setH(h);
    texture->setW(w);
}
//Regrresa la posicion en x del boton
int LButtonP::getPositionX()
{
    return mPosition.x;
}
//Regrresa la posicion en y del boton
int LButtonP::getPositionY()
{
    return mPosition.y;
}
//Regresa el ancho del boton
int LButtonP::getButtonWidht()
{
    return texture->getW();
}
//Regresa la altura del boton
int LButtonP::getButtonHeight()
{
    return texture->getH();
}
//Establece el sonido del boton
void LButtonP::setSound(string ruta)
{
    sound = Mix_LoadWAV(ruta.c_str());
}
//Constructor
boton_esfera::boton_esfera(SDL_Renderer *renderer):LButtonP(renderer){}
//Revisa si el boton fue presionado
bool boton_esfera::handleEvent(SDL_Event * e)
{
    bool s = false;
    static bool sonando = true;
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x,&y);

        bool inside = true;

        if (x < mPosition.x)
            inside = false;
        if (x > mPosition.x + texture->getW())
            inside = false;
        if (y < mPosition.y)
            inside = false;
        if (y > mPosition.y + texture->getH())
            inside = false;

        if (inside)
        {
            if (e->type == SDL_MOUSEBUTTONDOWN)
            {
                cont++;
                Mix_PlayChannel(-1,sound,0);
                if (cont >= 10 && sonando)
                {
                    sonando = false;
                    Mix_HaltMusic();
                    musica = Mix_LoadMUS("res/sfx/ALLIWANTFORSCREAMING.mp3");
                    Mix_PlayMusic(musica,-1);
                }
                return true;
            }

        }
    }
    return s;
}
//Constructor
rodolfo_boton::rodolfo_boton(SDL_Renderer *renderer):LButtonP(renderer){}
//Revisa si el boton fue presionado
bool rodolfo_boton::handleEvent(SDL_Event * e)
{
    bool s = false;
    static bool sonando = true;
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x,&y);

        bool inside = true;

        if (x < mPosition.x)
            inside = false;
        if (x > mPosition.x + texture->getW())
            inside = false;
        if (y < mPosition.y)
            inside = false;
        if (y > mPosition.y + texture->getH())
            inside = false;

        if (inside)
        {
            if (e->type == SDL_MOUSEBUTTONDOWN)
            {
                cont++;
                Mix_PlayChannel(-1,sound,0);
                if (cont >= 15 && sonando)
                {
                    sonando = false;
                    Mix_FreeChunk(sound);
                    sound = Mix_LoadWAV("res/sfx/orange.wav");
                }
                return true;
            }
        }
    }
    return s;
}
enum gameState{MENU,GAME,RECORDS,INSTRUCTIONS,CHARGE,NEW,INTRO,WIN};
struct images{
    Texture *background;
    Texture *Name;
    Texture *Charge;
    Texture *rodolfo;
};
class menu
{
private:
    bool first;
    gameState actual;
    images assets[4];
    images *actual_images;
    int num_menu;
    Game *juego;
    Songs canc;
    Texture *noel;
    Texture *esfera;
    Texture *letters_buttons[8];
    Texture *letters_name;
    Texture *letters_skip;
    Texture *letters_win;
    Texture *intro;
    Texture *intro2;
    Texture *win;
    LButton *menu_buttons[7];
    LButtonP * botones [2];
    LButton *skip;
    Mix_Chunk * select;
    instrucciones * in;
    Uint32 inicio_intro;
    Uint32 inicio_win;
public:
    menu(SDL_Renderer * renderer,Uint32 Delay);
    void dibujar(SDL_Renderer * renderer);
    bool start(SDL_Renderer * renderer,const Uint8 *keyState,Uint32 Delay,SDL_Event e,char *nombre,int *tam,bool *read);
    void actualizar();
};
//Constructor
menu::menu(SDL_Renderer * renderer,Uint32 Delay)
{
    num_menu=0;
    in = new instrucciones(renderer);
    actual=INTRO;
    for(int i=0;i<8;i++)
        menu_buttons[i]= new LButton(renderer);
    skip= new LButton(renderer);
    //images
    assets[0].background= new Texture("res/images/menu.jpg",renderer,1056,720);
    assets[0].rodolfo = new Texture("res/images/logo1.png",renderer,269,250,720,25);
    assets[0].Name= new Texture("res/images/name.jpg",renderer,1056,720);
    assets[0].Charge= new Texture("res/images/name.jpg",renderer,1056,720);

    assets[1].background= new Texture("res/images/menu2.png",renderer,1056,720);
    assets[1].rodolfo = new Texture("res/images/logo2.png",renderer,269,250,720,25);
    assets[1].Name= new Texture("res/images/name2.png",renderer,1056,720);
    assets[1].Charge= new Texture("res/images/name2.png",renderer,1056,720);

    assets[2].background= new Texture("res/images/menu3.jpg",renderer,1056,720);
    assets[2].rodolfo = new Texture("res/images/logo3.png",renderer,269,250,720,25);
    assets[2].Name= new Texture("res/images/name3.png",renderer,1056,720);
    assets[2].Charge= new Texture("res/images/name3.png",renderer,1056,720);

    assets[3].background= new Texture("res/images/menu4.png",renderer,1056,720);
    assets[3].rodolfo = new Texture("res/images/logo4.png",renderer,269,250,720,25);
    assets[3].Name= new Texture("res/images/name4.jpg",renderer,1056,720);
    assets[3].Charge= new Texture("res/images/name4.jpg",renderer,1056,720);
    //
    actual_images=&assets[0];
    noel = new Texture("res/images/bubble.png",renderer,250,238,85,25);
    esfera= new Texture("res/images/transparente.png",renderer,100,100,875,600);
    intro= new Texture("res/images/intro.png",renderer,1056,720);
    intro2= new Texture("res/images/intro2.png",renderer,1056,720);
    win= new Texture("res/images/win.png",renderer,1056,720);
    TTF_Font * letter_menu_font = TTF_OpenFont("res/BubbleDub.ttf",60);
    SDL_Color color={255,255,255};
    letters_buttons[0]=new Texture("Continue",color,letter_menu_font,renderer);
    letters_buttons[1]=new Texture("New Game",color,letter_menu_font,renderer);
    letters_buttons[2]=new Texture("Records",color,letter_menu_font,renderer);
    letters_buttons[3]=new Texture("Instructions",color,letter_menu_font,renderer);
    letters_buttons[4]=new Texture("Exit",color,letter_menu_font,renderer);
    letters_buttons[5]=new Texture("Easy",color,letter_menu_font,renderer);
    letters_buttons[6]=new Texture("Hard",color,letter_menu_font,renderer);
    letters_buttons[7]=new Texture("Continue",color,letter_menu_font,renderer);
    letters_buttons[0]->setPos(128,297);
    letters_buttons[1]->setPos(111,397);
    letters_buttons[2]->setPos(790,347);
    letters_buttons[3]->setPos(117,497);
    letters_buttons[4]->setPos(815,447);
    letters_buttons[5]->setPos(377,600);
    letters_buttons[6]->setPos(577,600);
    letters_buttons[7]->setPos(477,600);
    letters_skip =new Texture("Skip",color,letter_menu_font,renderer);
    letters_skip->setPos(800,600);
    TTF_CloseFont(letter_menu_font);
    letter_menu_font = NULL;
    color={255,255,255};
    TTF_Font * select_font = TTF_OpenFont("res/Bubble.ttf",50);
    letters_name=new Texture("GIVE ME YOUR NAME",color,select_font,renderer);
    letters_name->setPos(100,50);
    letters_win=new Texture("YOU WIN!!!",color,select_font,renderer);
    letters_win->setPos(385,100);
    TTF_CloseFont(select_font);
    select_font=NULL;
    for (int i = 0; i<8; i++)
    {
        menu_buttons[i]->setDimensions(letters_buttons[i]->getW(),letters_buttons[i]->getH());
        menu_buttons[i]->setPosition(letters_buttons[i]->getPositionX(),letters_buttons[i]->getPositionY());
    }
    skip->setDimensions(letters_skip->getW(),letters_skip->getH());
    skip->setPosition(letters_skip->getPositionX(),letters_skip->getPositionY());
    for (int i = 0; i<8; i++)
        menu_buttons[i]->setSound("res/sfx/Campanas.wav");
    skip->setSound("res/sfx/Campanas.wav");
    botones[0] = new boton_esfera(renderer);
    botones[0]->setDimensions(100,100);
    botones[0]->setPosition(875,600);
    botones[0]->setSound("res/sfx/orange.wav");
    botones[1] = new rodolfo_boton(renderer);
    botones[1]->setDimensions(250,238);
    botones[1]->setPosition(85,25);
    botones[1]->setSound("res/sfx/orange.wav");
    Mix_PlayMusic(canc.getIntro(),0);
    juego=NULL;
    first=true;
}
//Dibuja la pantalla
void menu::dibujar(SDL_Renderer * renderer)
{
    actual_images->background->print(renderer);
    actual_images->rodolfo->print(renderer);
    noel->print(renderer);
    esfera->print(renderer);
    for(int i=0;i<5;i++)
    {
        menu_buttons[i]->print(renderer);
        letters_buttons[i]->print(renderer);
    }
}
//Hace lo necesario dependiendo de en que estado del menu este
bool menu::start(SDL_Renderer * renderer,const Uint8 *keyState,Uint32 Delay,SDL_Event e,char *nombre,int *tam,bool *read)
{
    if(first)
    {
        inicio_intro=Delay;
        first=false;
    }
    bool boton;
    SDL_Rect Back;
    Back.x = 0;
    Back.y = 0;
    Back.w = 1056;
    Back.h = 720;
    SDL_Color color={255,255,255};
    SDL_Surface *NickSurface = NULL;
    SDL_Texture *NickTexture = NULL;
    TTF_Font * Font = TTF_OpenFont("res/christmas.ttf",60);
    int temp;
    switch(actual)
    {
    case WIN:
        if(Delay-inicio_win<=4000)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0,255);
            SDL_RenderFillRect(renderer, &Back);
        }
        else if(Delay-inicio_win<=6000)
        {
            win->print(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0,255-255*(Delay-inicio_win-4000)/2000);
            SDL_RenderFillRect(renderer, &Back);
        }
        else if(Delay-inicio_win<=162000)
        {
            win->print(renderer);
            letters_skip->print(renderer);
            if(skip->handleEvent(&e))
            {
               actual=INTRO;
                first=true;
                num_menu=0;
                actual_images=&assets[0];
                Mix_PlayMusic(canc.getIntro(),0);
            }
        }
        else
        {
            actual=INTRO;
            first=true;
            num_menu=0;
            actual_images=&assets[0];
            Mix_PlayMusic(canc.getIntro(),0);
        }
        letters_win->print(renderer);
        break;
    case INTRO:
        if(Delay-inicio_intro<=10000)
        {
            intro->print(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0,255);
            SDL_RenderFillRect(renderer, &Back);
        }
        else if(Delay-inicio_intro<=30000)
        {
            intro->print(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0,255-255*(Delay-inicio_intro-10000)/20000);
            SDL_RenderFillRect(renderer, &Back);
        }
        else if(Delay-inicio_intro<=50000)
        {
            intro2->print(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0,0+255*(Delay-inicio_intro-30000)/20000);
            SDL_RenderFillRect(renderer, &Back);
        }
        else
        {
            actual=MENU;
            Mix_PlayMusic(canc.getMenu(num_menu),-1);
        }
        if(e.key.keysym.sym==SDLK_ESCAPE)
        {
            actual=MENU;
            Mix_PlayMusic(canc.getMenu(num_menu),-1);
        }
        break;
    case MENU:
        dibujar(renderer);
        if (menu_buttons[0]->handleEvent(&e))
        {
            if(juego!=NULL)
            {
                nombre[0]='\0';
                *tam=0;
                *read=true;
                Mix_PlayMusic(canc.getName(num_menu),-1);
                actual=CHARGE;

            }
        }
        else if (menu_buttons[1]->handleEvent(&e))
        {
            *read=true;
            actual=NEW;
            Mix_PlayMusic(canc.getName(num_menu),-1);
            nombre[0]='\0';
            *tam=0;
        }
        else if (menu_buttons[2]->handleEvent(&e))
        {
            actual = RECORDS;
        }
        else if (menu_buttons[3]->handleEvent(&e))
        {
            actual = INSTRUCTIONS;
        }
        else if (menu_buttons[4]->handleEvent(&e))
        {
            return false;
        }
        else if (botones[0]->handleEvent(&e))
        {
        }
        else if (botones[1]->handleEvent(&e))
        {
        }
        break;
    case GAME:
        temp=juego->play(renderer,Delay,e);
        if(temp!=0)
        {
           actual=MENU;
            Mix_PlayMusic(canc.getMenu(num_menu),-1);
            if(temp==2)
            {
                num_menu++;
                if(num_menu!=4)
                {
                    actual_images=&assets[num_menu];
                    Mix_PlayMusic(canc.getMenu(num_menu),-1);
                }
                else
                {
                    actual=WIN;
                    inicio_win=Delay;
                    Mix_PlayMusic(canc.getWins(),-1);
                }
            }
            if(temp!=3)
            {
                delete juego;
                juego=NULL;
            }
        }
        break;
    case NEW:
        actual_images->Name->print(renderer);
        menu_buttons[5]->print(renderer);
        letters_buttons[5]->print(renderer);
        letters_buttons[6]->print(renderer);
        letters_name->print(renderer);
        Back.x = 468;
        Back.y = 270;
        Back.w = 320;
        Back.h = 60;
        SDL_SetRenderDrawColor(renderer, 0, 72, 110,200 );
        SDL_RenderFillRect(renderer, &Back);
        NickSurface = TTF_RenderText_Blended(Font,nombre, color);
        NickTexture = SDL_CreateTextureFromSurface(renderer, NickSurface);
        Back.w=10*strlen(nombre);
        SDL_RenderCopy(renderer, NickTexture, 0, &Back);
        boton=menu_buttons[6]->handleEvent(&e);
        if ((menu_buttons[5]->handleEvent(&e) || boton) && strlen(nombre))
        {
            string basura;
            for(int i=0;i<strlen(nombre);i++)
            {
                basura+=nombre[i];
            }
           if(juego!=NULL)
           {
                 delete juego;
           }
           if(boton)
                juego =new Game(renderer,basura,num_menu,1);
            else
                juego =new Game(renderer,basura,num_menu,0);
            actual=GAME;
            *read=false;
            temp=juego->play(renderer,Delay,e);
            SDL_RenderPresent(renderer);
            if(temp!=0)
            {
               actual=MENU;
                Mix_PlayMusic(canc.getMenu(num_menu),-1);
                if(temp!=3)
                {
                    delete juego;
                    juego=NULL;
                }
            }
            SDL_RenderPresent(renderer);

        }
        break;
    case CHARGE:
        actual_images->Charge->print(renderer);
        letters_buttons[7]->print(renderer);
        letters_name->print(renderer);
        Back.x = 468;
        Back.y = 270;
        Back.w = 320;
        Back.h = 60;
        SDL_SetRenderDrawColor(renderer, 0, 72, 110,200 );
        SDL_RenderFillRect(renderer, &Back);
        NickSurface = TTF_RenderText_Blended(Font,nombre, color);
        NickTexture = SDL_CreateTextureFromSurface(renderer, NickSurface);
        Back.w=10*strlen(nombre);
        SDL_RenderCopy(renderer, NickTexture, 0, &Back);
        if (menu_buttons[7]->handleEvent(&e))
        {
            *read=false;
            string basura;
            for(int i=0;i<strlen(nombre);i++)
            {
                basura+=nombre[i];
            }
            if(basura==juego->getContrasena())
            {
                Mix_PlayMusic(canc.getLevel(juego->getNivel(),num_menu),-1);
                temp=juego->play(renderer,Delay,e);
                actual=GAME;
                if(temp!=0)
                {
                   actual=MENU;
                    Mix_PlayMusic(canc.getMenu(num_menu),-1);
                    if(temp!=3)
                    {
                        delete juego;
                        juego=NULL;
                    }
                }
                SDL_RenderPresent(renderer);
            }
            else
            {
                actual=MENU;
                Mix_PlayMusic(canc.getMenu(num_menu),-1);
            }
        }
        break;
    case INSTRUCTIONS:

        in->start(renderer);

        actual = MENU;
        break;
    case RECORDS:
        {
            Pantalla_Records * pantalla = new Pantalla_Records(renderer);
            pantalla->start(renderer);
            delete pantalla;
        }


        actual = MENU;
        Mix_PlayMusic(canc.getMenu(num_menu),-1);
        break;
    }
    TTF_CloseFont(Font);
    Font = NULL;
    return true;
}

#endif // MENU_H_INCLUDED
