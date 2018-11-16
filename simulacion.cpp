#include "simulacion.h"

Simulacion::Simulacion(int numSim, int tiemSim, int quanSim, bool expon)
{
    numSims = numSim;
    tiemSims = tiemSim;
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
    reloj = 0;
    evento1();
    do{

        int evento = manejadorEventos->ObtenerEventoMasProximo();
        printf("evento %d y reloj %d\n",evento,reloj);
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
        emit this->actReloj(reloj);
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
    proceso *p = new proceso();
    manejadorEventos->indicarProximaSalidaCpu( (reloj + quanSims/2) ,p);
    manejadorEventos->indicarProximaSalidaIO(reloj + 5,p);
}

void Simulacion::evento3(){
    proceso *p = new proceso();
    manejadorEventos->indicarProximaSalidaIO(reloj + 10,p);
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
