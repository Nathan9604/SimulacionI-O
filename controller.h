#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QAbstractListModel>
#include <QVector>
#include <QtCore>
#include <sstream>

#include "simulacion.h"

class controller : public QAbstractListModel
{
    Q_OBJECT

    protected:
        QVector<QString> resultados;
        QVector<Simulacion *> sims;
        QList<nodoEstadisticas *> listaEstadisticas;
        Simulacion *sim;

        //Estadisticas de todas las simulaciones. Esto no ocupa contadores ya que dichos contadores equivalen a la cantidad total de simulaciones
        double ocupacionServidorTotal;
        double coeficienteEficienciaTotal;
        double tiempoPromedioUsoCpuTotal;
        double tiempoPromedioUsoIOTotal;

        int filasLeidas = 0;


    public:
        explicit controller(QObject *parent = nullptr);
        void initSim(int numSim, int tiemSim, int quanSim, bool expon);
        void simular(int numSim, int tiemSim, int quanSim, bool expon);
        void promSims();

    public: // Overriden methods from QAbastractListModel
        virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    protected:
        virtual bool canFetchMore(const QModelIndex &parent) const override;
        virtual void fetchMore(const QModelIndex &parent) override;

    signals:
        void actualiceReloj(float reloj);
        void actualiceEvento(int evento);
        void actualiceCpu(bool usoCpu);
        void actualiceIo(bool usoIo);
        void actualiceNumCola(int numCola);
        void actualiceNumSal(int numSal);
        void actualiceNumColaIO(int numColaIO);

    protected slots:
        void actReloj(float reloj);
        void actEvento(int evento);
        void actCpu(bool usoCpu);
        void actIo(bool usoIo);
        void actNumCola(int numCola);
        void actNumSal(int numSal);
        void actNumColaIO(int numColaIO);
        void almacenarResultados(nodoEstadisticas * nuevo);
};

#endif // CONTROLLER_H
