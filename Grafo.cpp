#include "Grafo.h"
#include <iostream>
using namespace std;
int Grafo::id=0;
//Constructor del grafo, inicializa el total de burbujas de cada color
Grafo::Grafo()
{
    h=NULL;
    for(int i=0;i<10;i++)
        totales[i]=0;
}
//Checa si el grafo esta vacio
bool Grafo::vacio()
{
    return (h==NULL);
}
//Regresa el tamaño del grafo
int Grafo::tamanio()
{
    int tam=0;
    Vertice *aux=h;
    while(aux!=NULL)
    {
        tam++;
        aux=aux->sig;
    }
    return tam;
}
//Regresa la direccion de memoria en la que esta almacenado el vertice con las coordenadas recibidas
Vertice* Grafo::getVertice(int x,int y)
{
     Vertice* aux=h;
     while(aux!=NULL)
     {
         if(aux->datos.x==x && aux->datos.y==y)
            return aux;
         aux=aux->sig;
     }
     return NULL;
}
//Inserta un nuevo vertice
void Grafo::insertaVertice(int color,int x,int y)
{
    Vertice *nuevo=new Vertice;
    nuevo->id=id;
    Grafo::id++;
    nuevo->datos.color=color;
    nuevo->datos.x=x;
    nuevo->datos.y=y;
    nuevo->sig=NULL;
    nuevo->ady=NULL;
    nuevo->temp=false;
    if(vacio())
        h=nuevo;
    else
    {
        Vertice *aux=h;
        while(aux->sig!=NULL)
        {
            aux=aux->sig;
        }
        aux->sig=nuevo;
    }
    totales[color]++;
    conexiones(x,y);
}
//inserta una arista entre dos vertices
void Grafo::insertaArista(Vertice *origen,Vertice *destino)
{
    Arista *nuevo = new Arista;
    nuevo->sig=NULL;
    nuevo->ady=NULL;
    Arista *aux=origen->ady;
    if(aux==NULL)
    {
        origen->ady=nuevo;
        nuevo->ady=destino;
    }
    else
    {
        while(aux->sig!=NULL)
            aux=aux->sig;
        aux->sig=nuevo;
        nuevo->ady=destino;
    }
}
//Imprime la lista de adyacencia del grafo
void Grafo::listaAdyacencia()
{
    Vertice *verAux;
    Arista *ariAux;
    verAux=h;
    while(verAux!=NULL)
    {
        cout<<"("<<verAux->datos.x<<","<<verAux->datos.y<<","<<verAux->datos.color<<")->";
        ariAux=verAux->ady;
        while(ariAux!=NULL)
        {
            cout<<"("<<ariAux->ady->datos.x<<","<<ariAux->ady->datos.y<<","<<ariAux->ady->datos.color<<")->";
            ariAux=ariAux->sig;
        }
        verAux=verAux->sig;
        cout<<endl;
    }
    for(int i=0;i<6;i++)
    {
        cout<<"Burbujas de color "<<i<<": "<<totales[i]<<endl;
    }
}
//Borra todos los verrtices
void Grafo::limpiar()
{
    Vertice *aux;
    while(h!=NULL)
    {
        aux=h;
        h=h->sig;
        delete aux;
    }
    for(int i=0;i<10;i++)
        totales[i]=0;
}
//Destructor
Grafo::~Grafo()
{
    Vertice *aux;
    while(h!=NULL)
    {
        aux=h;
        h=h->sig;
        delete aux;
    }
    for(int i=0;i<10;i++)
        totales[i]=0;
}
//Elimina la arista entre dos vertices
void Grafo::eliminarArista(Vertice *origen,Vertice *destino)
{
    bool band=false;
    Arista *actual,*anterior;
    actual=origen->ady;
    if(actual==NULL)
    {
        //cout<<"El vertice no tiene aristas"<<endl;
    }
    else if(actual->ady==destino)
    {
        origen->ady=actual->sig;
        delete actual;
    }
    else
    {
        while(actual!=NULL)
        {
            if(actual->ady==destino)
            {
                band=true;
                anterior->sig=actual->sig;
                delete actual;
                break;
            }
            anterior=actual;
            actual=actual->sig;
        }
        if(!band)
        {
            //cout<<"Esos dos vertices no estan conectados"<<endl;
        }
    }
}
//Hace las conexiones que tiene un vertice con los que esten a su alrededor
void Grafo::conexiones(int x,int y)
{
    Vertice* aux=NULL;
    int x2,y2;
    for(int i=0;i<6;i++)
    {
        switch(i)
        {
        case 0:
            x2=x-1+y%2;
            y2=y-1;
            break;
        case 1:
            x2=x+y%2;
            y2=y-1;
            break;
        case 2:
            x2=x-1;
            y2=y;
            break;
        case 3:
            x2=x+1;
            y2=y;
            break;
        case 4:
            x2=x-1+y%2;
            y2=y+1;
            break;
        case 5:
            x2=x+y%2;
            y2=y+1;
            break;
        }
        aux=getVertice(x2,y2);
        if(aux==NULL)
            continue;
        insertaArista(getVertice(x,y),getVertice(x2,y2));
        insertaArista(getVertice(x2,y2),getVertice(x,y));
    }
}
//llena el arreglo que recibe con las coordenadas y color de cada vertice, tambien regresa el total de vertices que coloco
int Grafo::getCoordenadas(info *arr)
{
   Vertice *aux=h;
   int tam=0;
   while(aux!=NULL)
   {
       arr[tam]=aux->datos;
       tam++;
       aux=aux->sig;
   }
    return tam;
}
//Realiza un bfs con los nodos del mismo color, regresa la cantidad de vertices que visito
int Grafo::bfsColor(int x,int y)
{
    int res=0;
    Vertice* aux=getVertice(x,y);
    bool marcados[100][100]={0};
    Vertice *arr[10000];
    marcados[aux->datos.x][aux->datos.y]=true;
    arr[0]=aux;
    int ini=0;
    int fini=0;
    Arista *aux2=NULL;
    while(ini<=fini)
    {
        res++;
        aux2=arr[ini]->ady;
        while(aux2!=NULL)
        {
            if(!marcados[aux2->ady->datos.x][aux2->ady->datos.y] && aux2->ady->datos.color==aux->datos.color)
            {
                marcados[aux2->ady->datos.x][aux2->ady->datos.y]=true;
                arr[++fini]=aux2->ady;
            }
            aux2=aux2->sig;
        }
        ini++;
    }
    return res;
}
//Elimina todos los vertices de un determinado color
void Grafo::bfsColorEliminar(int x,int y)
{
    Vertice* aux=getVertice(x,y);
    bool marcados[100][100]={0};
    Vertice *arr[10000];
    marcados[aux->datos.x][aux->datos.y]=true;
    arr[0]=aux;
    int ini=0;
    int fini=0;
    Arista *aux2=NULL;
    while(ini<=fini)
    {
        aux2=arr[ini]->ady;
        while(aux2!=NULL)
        {
            if(!marcados[aux2->ady->datos.x][aux2->ady->datos.y] && aux2->ady->datos.color==aux->datos.color)
            {
                marcados[aux2->ady->datos.x][aux2->ady->datos.y]=true;
                arr[++fini]=aux2->ady;
            }
            aux2=aux2->sig;
        }
        eliminaVertice(arr[ini]->datos.x,arr[ini]->datos.y);
        ini++;
    }
}
//Elimina un vertice
void Grafo::eliminaVertice(int x,int y)
{
    Vertice *elim=getVertice(x,y);
    Vertice *aux=h;
    Vertice *anterior=NULL;
    if(aux->datos.x==x && aux->datos.y==y)
    {
        while(aux!=NULL)
        {
            eliminarArista(aux,elim);
            aux=aux->sig;
        }
        aux=h;
        h=aux->sig;
        totales[aux->datos.color]--;
        delete aux;
    }
    else
    {
        while(aux!=NULL)
        {
            if(aux->datos.x==x && aux->datos.y==y)
            {
                anterior->sig=aux->sig;
            }
            else
            {
                eliminarArista(aux,elim);
            }
            anterior=aux;
            aux=aux->sig;
        }
        totales[elim->datos.color]--;
        delete elim;
    }
}
//Marca todos los vertices que esten conectados con un dfs
void Grafo::dfsMarcar(Vertice* o)
{
    o->temp=true;
    Arista* aux=o->ady;
    while(aux!=NULL)
    {
        if(!aux->ady->temp)
            dfsMarcar(aux->ady);
        aux=aux->sig;
    }
}
//Funcion encargada de ver que vertices no estan conectados al techo y eliminarlos
int Grafo::marcarSujetos(info *arr)
{
    Vertice* aux=h;
    while(aux!=NULL)
    {
        if(aux->datos.y==0 && !aux->temp)
            dfsMarcar(aux);
        aux=aux->sig;
    }
    aux=h;
    int res=0;
    while(aux!=NULL)
    {
        if(!aux->temp)
        {
            arr[res++]=aux->datos;
            eliminaVertice(aux->datos.x,aux->datos.y);
        }
        else
            aux->temp=false;
        aux=aux->sig;
    }
    return res;
}
//Revisa si el nivel de los vertices llego al tope
bool Grafo::perder()
{
    Vertice *aux=h;
    while(aux!=NULL)
    {
        if(aux->datos.y==22)
            return true;
        aux=aux->sig;
    }
    return false;
}
//Revisa si existe un color
bool Grafo::existColor(int col)
{
    if(totales[col]>0)
        return true;
    return false;
}
//Revisa si el jugador gano
bool Grafo::ganar()
{
    for(int i=0;i<6;i++)
    {
        if(totales[i]>0)
            return false;
    }
    return true;
}
//Regresa el total de colores
int Grafo::getTotColores()
{
    int res=0;
    for(int i=0;i<10;i++)
    {
        if(totales[i]>0)
            res++;
    }
    return res;
}
