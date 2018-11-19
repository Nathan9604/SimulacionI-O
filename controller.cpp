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
        this->connect( this->sim, &Simulacion::actNumColaIO, this, &controller::actNumColaIO );
        this->connect( this->sim, &Simulacion::almacenarResultados, this, &controller::almacenarResultados );

        //Ejecuta la simulación y luego le saca las estádisticas.
        sim->start();
        sim->estadisticasSim();

        //Agrege las estádisticas a la lista de despliegue

        //Agrega la simulación al vector de simulaciones.
        sims.append(sim);

        /*QString h = "Corrida " + QString::number( i ) + "\n" + "Tiempo promedio total programa en el sistema = " + QString::number(n->obtenerPromedioTotalSistema()) +
        "\n" + "Tiempo promedio programa en CPU = " + QString::number(n->obtenerPromedioCPU()) + "\n" + "Ocupación del servidor = " + QString::number(n->obtenerOcupacionServidor()) + "\n" +
        "Tiempo de uso promedio de dispositivo E/S = " + QString::number(n->obtenerPromedioIO()) + "\n" + "Promedio tiempo en colas = " + QString::number(n->obtenerPromedioColas()) + "\n" +
        "Coeficiente de eficiencia = " + QString::number(n->obtenerCoeficienteEficiencia()) + "\n";*/
        //resultados.append(h);
    }

    //Promedia todas las simulaciones y las muestra en pantalla.
    this->promSims();

    this->filasLeidas = 0;
    this->endResetModel();
    //RECORDAR ELIMINAR SIMS
}

void controller::promSims(){
    QList<nodoEstadisticas*>::iterator i;
    nodoEstadisticas *n;
    resultados.append( "***************************************************");
    resultados.append("Promedio total de la simulación");
    for (i = listaEstadisticas.begin(); i != listaEstadisticas.end(); i++){
        n = *i;
        tiempoPromedioUsoCpuTotal += n->obtenerPromedioCPU();
        tiempoPromedioUsoIOTotal += n->obtenerPromedioIO();
        tiempoPromedioColasTotal += n->obtenerPromedioColas();
        ocupacionServidorTotal += n->obtenerOcupacionServidor();
        coeficienteEficienciaTotal += n->obtenerCoeficienteEficiencia();
    }
    tiempoPromedioUsoCpuTotal = tiempoPromedioUsoCpuTotal / listaEstadisticas.size();
    tiempoPromedioUsoIOTotal = tiempoPromedioUsoIOTotal / listaEstadisticas.size();
    tiempoPromedioColasTotal = tiempoPromedioColasTotal / listaEstadisticas.size();

    ocupacionServidorTotal = ocupacionServidorTotal / listaEstadisticas.size();
    coeficienteEficienciaTotal = coeficienteEficienciaTotal / listaEstadisticas.size();
    tiempoPromedioTotalSistema = tiempoPromedioUsoCpuTotal + tiempoPromedioColasTotal + tiempoPromedioUsoIOTotal / listaEstadisticas.size();
    resultados.append("Tiempo promedio total programa en el sistema = " + QString::number(tiempoPromedioTotalSistema) +
            "\n" + "Tiempo promedio programa en CPU = " + QString::number(tiempoPromedioUsoCpuTotal) + "\n" + "Ocupación del servidor = " + QString::number(ocupacionServidorTotal) + "\n" +
            "Tiempo de uso promedio de dispositivo E/S = " + QString::number(tiempoPromedioUsoIOTotal) + "\n" + "Promedio tiempo en colas = " + QString::number(tiempoPromedioColasTotal) + "\n" +
            "Coeficiente de eficiencia = " + QString::number(coeficienteEficienciaTotal) + "\n");
    resultados.append( "***************************************************");
}

void controller::actReloj(float reloj){
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

void controller::actNumColaIO(int numColaIO){
    emit this->actualiceNumColaIO(numColaIO);
}

void controller::almacenarResultados(nodoEstadisticas * n){
    resultados.append("Tiempo promedio total programa en el sistema = " + QString::number(n->obtenerPromedioTotalSistema()) +
            "\n" + "Tiempo promedio programa en CPU = " + QString::number(n->obtenerPromedioCPU()) + "\n" + "Ocupación del servidor = " + QString::number(n->obtenerOcupacionServidor()) + "\n" +
            "Tiempo de uso promedio de dispositivo E/S = " + QString::number(n->obtenerPromedioIO()) + "\n" + "Promedio tiempo en colas = " + QString::number(n->obtenerPromedioColas()) + "\n" +
            "Coeficiente de eficiencia = " + QString::number(n->obtenerCoeficienteEficiencia()) + "\n");
    resultados.append( "***************************************************");

    listaEstadisticas.append(n);
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
