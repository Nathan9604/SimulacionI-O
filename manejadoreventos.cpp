#include "manejadoreventos.h"

ManejadorEventos::ManejadorEventos()
{
    //Inicializa todos los tiempos en infinito
    proximaSalidaCpu = INFINITO;
    proximaSalidaIO = INFINITO;
    proximoArribo = INFINITO;

    //Inicializa los proximos procesos en nulo
    proximoSalirCpu = 0;
    proximoSalirIO = 0;
}

ManejadorEventos::~ManejadorEventos()
{
    //No se debe destruir nada, dado que las simulaciones van a trabajar
    //con los punteros a procesos de esta clase
}

//Indica que ya no hay salidas en IO
void ManejadorEventos::vaciarSalidaIO()
{
	 proximaSalidaIO = INFINITO;
	 proximoSalirIO = 0;
}

//Indica que ya no hay procesos en CPU
void ManejadorEventos::vaciarSalidaCpu()
{
	proximaSalidaCpu = INFINITO;
	proximoSalirCpu = 0;
}

//Obtiene el tiempo más proximo en el que ocurrira un evento, ya sea
//un arribo, salida de io o salida de cpu.
int ManejadorEventos::obtenerProximoTiempo()
{
    float tiempo = -1;

    //Si un tiempo es infinito ni siquiera es necesario compararlo
    //con otros tiempos

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

//Indica al manejador de eventos cual sera el tiempo del proximo arribo
//Recibe como parámetro el tiempo del proximo arribo
void ManejadorEventos::indicarProximoArribo(float p)
{
    proximoArribo = p;
}


//Indica cuando sera la proxima salida de io, ademàs de cual proceso sera
//el que va a salir de IO
//Recibe como parametro el tiempo de la salida y un puntero al proceso
void ManejadorEventos::indicarProximaSalidaIO(float p, proceso * pid)
{
    proximaSalidaIO = p;
    proximoSalirIO = pid;
    printf("ProximaSalidaIO %d",p);

}

//Indica cuando sera la proxima salida de io, ademàs de cual proceso sera
//el que va a salir de CPU
//Recibe como parametro el tiempo de la salida y un puntero al proceso
void ManejadorEventos::indicarProximaSalidaCpu(float p, proceso * pid )
{
    proximaSalidaCpu = p;
    proximoSalirCpu = pid;
}



//Retorna evento 1, 2, 3 o -1 para indicar que no hay ningun evento a ocurrir
//Indica cual es el evento que va a ocurrir proximamente, incluso si esta
//ocurriendo en este momento
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

//Retorna un puntero al proceso que saldra de IO
//o nulo si no hay procesos en IO
proceso * ManejadorEventos::obtenerProximoProcesoIO()
{
    return proximoSalirIO;
}

//Retorna un puntero al proceso de saldra de CPU
//o nulo si no hay procesos en CPU
proceso * ManejadorEventos::obtenerProximoProcesoCPU()
{
    return proximoSalirCpu;
}
