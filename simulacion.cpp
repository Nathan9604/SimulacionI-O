#include "simulacion.h"
#include <stdlib.h>
#include <time.h>

Simulacion::Simulacion(int numSim, int tiemSim, int quanSim, bool expon)
{
    numSims = numSim;
    tiemSims = (float)tiemSim;
    quanSims = quanSim;
    exp = expon;

    if(exp == true){
        media = 30;
        varianza = 1;
    }
    else{
        media = 25;
        varianza = 4;
    }

    //Inicializa variables de estadisticas para esta simulacion
    ocupacionServidor = 0;
    coeficienteEficiencia = 0;
    tiempoPromedioUsoCpu = 0;
    tiempoPromedioUsoIO = 0;

    CPULibre = true;
    IOLibre = true;

    contadorUsosCpu = 0;
    contadorUsosIO = 0;

    //Inicializa el manejador de eventos
    srand (time(NULL));
    manejadorEventos = new ManejadorEventos();

}

void Simulacion::run(){
    correrSim();
}

void Simulacion::correrSim(){
    int evento = 1;
    reloj = 0;
    tiempoPromedioColas = 0;
    tiempoPromedioUsoCpu = 0;
    tiempoPromedioUsoIO = 0;
    evento1();
    do{
        evento = manejadorEventos->ObtenerEventoMasProximo();

        emit this->actReloj(reloj);
        emit this->actCpu(CPULibre);
        emit this->actIo(IOLibre);
        emit this->actEvento(evento);
        emit this->actNumCola(colaListosCPU.size());
        emit this->actNumSal(colaSalida.size());
        emit this->actNumColaIO(colaListosDispositivos.size());

        switch(evento)
        {
            case 1:
                evento1();
                break;
            case 2:
                evento2();
                break;
            case 3:
                evento3();
                break;
        }

        reloj = manejadorEventos->obtenerProximoTiempo();
    }
    while(reloj <= tiemSims);

    //Son los promedios de cada corrida, no el total
    proceso *p;
    QList<proceso*>::iterator i;
    for (i = colaSalida.begin(); i != colaSalida.end(); i++){
        p = *i;
        tiempoPromedioUsoCpu += p->obtenerTiempoCPU();
        tiempoPromedioUsoIO += p->obtenerTiempoIO();
        tiempoPromedioColas += p->obtenerTiempoCola();
    }
    tiempoPromedioColas = tiempoPromedioColas / colaSalida.size();
    tiempoPromedioUsoCpu = tiempoPromedioUsoCpu / colaSalida.size();
    tiempoPromedioUsoIO = tiempoPromedioUsoIO / colaSalida.size();
    tiempoPromedioTotalSistema = tiempoPromedioTotalSistema / colaSalida.size();

    //Se guardan las estadísticas de cada simulación en la lista de estadísticas
    nodoEstadisticas *n = new nodoEstadisticas();
    n->asignarPromedioColas(tiempoPromedioColas);
    n->asignarPromedioCPU(tiempoPromedioUsoCpu);
    n->asignarPromedioIO(tiempoPromedioUsoIO);
    n->asignarPromedioTotalSistema(tiempoPromedioTotalSistema);

    emit almacenarResultados(n);
}

void Simulacion::evento1()
{
    proceso *p = new proceso();

    //Si el CPU está libre, se envía programa a CPU
    if(CPULibre == true){

        CPULibre = false;
        float tiempoCPUactual = reloj + (quanSims/2) + distribucionUniforme( ((float)random())/100 );
        printf("2 %9.6f\n",tiempoCPUactual);
        manejadorEventos->indicarProximaSalidaCpu(tiempoCPUactual,p);
        //Se suma estadística de tiempo de uso de la CPU y tiempo total en el sistema del programa
        manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCPU(tiempoCPUactual);
        manejadorEventos->obtenerProximoProcesoCPU()->sumarPromedioTotalSistema(
        manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCPU());
    }
    else{
        colaListosCPU.enqueue(p);
        p->actualizarEntradaCola(reloj);
    }
    float proximoArribo = eleccionDistribucion();
    manejadorEventos->indicarProximoArribo(reloj + proximoArribo);
}

void Simulacion::evento2(){
    //manejadorEventos->proximoSalirCpu->sumarTiempoCola( reloj - manejadorEventos->proximoSalirCpu->entradaCola );
    double tiempoCPUactual;
    double tiempoIOactual;
    int siguienteEvento = random();

    if(siguienteEvento < 50) siguienteEvento = 1;
    else if (siguienteEvento >= 50 && siguienteEvento < 70) siguienteEvento = 2;
         else siguienteEvento = 3;

    switch(siguienteEvento){
        case 1: // Va para CPU
            if(colaListosCPU.size() > 0){
                manejadorEventos->obtenerProximoProcesoCPU()->actualizarEntradaCola(reloj);
                colaListosCPU.append(manejadorEventos->obtenerProximoProcesoCPU());

                //emit this->actNumCola(colaListosCPU.size());

                tiempoCPUactual = reloj + (quanSims/2) + distribucionUniforme( ((float)random())/100 );
                manejadorEventos->indicarProximaSalidaCpu(tiempoCPUactual, colaListosCPU.dequeue() );

                //Se suman estadísticas de tiempo en cola, tiempo de uso de la CPU, y tiempo total en el sistema del programa
                manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCPU(tiempoCPUactual);
                manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCola(reloj);
                manejadorEventos->obtenerProximoProcesoCPU()->sumarPromedioTotalSistema(
                manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCPU() +
                manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCola());
            }
            else{
                tiempoCPUactual = reloj + (quanSims/2) + distribucionUniforme( ((float)random())/100 );
                manejadorEventos->indicarProximaSalidaCpu(tiempoCPUactual, manejadorEventos->obtenerProximoProcesoCPU() );

                //Se suma estadística de tiempo de uso de la CPU y tiempo total en el sistema del programa
                manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCPU(tiempoCPUactual);
                manejadorEventos->obtenerProximoProcesoCPU()->sumarPromedioTotalSistema(
                manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCPU());
            }
            break;

        case 2: // Va para IO
            if(colaListosCPU.size() > 0){
                tiempoCPUactual = reloj + (quanSims/2) + distribucionUniforme( ((float)random())/100 );
                manejadorEventos->indicarProximaSalidaCpu(tiempoCPUactual, colaListosCPU.dequeue() );
                //emit this->actNumCola(colaListosCPU.size());

                //Se suman estadísticas de tiempo en cola, tiempo de uso de la CPU, y tiempo total en el sistema del programa
                manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCPU(tiempoCPUactual);
                manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCola(reloj);
                manejadorEventos->obtenerProximoProcesoCPU()->sumarPromedioTotalSistema(
                            manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCPU() +
                            manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCola());
            }
            else{
                CPULibre = true;
                //emit this->actCpu(CPULibre);
            }

            if(IOLibre == true){
                IOLibre = false;
                tiempoIOactual = distribucionIO( ((float)random())/100 );
                manejadorEventos->indicarProximaSalidaIO(tiempoIOactual, manejadorEventos->obtenerProximoProcesoCPU());
                                                                                           //no es próximo proceso IO?
                manejadorEventos->obtenerProximoProcesoIO()->sumarTiempoDispositivo(tiempoIOactual);
            }
            else{
                manejadorEventos->obtenerProximoProcesoCPU()->actualizarEntradaCola(reloj);
                colaListosDispositivos.enqueue(manejadorEventos->obtenerProximoProcesoCPU());
                //emit this->actNumColaDis( colaListosDispositivos.size() );
            }
            break;

        case 3: // Va para Salida
            if(colaListosCPU.size() > 0){
                tiempoCPUactual = reloj + (quanSims/2) + distribucionUniforme( ((float)random())/100 );
                manejadorEventos->indicarProximaSalidaCpu(tiempoCPUactual, colaListosCPU.dequeue() );
                //emit this->actNumCola(colaListosCPU.size());

                //Se suman estadísticas de tiempo en cola, tiempo de uso de la CPU, y tiempo total en el sistema del programa
                manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCPU(tiempoCPUactual);
                manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCola(reloj);
                manejadorEventos->obtenerProximoProcesoCPU()->sumarPromedioTotalSistema(
                manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCPU() +
                manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCola());
            }
            else{
                //No hace falta sacar lo que va a durar el proceso actual en CPU?
                CPULibre = true;
            }
            colaSalida.enqueue(manejadorEventos->obtenerProximoProcesoCPU());
            break;
    }

}


//Evnento: Salida de un proceso de la cola de dispositivos
void Simulacion::evento3(){
    proceso * p = new proceso();
    manejadorEventos->indicarProximaSalidaIO(reloj + 10,p);
    double tiempoCPUactual;
    double tiempoIOactual;

    //Obtiene el proceso sacado
    proceso * procesoListoDispositivo;

    if(colaListosDispositivos.size() > 0)
    {
        procesoListoDispositivo = colaListosDispositivos.front();

        //Elimina el proceso de la cola de dispositivos
        colaListosDispositivos.pop_front();

        //Si queda un proceso en la cola de dispositivos, entonces avisa al manejador de eventos
        if(colaListosDispositivos.size() > 0)
        {
            tiempoIOactual = distribucionIO( ((float)random())/100 );
           //Obtiene el proceso que esta de primero en la lista
           manejadorEventos->indicarProximaSalidaIO(tiempoIOactual, colaListosDispositivos.front());
           //Estadíticas de proceso que acaba de salir de IO
           colaListosDispositivos.front()->sumarTiempoDispositivo(tiempoIOactual);
           colaListosDispositivos.front()->sumarTiempoCola(reloj);
           manejadorEventos->obtenerProximoProcesoCPU()->sumarPromedioTotalSistema(
                       manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoIO() +
                       manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCola());
        }
        else
        {
            manejadorEventos->vaciarSalidaIO();
        }


        //Decide que hacer con el proceso que salio de la cola de dispositivos

        if(CPULibre)
        {
            //Avisa que este proceso sera el proximo en salir del cpu
            tiempoCPUactual = reloj + (quanSims/2) + distribucionUniforme( ((float)random())/100 );
            manejadorEventos->indicarProximaSalidaCpu(tiempoCPUactual, procesoListoDispositivo);

            //Actualiza estadísticas de proceso que va a salir de CPU
            procesoListoDispositivo->sumarTiempoCPU(tiempoCPUactual);
            procesoListoDispositivo->sumarTiempoCola(reloj);
            manejadorEventos->obtenerProximoProcesoCPU()->sumarPromedioTotalSistema(
                        manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCPU() +
                        manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCola());

            CPULibre = false;
            emit this->actCpu(CPULibre);
        }
        else //Manda el proceso a la cola de listos
        {
            colaListosCPU.push_front(procesoListoDispositivo);
            //emit this->actNumCola(colaListosCPU.size());
            //Actualiza entrada en cola de proceso
            procesoListoDispositivo->actualizarEntradaCola(reloj);
        }
    }


}

void Simulacion::estadisticasSim(){

    /*QList<nodoEstadisticas*>::iterator i;
    nodoEstadisticas *n;
    for (i = listaEstadisticas.begin(); i != listaEstadisticas.end(); i++){
        n = *i;
        tiempoPromedioUsoCpu += n->obtenerPromedioCPU();
        tiempoPromedioUsoIO += n->obtenerPromedioIO();
        tiempoPromedioColas += n->obtenerPromedioColas();
    }
    tiempoPromedioUsoCpu = tiempoPromedioUsoCpu / listaEstadisticas.size();
    tiempoPromedioUsoIO = tiempoPromedioUsoIO / listaEstadisticas.size();
    tiempoPromedioColas = tiempoPromedioColas / listaEstadisticas.size();
    //Falta tiempo promedio colas
    if(contadorUsosIO != 0)
    {
        tiempoPromedioUsoIO = tiempoPromedioUsoCpu / listaEstadisticas.size();
    }

    if(contadorUsosCpu != 0)
    {
        tiempoPromedioUsoCpu = tiempoPromedioUsoCpu / listaEstadisticas.size();
    }*/

    //ocupacionServidor = tiempoPromedioUsoCpu / tiemSims;
    //coeficienteEficiencia = tiempoPromedioColas / tiempoPromedioTotalSistema;
    //Actualiza los contadores globales
    //tiempoPromedioUsoCpuTotal += tiempoPromedioUsoCpu;
    //tiempoPromedioUsoIOTotal += tiempoPromedioUsoIO;


}

int Simulacion::random()
{
    return rand() % 100;
}

float Simulacion::eleccionDistribucion(){
    float valor = 0;

    if(exp == true) valor = distribucionExponencial(((float)random())/100);
    else valor = distribucionNormal();

    return valor;
}

float Simulacion::distribucionExponencial(float random)
{
    return ( (- log(1-random)) / media);
}

//( random * ( quanSims/2 - 0) + 0 ), a = 0 y b = quanSims/2
//( random * (quanSims/2) )
float Simulacion::distribucionUniforme(float random)
{
    return ( random * (quanSims/2) );
}

float Simulacion::distribucionNormal()
{
    //float resultado = ( (-2 * log(random1)) * 1/2 * (cos(2 * M_PI * random2)) );

    //if(resultado > 0) return resultado;

    //return ( (-2 * log(random1)) * 1/2 * (sin(2 * M_PI * random2)) );
    float acumulado = 0;
    for(int i = 1; i < 13; ++i)
        acumulado = acumulado + ((float)random())/100;
    return varianza * (acumulado - 6) + media;
}

float Simulacion::distribucionIO(float random)
{
    return 20 * sqrt(3 * random + 1);
}
