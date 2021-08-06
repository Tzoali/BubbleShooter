#include "Records.h"
//actualiza los records
void Records::actualizar(char * nombre, int puntuacion)
{
	strcpy(actual.nombre,nombre);
	actual.puntuacion = puntuacion;
}
//guarda la fecha del record
void Records::guardar_fecha_hora()
{
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
    strcpy(actual.fecha,output);
}
//crea el id
void Records::crearID()
{
	bool crear = true;
	bool igual = true;
	while (crear)
	{
		igual = false;
		int n = 1+rand()%(50-1+1);
		for (int i = 0; i<5; i++)
		{
			if (info[i].id == n)
			{
				igual = true;
				break;
			}
		}
		if (!igual)
		{
			actual.id = n;
			break;
		}
	}
}
//Constructor
Records::Records()
{
    actual.id = 0;
    strcpy(actual.nombre,"NADIE");
    strcpy(actual.fecha,"SIN FECHA");
    actual.puntuacion = -1;

	entrada.open("res/records/entrada.dat",ios::in|ios::binary);
	entrada.seekg(0,ios::beg);
	entrada.clear();

	for (int i = 0; i<5; i++)
	{
		entrada.read((char *)&info[i],sizeof(informacion));
	}

	salida.open("res/records/temp.dat",ios::out|ios::binary);

	crearID();

	ordenar();
}
//destructor
Records::~Records()
{
	cerrar();
}
//asigna un id
void Records::setID(int id)
{
	actual.id = id;
}
//reemplaza un record
void Records::reemplazar()
{
	int minimo = 100000;
	int j;
	for (int i = 0; i<5; i++)
	{
		if (info[i].puntuacion <= minimo)
		{
			j = i;
			minimo = info[i].puntuacion;
		}
	}
	if (actual.puntuacion >= info[j].puntuacion)
	{
		info[j] = actual;
	}
}
//ordena los records
void Records::ordenar()
{
	int minimo;
    for (int i = 0; i<4; i++)
    {
        minimo = i;
        for (int j = i+1; j<5; j++)
        {
            if (info[j].puntuacion > info[minimo].puntuacion)
            {
                minimo = j;
            }
        }
        informacion aux;
        aux = info[minimo];
        info[minimo] = info[i];
        info[i] = aux;
    }
}
//Cierra lo necesario
void Records::cerrar()
{
    guardar_fecha_hora();
	reemplazar();
	ordenar();

	salida.seekp(0,ios::beg);
	salida.clear();
	for (int i = 0; i<5; i++)
	{
		salida.write((char *)&info[i],sizeof(informacion));
	}

	entrada.close();
	salida.close();

	remove("res/records/entrada.dat");
	rename("res/records/temp.dat","res/records/entrada.dat");
}
//Muestra los datos
void Records::imprimir()
{
	cout<<endl<<"IMPRIENDO RECORDS"<<endl;
	for (int i = 0; i<5; i++)
	{
		cout<<endl<<"Jugador "<<i+1;
		cout<<endl<<"Nombre: "<<info[i].nombre;
		cout<<endl<<"ID: "<<info[i].id;
		cout<<endl<<"Puntuacion: "<<info[i].puntuacion<<endl;
	}
}
//regresa la informacion de un determinado record
informacion Records::getInformacion(int x)
{
    return info[x];
}
