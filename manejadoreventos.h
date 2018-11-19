#include "proceso.h"
#include "nodoEstadisticas.h"
#include <QQueue>

#ifndef MANEJADOREVENTOS_H
#define MANEJADOREVENTOS_H

#define INFINITO 100000000

class ManejadorEventos
{
protected:
    proceso * proximoSalirIO;
    proceso * proximoSalirCpu;

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

    proceso * obtenerProximoProcesoIO();
    proceso * obtenerProximoProcesoCPU();

    int obtenerProximoTiempo();

	void vaciarSalidaIO();
	void vaciarSalidaCpu();
};
#endif // _MANEJADOREVENTOS_H
