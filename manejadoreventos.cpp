#include "manejadoreventos.h"

ManejadorEventos::ManejadorEventos()
{
    proximaSalidaCpu = INFINITO;
    proximaSalidaIO = INFINITO;
    proximoArribo = INFINITO;
    proximoSalirCpu = 0;
    proximoSalirIO = 0;
}

ManejadorEventos::~ManejadorEventos()
{

}

void ManejadorEventos::vaciarSalidaIO()
{
	 proximaSalidaIO = INFINITO;
	 proximoSalirIO = 0;
}

void ManejadorEventos::vaciarSalidaCpu()
{
	proximaSalidaCpu = INFINITO;
	proximoSalirCpu = 0;
}

int ManejadorEventos::obtenerProximoTiempo()
{
    float tiempo = -1;

    if(proximoArribo != INFINITO)
    {
        if(proximoArribo <= proximaSalidaIO && proximoArribo <= proximaSalidaCpu){
            tiempo = proximoArribo;
            printf("arribo %9.6f\n",tiempo);
            return tiempo;
        }

    }

    if(proximaSalidaCpu != INFINITO)
    {
        if(proximaSalidaCpu <= proximoArribo && proximaSalidaCpu <= proximaSalidaIO){
            tiempo = proximaSalidaCpu;
            printf("cpu %9.6f\n",tiempo);
            return tiempo;
        }

    }

    if(proximaSalidaIO != INFINITO)
    {
        if(proximaSalidaIO <= proximoArribo && proximaSalidaIO <= proximaSalidaCpu){
            tiempo = proximaSalidaIO;
            printf("io %9.6f\n",tiempo);
            return tiempo;
        }

    }

    return tiempo;
}


void ManejadorEventos::indicarProximoArribo(float p)
{
    proximoArribo = p;
}
void ManejadorEventos::indicarProximaSalidaIO(float p, proceso * pid)
{
    proximaSalidaIO = p;
    proximoSalirIO = pid;

}
void ManejadorEventos::indicarProximaSalidaCpu(float p, proceso * pid )
{
    proximaSalidaCpu = p;
    proximoSalirCpu = pid;
}



//Retorna evento 1, 2, 3 o -1 para indicar que no hay ningun evento a ocurrir
float ManejadorEventos::ObtenerEventoMasProximo()
{
    int evento = -1;

    if(proximoArribo != INFINITO)
    {
        if(proximoArribo <= proximaSalidaIO && proximoArribo <= proximaSalidaCpu)
            evento = 1;
    }

    if(evento == -1 && proximaSalidaCpu != INFINITO)
    {
        if(proximaSalidaCpu <= proximoArribo && proximaSalidaCpu <= proximaSalidaIO)
            evento = 2;
    }

    if(evento == -1 && proximaSalidaIO != INFINITO)
    {
        if(proximaSalidaIO <= proximoArribo && proximaSalidaIO <= proximaSalidaCpu)
            evento = 3;
    }

    return evento;
}

proceso * ManejadorEventos::obtenerProximoProcesoIO()
{
    return proximoSalirIO;
}
proceso * ManejadorEventos::obtenerProximoProcesoCPU()
{
    return proximoSalirCpu;
}
