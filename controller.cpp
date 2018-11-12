#include "controller.h"

controller::controller(QObject *parent)
    : QAbstractListModel(parent)
{
}

void controller::simular(int numSim, int tiemSim, int quanSim, bool expon){

    for(int i = 0; i < numSim; i++){
        sim = new Simulacion(numSim, tiemSim, quanSim, expon);

        // Realiza la conección entre simulación y el controller.
        this->connect( this->sim, &Simulacion::actReloj, this, &controller::actReloj );
        this->connect( this->sim, &Simulacion::actEvento, this, &controller::actEvento );
        this->connect( this->sim, &Simulacion::actCpu, this, &controller::actCpu );
        this->connect( this->sim, &Simulacion::actIo, this, &controller::actIo );
        this->connect( this->sim, &Simulacion::actNumCola, this, &controller::actNumCola );
        this->connect( this->sim, &Simulacion::actNumSal, this, &controller::actNumSal );

        //Ejecuta la simulación y luego le saca las estádisticas.
        sim->correrSim();
        sim->estadisticasSim();

        //Agrege las estádisticas a la lista de despliegue

        //Agrega la simulación al vector de simulaciones.
        sims.append(sim);
    }

    //Promedia todas las simulaciones y las muestra en pantalla.
    this->promSims();

    //RECORDAR ELIMINAR SIMS
}

void controller::promSims(){
    //Promedia todas las simulaciones.
}

void controller::actReloj(int reloj){
    emit this->actualiceReloj(reloj);
}

void controller::actEvento(int evento){
    emit this->actualiceEvento(evento);
}

void controller::actCpu(bool usoCpu){
    emit this->actualiceCpu(usoCpu);
}

void controller::actIo(bool usoIo){
    emit this->actualiceIo(usoIo);
}

void controller::actNumCola(int numCola){
    emit this->actualiceNumCola(numCola);
}

void controller::actNumSal(int numSal){
    emit this->actualiceNumSal(numSal);
}

int controller::rowCount(const QModelIndex &parent) const
{
   // Q_UNUSED(parent);
    //return this->fetchedRowCount;
}


QVariant controller::data(const QModelIndex &index, int role) const
{
    /*if ( ! index.isValid() )
        return QVariant();

    if ( index.row() < 0 || index.row() >= totalResults.count() )//
        return QVariant();

    if (role == Qt::DisplayRole)
    {
            if(totalResults.count() > index.row()){
                return totalResults[index.row()];
            }
    }

    return QVariant();*/
}
