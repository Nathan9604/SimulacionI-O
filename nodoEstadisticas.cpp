#include "nodoEstadisticas.h"

nodoEstadisticas::nodoEstadisticas()
{
    tiempoPromedioColas = 0;
    tiempoPromedioUsoCpu = 0;
    tiempoPromedioUsoIO = 0;
}

nodoEstadisticas::~nodoEstadisticas()
{

}

void nodoEstadisticas::asignarPromedioColas(double nuevo)
{
    tiempoPromedioColas = nuevo;
}

void nodoEstadisticas::asignarPromedioCPU(double nuevo)
{
    tiempoPromedioUsoCpu = nuevo;
}

void nodoEstadisticas::asignarPromedioIO(double nuevo)
{
    tiempoPromedioUsoIO = nuevo;
}

void nodoEstadisticas::asignarPromedioTotalSistema(double nuevo)
{
    tiempoPromedioTotalSistema = nuevo;
}

double nodoEstadisticas::obtenerPromedioColas()
{
    return tiempoPromedioColas;
}

double nodoEstadisticas::obtenerPromedioCPU()
{
    return tiempoPromedioUsoCpu;
}

double nodoEstadisticas::obtenerPromedioIO()
{
    return tiempoPromedioUsoIO;
}

double nodoEstadisticas::obtenerPromedioTotalSistema()
{
    return tiempoPromedioTotalSistema;
}
