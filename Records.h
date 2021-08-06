#ifndef RECORDS_H_INCLUDED
#define RECORDS_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

struct informacion
{
	int id, puntuacion;
	char nombre[30];
	char fecha[15];
};

class Records
{
private:
	informacion info[5];
	informacion actual;
	fstream entrada;
	fstream salida;
public:
	Records();
	~Records();
	void actualizar(char * nombre, int puntuacion);
	void setID(int id);
	void reemplazar();
	void ordenar();
	void cerrar();
	void crearID();
	void imprimir();
	void guardar_fecha_hora();
	informacion getInformacion(int x);
};

#endif // RECORDS_H_INCLUDED
