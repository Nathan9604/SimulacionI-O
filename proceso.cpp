#include "proceso.h"

//Contructor que pone las variables en 0
proceso::proceso()
{
    tiempoCola = 0;
    entradaCola = 0;
}

//Destructor
proceso::~proceso(){}

//Función que suma el tiempo en cola del programa, le entra un double con la cantidad de tiempo que pasó
// el programa en una cola
void proceso::sumarTiempoCola(double cantidad)
{
    //tiempoCola += entradaCola - cantidad;
    tiempoCola += cantidad - entradaCola;
}

//Función que actualiza el tiempo en que entró programa a una cola, le entra un double con el tiempo en el que entró a la cola
void proceso::actualizarEntradaCola(double reloj)
{
    entradaCola = reloj;
}

//Función que suma el tiempo en CPU del programa, le entra un double con la cantidad de tiempo que pasó
// el programa en CPU
void proceso::sumarTiempoCPU(double cantidad)
{
    tiempoCPU += cantidad;
}

//Función que suma el tiempo en IO del programa, le entra un double con la cantidad de tiempo que pasó
// el programa en IO
void proceso::sumarTiempoDispositivo(double cantidad)
{
    tiempoDispositivo += cantidad;
}

//Se obtiene el tiempo en CPU del programa
double proceso::obtenerTiempoCPU()
{
    return tiempoCPU;
}

//Se obtiene el tiempo en IO del programa
double proceso::obtenerTiempoIO()
{
    return tiempoDispositivo;
}

//Se obtiene el tiempo en colas del programa
double proceso::obtenerTiempoCola()
{
    return tiempoCola;
}

//Se obtiene el tiempo promedio total del programa en el sistema
double proceso::obtenerPromedioTotalSistema()
{
    return tiempoPromedioTotalSistema;
}

//Función que suma el tiempo promedio total del programa en el sistema, le entra un double con una cantidad de tiempo que pasó
// el programa en IO, en colas o en CPU
void proceso::sumarPromedioTotalSistema(double cantidad)
{
    tiempoPromedioTotalSistema += cantidad;
}
