#ifndef Grafo_h
#define Grafo_h
#include <queue>
#include <list>
#include <time.h>
#include <stdlib.h>
struct info{
    int x;
    int y;
    int color;
};
class Arista;

class Vertice{
public:
    Vertice *sig;
    Arista *ady;
    int id;
    bool temp;
    info datos;
    friend class Grafo;
};
class Arista{
    Arista *sig;
    Vertice *ady;
    friend class Grafo;
};
class Grafo{
private:
    static int id;
    int totales[10];
    Vertice *h;
public:
    Grafo();
    bool vacio();
    int tamanio();
    Vertice *getVertice(int x,int y);
    void insertaArista(Vertice *origen,Vertice *destino);
    void insertaVertice(int color,int x,int y);
    void listaAdyacencia();
    void eliminarArista(Vertice *origen,Vertice *destino);
    void conexiones(int x,int y);
    bool buscarArista(int x,int y,int x2,int y2);
    int getCoordenadas(info *arr);
    int bfsColor(int x,int y);
    void bfsColorEliminar(int x,int y);
    void eliminaVertice(int x,int y);
    void dfsMarcar(Vertice *o);
    int marcarSujetos(info *arr);
    void limpiar();
    bool perder();
    bool existColor(int col);
    bool ganar();
    int getTotColores();
    ~Grafo();
};
#endif // Grafo_h
