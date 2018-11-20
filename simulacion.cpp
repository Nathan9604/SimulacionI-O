#include "simulacion.h"
#include <stdlib.h>
#include <time.h>

Simulacion::Simulacion(int numSim, int tiemSim, int quanSim, bool expon)
{
    // Carga valores en variables
    numSims = numSim;
    tiemSims = (float)tiemSim;
    quanSims = quanSim;
    exp = expon;

    // Establece media y varianza dependiendo de la distribución elegida
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
    ocupacionServidor = 0;

    CPULibre = true;
    IOLibre = true;

    contadorUsosCpu = 0;
    contadorUsosIO = 0;

    //Inicializa el manejador de eventos
    srand (time(NULL));
    manejadorEventos = new ManejadorEventos();

}

// Inicio del hilo
void Simulacion::run(){
    correrSim();
}

void Simulacion::correrSim(){
    int evento = 1;
    reloj = 0;
    tiempoPromedioColas = 0;
    tiempoPromedioUsoCpu = 0;
    tiempoPromedioUsoIO = 0;
    coeficienteEficiencia = 0;

    evento1();
    do{
        // Pide el próximo evento
        evento = manejadorEventos->ObtenerEventoMasProximo();

        // Actualiza los datos de la pantalla
        emit this->actReloj(reloj);
        emit this->actCpu(CPULibre);
        emit this->actIo(IOLibre);
        emit this->actEvento(evento);
        emit this->actNumCola(colaListosCPU.size());
        emit this->actNumSal(colaSalida.size());
        emit this->actNumColaIO(colaListosDispositivos.size());

        // llamado de los eventos
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

        // Valor del reloj en el próximo evento
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
        tiempoPromedioTotalSistema += p->obtenerPromedioTotalSistema();
    }
    tiempoPromedioColas = tiempoPromedioColas / colaSalida.size();
    tiempoPromedioUsoCpu = tiempoPromedioUsoCpu / colaSalida.size();
    tiempoPromedioUsoIO = tiempoPromedioUsoIO / colaSalida.size();
    tiempoPromedioTotalSistema = tiempoPromedioColas + tiempoPromedioUsoCpu + tiempoPromedioUsoIO / colaSalida.size();

    ocupacionServidor = tiempoPromedioUsoCpu / tiemSims;
    coeficienteEficiencia = tiempoPromedioColas / tiempoPromedioTotalSistema;

    //Se guardan las estadísticas de cada simulación en la lista de estadísticas
    nodoEstadisticas *n = new nodoEstadisticas();
    n->asignarPromedioColas(tiempoPromedioColas);
    n->asignarPromedioCPU(tiempoPromedioUsoCpu);
    n->asignarPromedioIO(tiempoPromedioUsoIO);
    n->asignarPromedioTotalSistema(tiempoPromedioTotalSistema);
    n->asignarCoeficienteEficiencia(coeficienteEficiencia);
    n->asignarOcupacionServidor(ocupacionServidor);

    emit almacenarResultados(n);
}

void Simulacion::evento1()
{
    proceso *p = new proceso();

    //Si el CPU está libre, se envía programa a CPU
    if(CPULibre == true){
        CPULibre = false;
        float tiempoCPUactual = reloj + (quanSims/2) + distribucionUniforme( ((float)random())/100 );
        manejadorEventos->indicarProximaSalidaCpu(tiempoCPUactual,p);
        //Se suma estadística de tiempo de uso de la CPU y tiempo total en el sistema del programa
        manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCPU(tiempoCPUactual - reloj);
        manejadorEventos->obtenerProximoProcesoCPU()->sumarPromedioTotalSistema(
        manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCPU());
    }
    else{
        //Se envía a cola de listos para CPU
        colaListosCPU.enqueue(p);
        p->actualizarEntradaCola(reloj);
    }
    //Se calcula próximo arribo
    float proximoArribo = eleccionDistribucion();
    manejadorEventos->indicarProximoArribo(reloj + proximoArribo);
}

void Simulacion::evento2(){
    double tiempoCPUactual;
    double tiempoIOactual;
    int siguienteEvento = random(); // Averigua si el proceso sale, va a IO o espera por CPU

    // Establece el valor para el switch
    if(siguienteEvento < 50) siguienteEvento = 1;
    else if (siguienteEvento >= 50 && siguienteEvento < 70) siguienteEvento = 2;
         else siguienteEvento = 3;

    switch(siguienteEvento){
        case 1: // Va para CPU
            // Hay alguien en la cola de CPU
            if(colaListosCPU.size() > 0){
                // Guarda el proceso del CPU en la cola de espera por CPU
                manejadorEventos->obtenerProximoProcesoCPU()->actualizarEntradaCola(reloj);
                colaListosCPU.append(manejadorEventos->obtenerProximoProcesoCPU());

                // Establece el tiempo en el que el nuevo proceso usará el CPU y se lo asigna
                tiempoCPUactual = reloj + (quanSims/2) + distribucionUniforme( ((float)random())/100 );
                manejadorEventos->indicarProximaSalidaCpu(tiempoCPUactual, colaListosCPU.dequeue() );

                //Se suman estadísticas de tiempo en cola, tiempo de uso de la CPU, y tiempo total en el sistema del programa
                manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCPU(tiempoCPUactual - reloj);
                manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCola(reloj);
                manejadorEventos->obtenerProximoProcesoCPU()->sumarPromedioTotalSistema(
                manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCPU() +
                manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCola());
            }
            else{
                // Como no hay nadie en cola, el proceso puede volver a usar la cola, se define el tiempo de el nuevo uso
                tiempoCPUactual = reloj + (quanSims/2) + distribucionUniforme( ((float)random())/100 );
                manejadorEventos->indicarProximaSalidaCpu(tiempoCPUactual, manejadorEventos->obtenerProximoProcesoCPU() );

                //Se suma estadística de tiempo de uso de la CPU y tiempo total en el sistema del programa
                manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCPU(tiempoCPUactual - reloj);
                manejadorEventos->obtenerProximoProcesoCPU()->sumarPromedioTotalSistema(
                manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCPU());
            }
            break;

        case 2: // Va para IO

            // Si hay alguien en el dispositivo de IO envie el proceso a cola, sino dejelo usar el dispositivo
            if(IOLibre == true){
                IOLibre = false;

                // Se le asigna el tiempo de uso de IO y lo deja usarlo
                tiempoIOactual = reloj + distribucionIO( ((float)random())/100 );
                manejadorEventos->indicarProximaSalidaIO(tiempoIOactual, manejadorEventos->obtenerProximoProcesoCPU());

                manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoDispositivo(tiempoIOactual - reloj);
            }
            else{
                // Como el dispositivo está ocupado, envielo a la cola de IO
                manejadorEventos->obtenerProximoProcesoCPU()->actualizarEntradaCola(reloj);
                colaListosDispositivos.enqueue(manejadorEventos->obtenerProximoProcesoCPU());
            }

            // Si hay alguien esperando por CPU asigneselo antes de enviar el proceso a cola de IO o a IO
            if(colaListosCPU.size() > 0){
                // Se establece el tiempo en el que el nuevo proceso se le permite usar el CPU y se le asigna
                tiempoCPUactual = reloj + (quanSims/2) + distribucionUniforme( ((float)random())/100 );
                manejadorEventos->indicarProximaSalidaCpu(tiempoCPUactual, colaListosCPU.dequeue() );

                //Se suman estadísticas de tiempo en cola, tiempo de uso de la CPU, y tiempo total en el sistema del programa
                manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCPU(tiempoCPUactual - reloj);
                manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCola(reloj);
                manejadorEventos->obtenerProximoProcesoCPU()->sumarPromedioTotalSistema(
                            manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCPU() +
                            manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCola());
            }
            else{
                // Como no hay nadie en cola el CPU se pasa a libre
                CPULibre = true;
            }
            break;

        case 3: // Va para Salida

            // Si hay alguien en la cola de CPU envielo al CPU
            if(colaListosCPU.size() > 0){
                // Se define el tiempo de uso de CPU y se le asigna
                tiempoCPUactual = reloj + (quanSims/2) + distribucionUniforme( ((float)random())/100 );
                manejadorEventos->indicarProximaSalidaCpu(tiempoCPUactual, colaListosCPU.dequeue() );

                // Se suman estadísticas de tiempo en cola, tiempo de uso de la CPU, y tiempo total en el sistema del programa
                manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCPU(tiempoCPUactual - reloj);
                manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCola(reloj);
                manejadorEventos->obtenerProximoProcesoCPU()->sumarPromedioTotalSistema(
                manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCPU() +
                manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCola());
            }
            else{
                // Como no hay nadie en cola de CPU deje el CPU libre
                CPULibre = true;
            }

            // Envie el proceso a la cola de salida
            colaSalida.enqueue(manejadorEventos->obtenerProximoProcesoCPU());
            break;
    }

}


//Evnento: Salida de un proceso de la cola de dispositivos
void Simulacion::evento3(){
    //proceso * p = new proceso();
    //manejadorEventos->indicarProximaSalidaIO(reloj + 10,p);
    double tiempoCPUactual;
    double tiempoIOactual;

    //Obtiene el proceso sacado
    //proceso * procesoListoDispositivo;

    //if(colaListosDispositivos.size() > 0)
    //{
        //Elimina el proceso de la cola de dispositivos
        //procesoListoDispositivo = colaListosDispositivos.dequeue();

    //Decide que hacer con el proceso que salio de la cola de dispositivos

    if(CPULibre)
    {
        //Avisa que este proceso sera el proximo en salir del cpu
        tiempoCPUactual = reloj + (quanSims/2) + distribucionUniforme( ((float)random())/100 );
        manejadorEventos->indicarProximaSalidaCpu(tiempoCPUactual, manejadorEventos->obtenerProximoProcesoIO());

        //Actualiza estadísticas de proceso que va a salir de CPU
        //procesoListoDispositivo->sumarTiempoCPU(tiempoCPUactual - reloj);
        //procesoListoDispositivo->sumarTiempoCola(reloj);
        manejadorEventos->obtenerProximoProcesoCPU()->sumarPromedioTotalSistema(
                    manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCPU() +
                    manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCola());

        CPULibre = false;
        //emit this->actCpu(CPULibre);
    }
    else //Manda el proceso a la cola de listos
    {
        colaListosCPU.enqueue(manejadorEventos->obtenerProximoProcesoIO());
        //emit this->actNumCola(colaListosCPU.size());
        //Actualiza entrada en cola de proceso
        //procesoListoDispositivo->actualizarEntradaCola(reloj);
    }

        //Si queda un proceso en la cola de dispositivos, entonces avisa al manejador de eventos
        if(colaListosDispositivos.size() > 0)
        {            
            tiempoIOactual = reloj + distribucionIO( ((float)random())/100 );
           //Obtiene el proceso que esta de primero en la lista
           manejadorEventos->indicarProximaSalidaIO(tiempoIOactual, colaListosDispositivos.dequeue());
           //Estadíticas de proceso que acaba de salir de IO
           //colaListosDispositivos.front()->sumarTiempoDispositivo(tiempoIOactual - reloj);
           //colaListosDispositivos.front()->sumarTiempoCola(reloj);
           manejadorEventos->obtenerProximoProcesoCPU()->sumarPromedioTotalSistema(
                       manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoIO() +
                       manejadorEventos->obtenerProximoProcesoCPU()->obtenerTiempoCola());
        }
        else
        {
            IOLibre = true;
            manejadorEventos->vaciarSalidaIO();
        }



    /*}
    else
    {
        manejadorEventos->vaciarSalidaIO();
    }*/


}

//Saca el promedio de cada corrida
nodoEstadisticas* Simulacion::estadisticasSim()
{
    //Son los promedios de cada corrida, no el total
    proceso *p;
    tiempoPromedioUsoCpu = 0;
    tiempoPromedioUsoIO = 0;
    tiempoPromedioColas = 0;
    ocupacionServidor = 0;
    coeficienteEficiencia = 0;
    tiempoPromedioTotalSistema = 0;
    QList<proceso*>::iterator i;
    for (i = colaSalida.begin(); i != colaSalida.end(); i++){
        p = *i;
        tiempoPromedioUsoCpu += p->obtenerTiempoCPU();
        tiempoPromedioUsoIO += p->obtenerTiempoIO();
        tiempoPromedioColas += p->obtenerTiempoCola();
        tiempoPromedioTotalSistema += p->obtenerPromedioTotalSistema();
    }
    tiempoPromedioColas = tiempoPromedioColas / colaSalida.size();
    tiempoPromedioUsoCpu = tiempoPromedioUsoCpu / colaSalida.size();
    tiempoPromedioUsoIO = tiempoPromedioUsoIO / colaSalida.size();
    tiempoPromedioTotalSistema = tiempoPromedioColas + tiempoPromedioUsoCpu + tiempoPromedioUsoIO / colaSalida.size();

    ocupacionServidor = tiempoPromedioUsoCpu / tiemSims;
    coeficienteEficiencia = tiempoPromedioColas / tiempoPromedioTotalSistema;

    //Se guardan las estadísticas de cada simulación en la lista de estadísticas
    nodoEstadisticas *n = new nodoEstadisticas();
    n->asignarPromedioColas(tiempoPromedioColas);
    n->asignarPromedioCPU(tiempoPromedioUsoCpu);
    n->asignarPromedioIO(tiempoPromedioUsoIO);
    n->asignarPromedioTotalSistema(tiempoPromedioTotalSistema);
    n->asignarCoeficienteEficiencia(coeficienteEficiencia);
    n->asignarOcupacionServidor(ocupacionServidor);
    return n;
}

// Devuelve un valor random de 0 a 99
int Simulacion::random()
{
    return rand() % 100;
}

// Decide cual de las dos distribuciones ejecutar para el arribo de procesos
float Simulacion::eleccionDistribucion(){
    float valor = 0;

    if(exp == true) valor = distribucionExponencial(((float)random())/100);
    else valor = distribucionNormal();

    return valor;
}

// Generar un valor para una distribución exponencial
float Simulacion::distribucionExponencial(float random)
{
    return ( (- log(1-random)) / media);
}

// Generar un valor para una distribución uniforme
//( random * ( quanSims/2 - 0) + 0 ), a = 0 y b = quanSims/2
//( random * (quanSims/2) )
float Simulacion::distribucionUniforme(float random)
{
    return ( random * (quanSims/2) );
}

// Generar un valor para una distribución normal por teorema del límite central con K = 12
float Simulacion::distribucionNormal()
{
    float acumulado = 0;
    for(int i = 1; i < 13; ++i)
        acumulado = acumulado + ((float)random())/100;
    return varianza * (acumulado - 6) + media;
}

// Generar un valor para la distribución correspondiente al IO
float Simulacion::distribucionIO(float random)
{
    return 20 * sqrt(3 * random + 1);
}

double Simulacion::obtenerTiempoCPUGlobal()
{
    return tiempoPromedioUsoCpu;
}

double Simulacion::obtenerTiempoIOGlobal()
{
    return tiempoPromedioUsoIO;
}

double Simulacion::obtenerTiempoColasGlobal()
{
    return tiempoPromedioColas;
}

double Simulacion::obtenerCoeficienteEficienciaGlobal()
{
    return coeficienteEficiencia;
}

double Simulacion::obtenerOcupacionServidorGlobal()
{
    return ocupacionServidor;
}

double Simulacion::obtenerTiempoTotalSistema()
{
    return tiempoPromedioTotalSistema;
}
