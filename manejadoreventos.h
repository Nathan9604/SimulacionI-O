#include "proceso.h"
#include <QQueue>

#ifndef MANEJADOREVENTOS_H
#define MANEJADOREVENTOS_H

#define INFINITO -1

class ManejadorEventos
{
protected:
    proceso * proximoSalirIO;
    proceso * proximoSalirCpu;
    proceso *proximoProcesoCpu;

    int proximoArribo;
    int proximaSalidaIO;
    int proximaSalidaCpu;
    bool CPULibre;
    QQueue<proceso> colaListosCPU;
    QQueue<proceso> colaListosDispositivos;


public:
    ManejadorEventos();
    ~ManejadorEventos();

    void indicarProximoArribo(int);
    void indicarProximaSalidaIO(int, proceso *);
    void indicarProximaSalidaCpu(int, proceso * );


    //Retorna evento 1, 2, 3 o -1 para indicar que no hay ningun evento a ocurrir
    int ObtenerEventoMasProximo();

    proceso * obtenerProximoProcesoIO();
    proceso * obtenerProximoProcesoCPU();

    int obtenerProximoTiempo();

    void evento1(proceso * p);
	void vaciarSalidaIO();
	void vaciarSalidaCpu();
};
#endif // _MANEJADOREVENTOS_H
