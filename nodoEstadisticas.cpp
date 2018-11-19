#include "nodoEstadisticas.h"

//Constructor que pone las variables en 0
nodoEstadisticas::nodoEstadisticas()
{
    tiempoPromedioColas = 0;
    tiempoPromedioUsoCpu = 0;
    tiempoPromedioUsoIO = 0;
    coeficienteEficiencia = 0;
    ocupacionServidor = 0;
}

//Destructor
nodoEstadisticas::~nodoEstadisticas()
{

}

//Función que pone el tiempo promedio en colas de una corrida con respecto al parámetro
void nodoEstadisticas::asignarPromedioColas(double nuevo)
{
    tiempoPromedioColas = nuevo;
}

//Función que pone el tiempo promedio en CPU de una corrida con respecto al parámetro
void nodoEstadisticas::asignarPromedioCPU(double nuevo)
{
    tiempoPromedioUsoCpu = nuevo;
}

//Función que pone el tiempo promedio en IO de una corrida con respecto al parámetro
void nodoEstadisticas::asignarPromedioIO(double nuevo)
{
    tiempoPromedioUsoIO = nuevo;
}

//Función que pone el tiempo promedio promedio total en el sistema de los programas de una corrida con respecto al parámetro
void nodoEstadisticas::asignarPromedioTotalSistema(double nuevo)
{
    tiempoPromedioTotalSistema = nuevo;
}

//Pone el coeficiente de eficiencia
void nodoEstadisticas::asignarCoeficienteEficiencia(double nuevo)
{
    coeficienteEficiencia = nuevo;
}

//Pone la ocupación del servidor
void nodoEstadisticas::asignarOcupacionServidor(double nuevo)
{
    ocupacionServidor = nuevo;
}

//Se obtiene el promedio en colas de una corrida
double nodoEstadisticas::obtenerPromedioColas()
{
    return tiempoPromedioColas;
}

//Se obtiene el tiempo promedio en CPU de una corrida
double nodoEstadisticas::obtenerPromedioCPU()
{
    return tiempoPromedioUsoCpu;
}

//Se obtiene el tiempo promedio en IO de una corrida
double nodoEstadisticas::obtenerPromedioIO()
{
    return tiempoPromedioUsoIO;
}

//Se obtiene el tiempo promedio total en el sistema de los programas de una corrida
double nodoEstadisticas::obtenerPromedioTotalSistema()
{
    return tiempoPromedioTotalSistema;
}

//Se obtiene ocupacion del servidor
double nodoEstadisticas::obtenerOcupacionServidor()
{
    return ocupacionServidor;
}

//Se obtiene coeficiente de eficiencia
double nodoEstadisticas::obtenerCoeficienteEficiencia()
{
    return coeficienteEficiencia;
}

