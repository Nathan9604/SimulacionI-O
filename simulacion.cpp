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

    contadorUsosCpu = 0;
    contadorUsosIO = 0;

    //Inicializa el manejador de eventos
    manejadorEventos = new ManejadorEventos();

}

void Simulacion::correrSim(){
    // Desde acá se realiza los eventos falta evento 1, 2, 3 y el que saca las estadisticas al final. además de la clase proceso

    // Ejemplo para verlo correr.
    int reloj = 0;
    for(int i = 0; i < tiemSims; i++){
        ++reloj;

        int evento = manejadorEventos->ObtenerEventoMasProximo();

        switch(evento)
        {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
        }


        //emit this->actReloj(reloj);
        //reloj = manejadorEventos->obtenerProximoTiempo();

    }
    printf("\n");
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
