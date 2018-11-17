#ifndef PROCESO_H
#define PROCESO_H


class proceso
{
protected:
    float tiempoCola;
    float entradaCola;
    float tiempoCPU;
    float tiempoDispositivo;
public:
    proceso();
    ~proceso();
    void sumarTiempoCola(float cantidad);
    void actualizarEntradaCola(float reloj);
    void sumarTiempoCPU(float cantidad);
    void sumarTiempoDispositivo(float cantidad);


    //lo mismo con io y cpu
    /*void sumarTiempoCola(float cantidad);
    void actualizarEntradaCola(float reloj);*/
};

#endif // PROCESO_H
