#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QAbstractListModel>
#include <QVector>
#include <QtCore>
#include <QQueue>

#include "simulacion.h"
#include "proceso.h"

class controller : public QAbstractListModel
{
    Q_OBJECT

    protected:
        QVector<QString> resultados;
        QVector<Simulacion *> sims;
        Simulacion *sim;
        QQueue<proceso> colaListos;
        QQueue<proceso> colaDispositivos;

        //Estadisticas de todas las simulaciones. Esto no ocupa contadores ya que dichos contadores equivalen a la cantidad total de simulaciones
        double ocupacionServidorTotal;
        double coeficienteEficienciaTotal;
        double tiempoPromedioUsoCpuTotal;
        double tiempoPromedioUsoIOTotal;


    public:
        explicit controller(QObject *parent = nullptr);
        void initSim(int numSim, int tiemSim, int quanSim, bool expon);
        void simular(int numSim, int tiemSim, int quanSim, bool expon);
        void promSims();

    public: // Overriden methods from QAbastractListModel
        virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    signals:
        void actualiceReloj(int reloj);
        void actualiceEvento(int evento);
        void actualiceCpu(bool usoCpu);
        void actualiceIo(bool usoIo);
        void actualiceNumCola(int numCola);
        void actualiceNumSal(int numSal);

    protected slots:
        void actReloj(int reloj);
        void actEvento(int evento);
        void actCpu(bool usoCpu);
        void actIo(bool usoIo);
        void actNumCola(int numCola);
        void actNumSal(int numSal);
};

#endif // CONTROLLER_H
