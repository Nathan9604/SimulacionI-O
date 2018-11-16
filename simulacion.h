#ifndef SIMULACION_H
#define SIMULACION_H

#include <QtCore>
#include "manejadoreventos.h"

class Simulacion : public QThread
{
    Q_OBJECT

    protected:
        int numSims;
        int tiemSims;
        int quanSims;
        bool exp;       //¿Es exponencial?
        int varianza;
        int media;

        //Estadisticas de la simulacion actual
        double ocupacionServidor;
        double coeficienteEficiencia;
        double tiempoPromedioUsoCpu;
        double tiempoPromedioUsoIO;

        int contadorUsosCpu;
        int contadorUsosIO;

        //Utilizadas para calcular proximo valor del reloj
        ManejadorEventos * manejadorEventos;

        int reloj;
        bool CPULibre;
        bool IOLibre;

        QQueue<proceso *> colaListosCPU;
        QQueue<proceso *> colaListosDispositivos;

    public:
        Simulacion(int numSim, int tiemSim, int quanSim, bool expon);
        void correrSim();
        void estadisticasSim();
        void evento1();
        void evento2();
        void evento3();

    signals:
        void actReloj(int reloj);
        void actEvento(int evento);
        void actCpu(bool usoCpu);
        void actIo(bool usoIo);
        void actNumCola(int numCola);
        void actNumSal(int numSal);
};

#endif // SIMULACION_H
