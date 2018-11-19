#ifndef PROCESO_H
#define PROCESO_H


class proceso
{
protected:
    double tiempoCola;
    double entradaCola;
    double tiempoCPU;
    double tiempoDispositivo;
    double tiempoPromedioTotalSistema;
public:
    proceso();
    ~proceso();
    void sumarTiempoCola(double cantidad);
    void actualizarEntradaCola(double reloj);
    void sumarTiempoCPU(double cantidad);
    void sumarTiempoDispositivo(double cantidad);
    void sumarPromedioTotalSistema(double cantidad);

    double obtenerPromedioTotalSistema();
    double obtenerTiempoCPU();
    double obtenerTiempoIO();
    double obtenerTiempoCola();


    //lo mismo con io y cpu
    /*void sumarTiempoCola(float cantidad);
    void actualizarEntradaCola(float reloj);*/
};

#endif // PROCESO_H
