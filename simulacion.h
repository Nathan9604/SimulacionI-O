#ifndef SIMULACION_H
#define SIMULACION_H

#include <math.h>
#include <QtCore>
#include <QList>
#include <iterator>
#include <random>


#include "manejadoreventos.h"

class Simulacion : public QThread
{
    Q_OBJECT

    protected:
        int numSims;
        float tiemSims;
        int quanSims;
        bool exp;       //¿Es exponencial?
        int varianza;
        int media;

        //Estadisticas de la simulacion actual
        double ocupacionServidor;
        double tiempoPromedioTotalSistema;
        double coeficienteEficiencia;
        double tiempoPromedioUsoCpu;
        double tiempoPromedioUsoIO;
        double tiempoPromedioColas;

        int contadorUsosCpu;
        int contadorUsosIO;

        //Utilizadas para calcular proximo valor del reloj
        ManejadorEventos * manejadorEventos;

        float reloj;
        bool CPULibre;
        bool IOLibre;

        QQueue<proceso *> colaListosCPU;
        QQueue<proceso *> colaListosDispositivos;
        QQueue<proceso *> colaSalida;

        void run();

    public:
        Simulacion(int numSim, int tiemSim, int quanSim, bool expon);
        void correrSim();
        void estadisticasSim();

        int random();
        float distribucionExponencial(float random);
        float distribucionUniforme(float random);
        float distribucionNormal();
        float distribucionIO(float random);
        float eleccionDistribucion();

        void evento1();
        void evento2();
        void evento3();

    signals:
        void actReloj(float reloj);
        void actEvento(int evento);
        void actCpu(bool usoCpu);
        void actIo(bool usoIo);
        void actNumCola(int numCola);
        void actNumSal(int numSal);
        void actNumColaIO(int numColaIO);
        void almacenarResultados(nodoEstadisticas *);
};

#endif // SIMULACION_H
