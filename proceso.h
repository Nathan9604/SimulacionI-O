#ifndef PROCESO_H
#define PROCESO_H

//Es un programa en el sistema
class proceso
{
protected:
    //Son las variables estadísticas de un programa
    double tiempoCola;
    double entradaCola;
    double tiempoCPU;
    double tiempoDispositivo;
    double tiempoPromedioTotalSistema;
public:
    //Constructor
    proceso();
    //Destructor
    ~proceso();

    //Suma la cantidad de tiempo del programa en colas, con el parámetro
    void sumarTiempoCola(double cantidad);
    //Actualiza el tiempo en el que entró el programa a una cola, con el parámetro
    void actualizarEntradaCola(double reloj);
    //Suma la cantidad de tiempo del programa en CPU, con el parámetro
    void sumarTiempoCPU(double cantidad);
    //Suma la cantidad de tiempo del programa en IO, con el parámetro
    void sumarTiempoDispositivo(double cantidad);
    //Suma la cantidad de promedio total del programa en el sistema, con el parámetro
    void sumarPromedioTotalSistema(double cantidad);

    //Se obtiene el tiempo promedio total del programa en el sistema
    double obtenerPromedioTotalSistema();
    //Se obtiene el tiempo en CPU del programa
    double obtenerTiempoCPU();
    //Se obtiene el tiempo en IO del programa
    double obtenerTiempoIO();
    //Se obtiene el tiempo en colas del programa
    double obtenerTiempoCola();


    //lo mismo con io y cpu
    /*void sumarTiempoCola(float cantidad);
    void actualizarEntradaCola(float reloj);*/
};

#endif // PROCESO_H
