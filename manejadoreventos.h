#include "proceso.h"
#include "nodoEstadisticas.h"
#include <QQueue>

#ifndef MANEJADOREVENTOS_H
#define MANEJADOREVENTOS_H

#define INFINITO 100000000

class ManejadorEventos
{
protected:

    //Indica ncuales son los proximos eventos a salir
    proceso * proximoSalirIO;
    proceso * proximoSalirCpu;

    //Indican en que tiempo ocurriran los proximos eventos
    float proximoArribo;
    float proximaSalidaIO;
    float proximaSalidaCpu;

public:
    ManejadorEventos();
    ~ManejadorEventos();

    void indicarProximoArribo(float);
    void indicarProximaSalidaIO(float, proceso *);
    void indicarProximaSalidaCpu(float, proceso * );


    //Retorna evento 1, 2, 3 o -1 para indicar que no hay ningun evento a ocurrir
    float ObtenerEventoMasProximo();

    //Permite obtener el proximo proceso a salir de IO
    //Retorna null si no hay ningun proceso en IO
    proceso * obtenerProximoProcesoIO();

    //Permite obtener el proximo proceso a salir de CPU
    //Retorna null si no hay ningun proceso en CPU
    proceso * obtenerProximoProcesoCPU();

    //Obtiene el tiempo más proximo en el que ocurrira un evento, ya sea
    //un arribo, salida de io o salida de cpu.
    int obtenerProximoTiempo();

    //Indica que ya no hay ningun proceso en IO
	void vaciarSalidaIO();
    //Indica que ya no hay tiempo en CPU
	void vaciarSalidaCpu();
};
#endif // _MANEJADOREVENTOS_H
