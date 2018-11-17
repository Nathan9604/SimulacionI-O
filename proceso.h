#ifndef PROCESO_H
#define PROCESO_H


class proceso
{
protected:
    double tiempoCola;
    double entradaCola;
    double tiempoCPU;
    double tiempoDispositivo;
public:
    proceso();
    ~proceso();
    void sumarTiempoCola(double cantidad);
    void actualizarEntradaCola(double reloj);
    void sumarTiempoCPU(double cantidad);
    void sumarTiempoDispositivo(double cantidad);

    double obtenerTiempoCPU();
    double obtenerTiempoIO();
    double obtenerTiempoCola();


    //lo mismo con io y cpu
    /*void sumarTiempoCola(float cantidad);
    void actualizarEntradaCola(float reloj);*/
};

#endif // PROCESO_H
