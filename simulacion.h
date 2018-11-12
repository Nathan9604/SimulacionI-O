#ifndef SIMULACION_H
#define SIMULACION_H

#include <QtCore>

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

    public:
        Simulacion(int numSim, int tiemSim, int quanSim, bool expon);
        void correrSim();
        void estadisticasSim();

    signals:
        void actReloj(int reloj);
        void actEvento(int evento);
        void actCpu(bool usoCpu);
        void actIo(bool usoIo);
        void actNumCola(int numCola);
        void actNumSal(int numSal);
};

#endif // SIMULACION_H
