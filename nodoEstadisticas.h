#ifndef NODOESTADÍSTICAS_H
#define NODOESTADÍSTICAS_H

//Son las estadísticas de una corrida
class nodoEstadisticas
{
    protected:
    //Variables que registran estadísticas
    double tiempoPromedioUsoCpu;
    double tiempoPromedioUsoIO;
    double tiempoPromedioColas;
    double tiempoPromedioTotalSistema;
    double coeficienteEficiencia;
    double ocupacionServidor;

    public:
    //Constructor
    nodoEstadisticas();
    //Destructor
    ~nodoEstadisticas();

    //Se obtiene el tiempo promedio en CPU de la corrida
    double obtenerPromedioCPU();
    //Se obtiene el tiempo promedio en IO de la corrida
    double obtenerPromedioIO();
    //Se obtiene el tiempo promedio en colas de la corrida
    double obtenerPromedioColas();
    //Se obtiene el tiempo promedio total en el sistema de la corrida
    double obtenerPromedioTotalSistema();
    //Se obtiene ocupación del servidor
    double obtenerOcupacionServidor();
    //Se obtiene coeficiente eficiencia
    double obtenerCoeficienteEficiencia();

    //Se asigna el tiempo promedio en CPU de la corrida, con el parámetro que llega
    void asignarPromedioTotalSistema(double nuevo);
    //Se asigna el tiempo promedio en IO de la corrida, con el parámetro que llega
    void asignarPromedioCPU(double nuevo);
    //Se asigna el tiempo promedio en colas de la corrida, con el parámetro que llega
    void asignarPromedioIO(double nuevo);
    //Se asigna el tiempo promedio total en el sistema de la corrida, con el parámetro que llega
    void asignarPromedioColas(double nuevo);
    //Se asigna ocupación del servidor de la corrida
    void asignarOcupacionServidor(double nuevo);
    //Se asigna el coeficiente de eficiencia de la corrida
    void asignarCoeficienteEficiencia(double nuevo);
};

#endif // NODOESTADÍSTICAS_H
