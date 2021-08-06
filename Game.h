#ifndef Game_h
#define Game_h
#include <iostream>
#include <string>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <algorithm>
#include <queue>
#include <fstream>
#include <list>
#include "Songs.h"
#include "Records.h"
#include "math.h"
#include "Grafo.h"
#include "Bubbles.h"
#define OUT_SPHERE_X 610
#define OUT_SPHERE_Y 630
//calcula la distancia cuadrada
double distanceSquared( int x1, int y1, int x2, int y2 )
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    return deltaX*deltaX + deltaY*deltaY;
}
//revisa si dos objetos circulares colisionaron
bool checkCollision( int ar,int ax,int ay,int br,int bx,int by )
{
    //Calculate total radius squared
    int totalRadiusSquared = ar + br;
    totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

    //If the distance between the centers of the circles is less than the sum of their radii
    if( distanceSquared( ax, ay, bx, by ) < ( totalRadiusSquared ) )
    {
        //The circles have collided
        return true;
    }

    //If not
    return false;
}
//revisa si dos objetos rectangulares colisionaron
bool checkCollision2( int ax,int ay,int aw,int bx,int by,int bw)
{
    SDL_Rect a,b;
    a.x=ax;
    a.y=ay;
    a.w=a.h=aw;
    b.x=bx;
    b.y=by;
    b.w=b.h=bw;

    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
class LButton
{
private:
    SDL_Point mPosition;
    Texture *texture;
    Mix_Chunk * sound;
public:
    LButton(SDL_Renderer * renderer);
    LButton(SDL_Renderer * renderer,string ruta);
    ~LButton();
    void setPosition(int x, int y);
    bool handleEvent(SDL_Event * e);
    void setDimensions(int w, int h);
    void setDimensions(int w, int h,int small);
    int getPositionX();
    void print(SDL_Renderer *renderer);
    int getPositionY();
    int getButtonWidht();
    int getButtonHeight();
    void setSound(string ruta);
};
//Constructor del boton
LButton::LButton(SDL_Renderer * renderer)
{
    texture = new Texture("res/images/transparente.png",renderer,0,0,0,0);
    mPosition.x=0;
    mPosition.y=0;
}
LButton::LButton(SDL_Renderer * renderer,string ruta)
{
    texture = new Texture(ruta,renderer,0,0,0,0);
    mPosition.x=0;
    mPosition.y=0;
}
//destructor del boton
LButton::~LButton()
{
    texture->free();
    //Mix_FreeChunk(sound);
    //sound = NULL;
}
//Imprime el boton
void LButton::print(SDL_Renderer *renderer)
{
    texture->print(renderer);
}
//Establece la posicion del boton
void LButton::setPosition(int x, int y)
{
    texture->setPos(x,y);
    mPosition.x=x;
    mPosition.y=y;
}
//Revisa si el boton fue presionado e indica que hace
bool LButton::handleEvent(SDL_Event * e)
{
    bool s = false;
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
                Mix_PlayChannel(-1,sound,0);
                return true;
            }

        }
    }
    return s;
}
//Establece el tamaño del boton
void LButton::setDimensions(int w, int h)
{
    texture->setH(h);
    texture->setW(w);
}
//Establece el tamaño del boton pequeño
void LButton::setDimensions(int w, int h,int small)
{
    texture->setH(h);
    texture->setW(w);
}
//Regresa la posicion en x del boton
int LButton::getPositionX()
{
    return mPosition.x;
}
//Regresa la posicion en y del boton
int LButton::getPositionY()
{
    return mPosition.y;
}
//Regresa el ancho del boton
int LButton::getButtonWidht()
{
    return texture->getW();
}
//Regresa la altura del boton
int LButton::getButtonHeight()
{
    return texture->getH();
}
//Establece el sonido del boton
void LButton::setSound(string ruta)
{
    sound = Mix_LoadWAV(ruta.c_str());
}

struct game_assets
{
    Texture *Fondo;
    Texture *Fondo1;
    Texture *Fondo2;
    Texture *Fondo3;
    Texture *Stone;
    Texture *Puntero;
    Texture *Puntos;
    Texture *vida;
    Texture *vida2;
};

class Game{
private:
    list<info> caidos;
    info caidos_arr[1000];
    Songs canc;
    game_assets *act;
    game_assets level1;
    Grafo graph;
    LButton *pantalla;
    Texture *letters_puntuacion;
    Texture *letters_numeros;
    Texture *letters_menu;
    LButton *buttonMenu;
    bool shoot;
    bool bajando;
    bool mover;
    bool lose;
    bool first;
    bool eliminar;
    int totvidas;
    int elix,eliy;
    double pendiente_x, pendiente_y;
    void loadAllGameAssets(SDL_Renderer *Render);
    void dibujar_puntero(SDL_Renderer *Render);
    Bubble *burbuja_actual;
    Bubble *burbujas[6];
    info coordenadas[1000];
    info coordenadasBajar[1000];
    int tamBajar;
    int totBajado;
    int uno,dos;
    int nivel;
    int totColores;
    int totABajar;
    int dificultad;
    double i,j,q,w;
    int vidas;
    int tiempo;
    string contrasena;
    int puntuacion;
    int num_menu;
    Records * r;
    char nombre[15];
public:
    Game(SDL_Renderer *Render,string contrasena,int num_m,int dificultad);
    ~Game();
    int play(SDL_Renderer *Render,Uint32 Delay,SDL_Event e);
    inline string getContrasena(){return contrasena;}
    inline int getNivel(){return nivel;}
    void actualizar(SDL_Renderer *Render);
    void nextLevel();
};
//Destructor
Game::~Game()
{
    delete r;
}
//Constructor
Game::Game(SDL_Renderer *Render,string contrasena,int num_m,int dificultad)
{
    tiempo=0;
    this->dificultad=dificultad;
    num_menu=num_m;
    r = new Records();
    strcpy(nombre,contrasena.c_str());
    vidas=5;
    totvidas=5;
    this->contrasena=contrasena;
    bajando=false;
    puntuacion=0;
    nivel=1;
    SDL_Color color={255,255,255};
    TTF_Font * select_font = TTF_OpenFont("res/Bubble.ttf",40);
    letters_puntuacion=new Texture("SCORE:",color,select_font,Render);
    letters_puntuacion->setPos(10,50);
    letters_numeros=new Texture("0",color,select_font,Render);
    letters_numeros->setPos(170,50);
    letters_menu=new Texture("Main Menu",color,select_font,Render);
    letters_menu->setPos(10,600);
    TTF_CloseFont(select_font);
    select_font=NULL;
    buttonMenu=new LButton(Render);
    buttonMenu->setPosition(10,600);
    buttonMenu->setDimensions(letters_menu->getW(),letters_menu->getH());
    buttonMenu->setSound("res/sfx/Campanas.wav");
    loadAllGameAssets(Render);
    level1.Fondo=level1.Fondo1;
    act=&level1;
    pantalla=new LButton(Render);
    pantalla->setDimensions(434,640);
    pantalla->setPosition(373,0);
    pantalla->setSound("res/sfx/Campanas.wav");
    shoot=true;
    lose=false;
    mover=false;
    eliminar=false;
    totColores=4;
    for(int qw=0;qw<4;qw++)
    {
        for(int we=0;we<15;we++)
        {
            graph.insertaVertice(rand()%totColores,we,qw);
        }
    }
    //graph.listaAdyacencia();
    burbujas[0]=new Yellow(Render);
    burbujas[1]=new Blue(Render);
    burbujas[2]=new Red(Render);
    burbujas[3]=new Green(Render);
    burbujas[4]=new Purple(Render);
    burbujas[5]=new Orange(Render);
    burbuja_actual=NULL;
    do{
        uno=rand()%6;
    }while(!graph.existColor(uno));
    do{
        dos=rand()%6;
    }while(!graph.existColor(dos));
    i=580;
    j=680;
    q=-10;
    w=-10;
    mover=false;
    first=true;
}
//Carga las imagenes necesarias
void Game::loadAllGameAssets(SDL_Renderer *Render)
{
    if(num_menu==0)
    {
         level1.Fondo1= new Texture("res/images/fondo.png",Render,1056,720);
        level1.Fondo2= new Texture("res/images/fondo2.jpg",Render,1056,720);
        level1.Fondo3= new Texture("res/images/fondo3.jpg",Render,1056,720);
    }
    else if(num_menu==1)
    {
       level1.Fondo1= new Texture("res/images/fondo1.png",Render,1056,720);
        level1.Fondo2= new Texture("res/images/fondo21.jpg",Render,1056,720);
        level1.Fondo3= new Texture("res/images/fondo31.jpg",Render,1056,720);
    }
    else if(num_menu==2)
    {
        level1.Fondo1= new Texture("res/images/fondo20.jpg",Render,1056,720);
        level1.Fondo2= new Texture("res/images/fondo22.jpg",Render,1056,720);
        level1.Fondo3= new Texture("res/images/fondo32.jpg",Render,1056,720);
    }
    else if(num_menu==3)
    {
        level1.Fondo1= new Texture("res/images/fondo30.png",Render,1056,720);
        level1.Fondo2= new Texture("res/images/fondo23.jpg",Render,1056,720);
        level1.Fondo3= new Texture("res/images/fondo33.jpg",Render,1056,720);
    }
    level1.Stone=new Texture("res/images/stoneTexture.png",Render,30,720);
    level1.Puntero=new Texture("res/images/arrow.png",Render,60,30);
    level1.Puntos=new Texture("res/images/points.png",Render,454,38,363,620);
    level1.vida=new Texture("res/images/vida.png",Render,30,30);
    level1.vida2=new Texture("res/images/vida2.png",Render,30,30);
}
//Funcionamiento del juego
int Game::play(SDL_Renderer *Render,Uint32 Delay,SDL_Event e)
{
    if(graph.ganar())
    {
        if(nivel==3)
        {
            if(dificultad==1)
            {
                puntuacion*=2;
                actualizar(Render);
                SDL_RenderPresent(Render);
            }
            SDL_Delay(100);
            return 2;
        }
        nextLevel();
    }
    bool stop=false;
    act->Fondo->print(Render);
    act->Stone->setPosX(343);
    act->Stone->print(Render);
    act->Stone->setPosX(807);
    act->Stone->print(Render);
    dibujar_puntero(Render);
    act->Puntos->print(Render);
    letters_puntuacion->print(Render);
    letters_numeros->print(Render);
    letters_menu->print(Render);
    if(buttonMenu->handleEvent(&e))
    {
        return 3;

    }
    for (list<info>::iterator it=caidos.begin(); it != caidos.end(); ++it)
    {
        it->y++;
        burbujas[it->color]->setPos(it->x,it->y);
        burbujas[it->color]->print(Render);
        if(it->y>=700)
        {
            caidos.erase(it);
        }
    }
    int tam=graph.getCoordenadas(coordenadas);
    if(bajando)
    {
        totBajado++;
        for(int qw=0;qw<tamBajar;qw++)
        {
            burbujas[coordenadasBajar[qw].color]->setPos(373+coordenadasBajar[qw].x*28+14*(coordenadasBajar[qw].y%2)+totBajado/3*(coordenadasBajar[qw].y%2 ? -1: +1),28*coordenadasBajar[qw].y+totBajado/3);
            burbujas[coordenadasBajar[qw].color]->print(Render);
        }
        if(totBajado==42)
        {
            totBajado=0;
            graph.limpiar();
            int qwerty;
            for(int qw=0;qw<tamBajar;qw++)
            {
                graph.insertaVertice(coordenadasBajar[qw].color,coordenadasBajar[qw].x,coordenadasBajar[qw].y+1);
            }
            for(int qw=0;qw<15;qw++)
            {
                do{
                    qwerty=rand()%6;
                }while(!graph.existColor(qwerty));
                graph.insertaVertice(qwerty,qw,0);
            }
            totABajar--;
            if(totABajar==0)
            {
                bajando=false;
                int totCaidos=graph.marcarSujetos(caidos_arr);
                for(int qw=0;qw<totCaidos;qw++)
                {
                    caidos_arr[qw].x=373+caidos_arr[qw].x*28+14*(caidos_arr[qw].y%2);
                    caidos_arr[qw].y=caidos_arr[qw].y*28;
                    caidos.push_back(caidos_arr[qw]);
                }
                lose=graph.perder();
            }
            else
            {
                tamBajar=graph.getCoordenadas(coordenadasBajar);
            }
        }
        return 0;
    }
    else
    {
        for(int qw=0;qw<tam;qw++)
        {
            burbujas[coordenadas[qw].color]->setPos(373+coordenadas[qw].x*28+14*(coordenadas[qw].y%2),28*coordenadas[qw].y);
            burbujas[coordenadas[qw].color]->print(Render);
        }
    }
    for(int qw=0;qw<totvidas;qw++)
    {
        if(vidas>qw)
        {
            act->vida->setPos(10+40*qw,100);
            act->vida->print(Render);
        }
        else
        {
            act->vida2->setPos(10+40*qw,100);
            act->vida2->print(Render);
        }
    }
    while(!graph.existColor(dos) && !graph.ganar())
        dos=rand()%6;
    burbujas[dos]->setPos(400,690);
    burbujas[dos]->print(Render);

    if(lose)
    {
        SDL_RenderPresent(Render);
        SDL_Delay(1000);
        return 1;
    }
    if(eliminar)
    {
        SDL_RenderPresent(Render);
        SDL_Delay(100);
        burbujas[graph.getVertice(elix,eliy)->datos.color]->sound();
        graph.bfsColorEliminar(elix,eliy);
        int totCaidos=graph.marcarSujetos(caidos_arr);
        for(int qw=0;qw<totCaidos;qw++)
        {
            caidos_arr[qw].x=373+caidos_arr[qw].x*28+14*(caidos_arr[qw].y%2);
            caidos_arr[qw].y=caidos_arr[qw].y*28;
            caidos.push_back(caidos_arr[qw]);
        }
        puntuacion+=totCaidos*5;
        r->actualizar(nombre,puntuacion);
        actualizar(Render);
        //graph.listaAdyacencia();
        eliminar=false;
    }
    if(shoot)
    {
        tiempo++;
        if(tiempo>=3000)
        {
            shoot=false;
            q=-4;
            w=-4;
            mover=true;
            tiempo=0;
            Mix_PlayChannel(-1,canc.getCascabel(),0);
        }
    }
    if(shoot && pantalla->handleEvent(&e))
    {
        shoot=false;
        q = pendiente_x;
        w = pendiente_y;
        mover = true;
        tiempo=0;
    }
    if(shoot)
    {
        while(!graph.existColor(uno) && !graph.ganar())
            uno=rand()%6;
        burbuja_actual=burbujas[uno];
        burbuja_actual->setPos(i,j);
        burbuja_actual->print(Render);
    }
    if(first)
    {
        first=false;
        mover=false;
        shoot=true;
        SDL_Delay(1000);
        Mix_PlayMusic(canc.getLevel(nivel,num_menu),-1);
    }
    if (mover)
    {
        i += q;
        j += w;
        if ((i < 373 && q < 0) || (i+40 > 820 && q > 0))
        {
            q = q * -1;
            //Mix_PlayChannel(-1,gRebote,0);
        }
        burbuja_actual->setPos(i,j);
        burbuja_actual->print(Render);
        for(int qw=0;qw<tam;qw++)
        {
            stop=checkCollision(14,i,j,14,28*coordenadas[qw].x+14*((coordenadas[qw].y)%2)+373,28*coordenadas[qw].y);
            if(stop)
                break;
        }
        if(stop || j<0)
        {
            mover=false;
            //int cy=redondear((j)/28.0);
            //int cx=redondear( ((i-373)-14*(cy%2))/28.0 );
            //
            int esqx=i-373,esqy=j;
            int posEsqy=esqy/28;
            int posEsqx=((esqx)-14*(posEsqy%2))/28;
            int esq1x,esq2x,esq3x,esq4x,esq1y,esq2y,esq3y,esq4y;
            esq2y=esq1y=posEsqy*28;
            esq4y=esq3y=posEsqy*28+28;
            esq1x=28*posEsqx+14*(posEsqy%2);
            esq2x=28*posEsqx+14*(posEsqy%2)+28;
            if(posEsqy%2)
            {
                if(esqx>=esq1x+14)
                    esq3x=esq1x+14;
                else
                  esq3x=esq1x-14;
            }
            else
            {
                if(esqx>=esq1x+14)
                    esq3x=esq1x+14;
                else
                  esq3x=esq1x-14;
            }
            esq4x=esq3x+28;
            int alto,ancho;
            int area1,area2,area3,area4;
            alto=esq1y+28-esqy;
            ancho=esq1x+28-esqx;
            area1=alto*ancho;
            ancho=esqx+28-esq2x;
            area2=alto*ancho;
            alto=esqy+28-esq3y;
            ancho=esq3x+28-esqx;
            area3=alto*ancho;
            ancho=esqx+28-esq4x;
            area4=alto*ancho;
            int newx,newy;
            if(area1>=area2 && area1>=area3 && area1>=area4)
            {
                newx=(esq1x-14*((esq1y/28)%2))/28;
                newy=esq1y/28;
            }
            else if(area2>=area1 && area2>=area3 && area2>area4)
            {
                newx=(esq2x-14*((esq2y/28)%2))/28;
                newy=esq2y/28;
            }
            else if(area3>=area1 && area3>=area2 && area3>area4)
            {
                newx=(esq3x-14*((esq3y/28)%2))/28;
                newy=esq3y/28;
            }
            else
            {
                newx=(esq4x-14*((esq4y/28)%2))/28;
                newy=esq4y/28;
            }
             graph.insertaVertice(uno,newx,newy);
            if(newy>=22)
                lose=true;
            else
            {
                int conex=graph.bfsColor(newx,newy);
                if(conex>=3)
                {
                    puntuacion+=30;
                    puntuacion+=(conex-3)*15;
                    eliminar=true;
                    elix=newx;
                    eliy=newy;
                }
                else
                {
                    vidas--;
                    if(vidas<0)
                    {
                        if(totvidas==5)
                            vidas=totvidas=3;
                        else if(totvidas==3)
                            vidas=totvidas=1;
                        else
                            vidas=totvidas=5;
                        tamBajar=graph.getCoordenadas(coordenadasBajar);
                        bajando=true;
                        totABajar=totColores-graph.getTotColores()+1;
                        totBajado=0;
                    }
                }
            }
            //
            uno=dos;
            do{
                dos=rand()%6;
            }while(!graph.existColor(dos) && !graph.ganar());
            shoot=true;
            i=580;
            j=680;
            q=-10;
            w=-10;

        }
    }
    return 0;
}
//Dibuja el puntero
void Game::dibujar_puntero(SDL_Renderer * Render)
{
    /*int x, y;
    SDL_GetMouseState(&x,&y);

    double m, nx, ny;
    int vx,vy,vz,vr = 10, ve = 0, px;

    vx = x-600;

    if (y < OUT_SPHERE_Y)
        vy = y-OUT_SPHERE_Y;
    else
        vy = 1;

    vz = (vx*vr)+(vy*ve);
    nx = vx; ny = vy;
    vx = pow(vx,2); vy = pow(vy,2);
    m = sqrt(vx+vy);
    px = m; nx /= px; ny /= px;
    m *= 10;
    if (m == 0)
        m = 0;
    else
        m = vz/m;
    m = acos(m);
    m = m*180/3.141592654;
    m *= -1;

    act->Puntero->render(Render,570,720-40,NULL,m);
    pendiente_x = 600-x;
    pendiente_y = 630-y;
    m = sqrt(pow(pendiente_x,2) + pow(pendiente_y,2));
    m = m/15;
    pendiente_x = pendiente_x / (-1*m);
    pendiente_y = pendiente_y / (-1*m);
    */
    int x,y;
    SDL_GetMouseState(&x,&y);
    double mx,my;
    mx=(594.0-x);
    my=(694.0-y);
    pendiente_x=-mx/my;
    pendiente_y=-1;
    double dist=sqrt(pow(pendiente_x,2)+pow(pendiente_y,2));
    pendiente_x=4*pendiente_x/dist;
    pendiente_y=4*pendiente_y/dist;
    double m=my/mx;
    m=atan(m);
    m=m*180/acos(-1);
    if(m>=0)
        m-=180;
    act->Puntero->render(Render,570,720-40,NULL,m);

}
//Actualiza la puntuacion
void Game::actualizar(SDL_Renderer *Render)
{
    letters_numeros->free();
    char arr[1000];
    itoa(puntuacion,arr,10);
    SDL_Color color={255,255,255};
    TTF_Font * select_font = TTF_OpenFont("res/Bubble.ttf",40);
    letters_numeros=new Texture(arr,color,select_font,Render);
    letters_numeros->setPos(170,50);
    TTF_CloseFont(select_font);
    select_font=NULL;

}
//Carga lo necesario para el siguiente nivel
void Game::nextLevel()
{
    nivel++;
    vidas=5;
    totvidas=5;
    bajando=false;
    shoot=true;
    lose=false;
    mover=false;
    eliminar=false;
    if(dificultad==1)
        totColores++;
    for(int qw=0;qw<4;qw++)
    {
        for(int we=0;we<15;we++)
        {
            graph.insertaVertice(rand()%totColores,we,qw);
        }
    }
    //graph.listaAdyacencia();
     burbuja_actual=NULL;
    do{
        uno=rand()%6;
    }while(!graph.existColor(uno) && !graph.ganar());
    do{
        dos=rand()%6;
    }while(!graph.existColor(dos) && !graph.ganar());
    i=580;
    j=680;
    q=-10;
    w=-10;
    mover=false;
    Mix_PlayMusic(canc.getLevel(nivel,num_menu),-1);
    if(nivel==2)
    {
        level1.Fondo=level1.Fondo2;
    }
    else
    {
       level1.Fondo=level1.Fondo3;
    }
}
#endif
