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
    proceso * proximoSalirIO;   // Proceso en el dispositivo de IO
    proceso * proximoSalirCpu;  // Proceso en CPU

    //Indican en que tiempo ocurriran los proximos eventos
    float proximoArribo;        // Tiempo del proximo arribo
    float proximaSalidaIO;      // Tiempo de próxima salida de IO
    float proximaSalidaCpu;     // Tiempo de próxima salida de CPU

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

    float obtenerProximoTiempo();

    //Indica que ya no hay ningun proceso en IO
	void vaciarSalidaIO();
    //Indica que ya no hay tiempo en CPU
	void vaciarSalidaCpu();
};
#endif // _MANEJADOREVENTOS_H
