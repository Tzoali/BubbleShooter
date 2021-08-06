#ifndef Bubbles_h
#define Bubbles_h
class Bubble{
protected:
    Texture *tex;
    Mix_Chunk *sonido;
public:
    Bubble(SDL_Renderer *Render,string ruta);
    void print(SDL_Renderer *Render){tex->print(Render);}
    void setPos(int x,int y);
    virtual void sound()=0;
};
Bubble::Bubble(SDL_Renderer *Render,string ruta)
{
    tex=new Texture(ruta,Render,28,28);
}
void Bubble::setPos(int x,int y)
{
    tex->setPos(x,y);
}
class Red:public Bubble{
public:
    Red(SDL_Renderer *Render);
    void sound(){Mix_PlayChannel(2,sonido,0);}
};
Red::Red(SDL_Renderer *Render):Bubble(Render,"res/images/red.png")
{
    sonido=Mix_LoadWAV("res/sfx/red.wav");
}
class Blue:public Bubble{
public:
    Blue(SDL_Renderer *Render);
    void sound(){Mix_PlayChannel(2,sonido,0);}
};
Blue::Blue(SDL_Renderer *Render):Bubble(Render,"res/images/blue.png")
{
    sonido=Mix_LoadWAV("res/sfx/blue.wav");
}
class Green:public Bubble{
public:
    Green(SDL_Renderer *Render);
    void sound(){Mix_PlayChannel(2,sonido,0);}
};
Green::Green(SDL_Renderer *Render):Bubble(Render,"res/images/green.png")
{
    sonido=Mix_LoadWAV("res/sfx/green.wav");
}
class Yellow:public Bubble{
public:
    Yellow(SDL_Renderer *Render);
    void sound(){Mix_PlayChannel(2,sonido,0);}
};
Yellow::Yellow(SDL_Renderer *Render):Bubble(Render,"res/images/yellow.png")
{
    sonido=Mix_LoadWAV("res/sfx/yellow.wav");
}
class Orange:public Bubble{
public:
    Orange(SDL_Renderer *Render);
    void sound(){}
};
Orange::Orange(SDL_Renderer *Render):Bubble(Render,"res/images/orange.png")
{
}
class Purple:public Bubble{
public:
    Purple(SDL_Renderer *Render);
    void sound(){}
};
Purple::Purple(SDL_Renderer *Render):Bubble(Render,"res/images/purple.png")
{
}
#endif // Bubbles_h
