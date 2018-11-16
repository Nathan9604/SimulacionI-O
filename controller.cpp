#include "controller.h"

controller::controller(QObject *parent)
    : QAbstractListModel(parent)
{
}

void controller::simular(int numSim, int tiemSim, int quanSim, bool expon){

    for(int i = 0; i < numSim; i++){
        sim = new Simulacion(numSim, tiemSim, quanSim, expon);
printf("iteracion %d\n",i);
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

        QString h = "Prueba " + QString::number( i );
        resultados.append(h);
    }

    //Promedia todas las simulaciones y las muestra en pantalla.
    this->promSims();

    this->filasLeidas = 0;
    this->endResetModel();
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
    Q_UNUSED(parent);
    return this->filasLeidas;
}


QVariant controller::data(const QModelIndex &index, int role) const
{
    if ( ! index.isValid() )
        return QVariant();

    if ( index.row() < 0 || index.row() >= resultados.count() )//
        return QVariant();

    if (role == Qt::DisplayRole)
    {
            if(resultados.count() > index.row()){
                return resultados[index.row()];
            }
    }

    return QVariant();
}


bool controller::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->filasLeidas < resultados.count();
}


void controller::fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent);
    int remainder = 0;
    remainder = resultados.count();
    remainder = remainder - this->filasLeidas;
    int itemsToFetch = qMin(100, remainder);

    if (itemsToFetch <= 0)
        return;

    int firstRow = this->filasLeidas;
    int lastRow = this->filasLeidas + itemsToFetch - 1;

    beginInsertRows(QModelIndex(), firstRow, lastRow);
    this->filasLeidas += itemsToFetch;
    endInsertRows();
}
