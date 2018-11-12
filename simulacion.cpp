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
}

void Simulacion::correrSim(){
    // Desde acá se realiza los eventos falta evento 1, 2, 3 y el que saca las estadisticas al final. además de la clase proceso

    // Ejemplo para verlo correr.
    int reloj = 0;
    for(int i = 0; i < tiemSims; i++){
        ++reloj;
        emit this->actReloj(reloj);
    }
    printf("\n");
}

void Simulacion::estadisticasSim(){

}
