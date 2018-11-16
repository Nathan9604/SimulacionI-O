#include "simulacion.h"

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
    manejadorEventos = new ManejadorEventos();

}

void Simulacion::correrSim(){
    // Desde acá se realiza los eventos falta evento 1, 2, 3 y el que saca las estadisticas al final. además de la clase proceso

    // Ejemplo para verlo correr.
    int evento = 1;
    reloj = 0;
    evento1();
    do{
        emit this->actReloj(reloj);
        emit this->actCpu(CPULibre);
        emit this->actIo(IOLibre);
        emit this->actEvento(evento);
        emit this->actNumCola(colaListosCPU.size());
        emit this->actNumSal(colaSalida.size());

        evento = manejadorEventos->ObtenerEventoMasProximo();
        printf("evento %d y reloj %9.6f\n",evento,reloj);
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
}

void Simulacion::evento1()
{
    proceso *p = new proceso();

    if(CPULibre == true){
        CPULibre = false;
        int salidaProceso = reloj + (quanSims/2); //+ distribución 20 a 40
        manejadorEventos->indicarProximaSalidaCpu(salidaProceso,p);
    }
    else{
        colaListosCPU.push_back(p);
        p->actualizarEntradaCola(reloj);
    }
    manejadorEventos->indicarProximoArribo(reloj + 20);
}

void Simulacion::evento2(){
    //manejadorEventos->proximoSalirCpu->sumarTiempoCola( reloj - manejadorEventos->proximoSalirCpu->entradaCola );

    int siguienteEvento = rand() % 100;
    printf("siguienteEvento %d",siguienteEvento);

    if(siguienteEvento < 50) siguienteEvento = 1;
    else if (siguienteEvento >= 50 && siguienteEvento < 70) siguienteEvento = 2;
         else siguienteEvento = 3;

    switch(siguienteEvento){
        case 1: // Va para CPU
            if(colaListosCPU.size() > 0){
                manejadorEventos->obtenerProximoProcesoCPU()->actualizarEntradaCola(reloj);
                colaListosCPU.append(manejadorEventos->obtenerProximoProcesoCPU());

                emit this->actNumCola(colaListosCPU.size());

                manejadorEventos->indicarProximaSalidaCpu(reloj + (quanSims/2) + distribucionUniforme( (random()/100) ), colaListosCPU.dequeue() );
                manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCola(reloj);
                //manejadorEventos->obtenerProximoProcesoCPU()->actualizarEntradaCpu(reloj);
            }
            else{
                manejadorEventos->indicarProximaSalidaCpu(reloj + (quanSims/2) + distribucionUniforme( (random()/100) ), manejadorEventos->obtenerProximoProcesoCPU() );
                //manejadorEventos->obtenerProximoProcesoCPU()->actualizarEntradaCpu(reloj);
            }
            break;

        case 2: // Va para IO
            if(colaListosCPU.size() > 0){
                manejadorEventos->indicarProximaSalidaCpu(reloj + (quanSims/2) + distribucionUniforme( (random()/100) ), colaListosCPU.dequeue() );
                emit this->actNumCola(colaListosCPU.size());

                manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCola(reloj);
                //manejadorEventos->obtenerProximoProcesoCPU()->actualizarEntradaCpu(reloj);
            }
            else{
                CPULibre = true;
                emit this->actCpu(CPULibre);
            }

            //manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCpu(reloj);

            if(IOLibre == true){
                IOLibre = false;
                manejadorEventos->indicarProximaSalidaIO(distribucionIO( (random()/100) ), manejadorEventos->obtenerProximoProcesoCPU());
            }
            else{
                manejadorEventos->obtenerProximoProcesoCPU()->actualizarEntradaCola(reloj);
                colaListosDispositivos.enqueue(manejadorEventos->obtenerProximoProcesoCPU());
                //emit this->actNumColaDis( colaListosDispositivos.size() );
            }
            break;

        case 3: // Va para Salida
            if(colaListosCPU.size() > 0){
                manejadorEventos->indicarProximaSalidaCpu(reloj + (quanSims/2) + distribucionUniforme( (random()/100) ), colaListosCPU.dequeue() );
                emit this->actNumCola(colaListosCPU.size());

                manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCola(reloj);
                //manejadorEventos->obtenerProximoProcesoCPU()->actualizarEntradaCpu(reloj);
            }
            else{
                CPULibre = true;
            }
            //manejadorEventos->obtenerProximoProcesoCPU()->sumarTiempoCpu(reloj);
            colaSalida.enqueue(manejadorEventos->obtenerProximoProcesoCPU());
            break;
    }

}


//Evnento: Salida de un proceso de la cola de dispositivos
void Simulacion::evento3(){
    proceso * p = new proceso();
    manejadorEventos->indicarProximaSalidaIO(reloj + 10,p);

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
           //Obtiene el proceso que esta de primero en la lista
           manejadorEventos->indicarProximaSalidaIO(distribucionIO( (random()/100) ), colaListosDispositivos.front());
        }
        else
        {
            manejadorEventos->vaciarSalidaIO();
        }


        //Decide que hacer con el proceso que salio de la cola de dispositivos

        if(CPULibre)
        {
            //Avisa que este proceso sera el proximo en salir del cpu
            manejadorEventos->indicarProximaSalidaCpu(reloj + (quanSims/2) + distribucionUniforme( (random()/100) ), procesoListoDispositivo);


            CPULibre = false;
            emit this->actCpu(CPULibre);
        }
        else //Manda el proceso a la cola de listos
        {
            colaListosCPU.push_front(procesoListoDispositivo);
            emit this->actNumCola(colaListosCPU.size());
        }
    }


}

void Simulacion::estadisticasSim(){
    //Calcula los promedios

    if(contadorUsosIO != 0)
    {
        tiempoPromedioUsoIO = tiempoPromedioUsoCpu / contadorUsosIO;
    }

    if(contadorUsosCpu != 0)
    {
        tiempoPromedioUsoCpu = tiempoPromedioUsoCpu / contadorUsosCpu;
    }

    //Actualiza los contadores globales
    //tiempoPromedioUsoCpuTotal += tiempoPromedioUsoCpu;
    //tiempoPromedioUsoIOTotal += tiempoPromedioUsoIO;


}

int Simulacion::random()
{
    std::default_random_engine generador;
    std::uniform_int_distribution<int> randomizer(0,99);

    return randomizer(generador);
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

float Simulacion::distribucionNormal(float random1, float random2)
{
    float resultado = ( (-2 * log(random1)) * 1/2 * (cos(2 * M_PI * random2)) );

    if(resultado > 0) return resultado;

    return ( (-2 * log(random1)) * 1/2 * (sin(2 * M_PI * random2)) );
}

float Simulacion::distribucionIO(float random)
{
    return 20 * sqrt(3 * random + 1);
}
