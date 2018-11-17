#include "proceso.h"

proceso::proceso()
{
    tiempoCola = 0;
    entradaCola = 0;
}

proceso::~proceso(){}

void proceso::sumarTiempoCola(double cantidad)
{
    tiempoCola += entradaCola - cantidad;
    //No es tiempoCola += cantidad - entradaCola ?
}

void proceso::actualizarEntradaCola(double reloj)
{
    entradaCola = reloj;
}

void proceso::sumarTiempoCPU(double cantidad)
{
    tiempoCPU += cantidad;
}

void proceso::sumarTiempoDispositivo(double cantidad)
{
    tiempoDispositivo += cantidad;
}

double proceso::obtenerTiempoCPU()
{
    return tiempoCPU;
}

double proceso::obtenerTiempoIO()
{
    return tiempoDispositivo;
}

double proceso::obtenerTiempoCola()
{
    return tiempoCola;
}
