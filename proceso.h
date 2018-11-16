#ifndef PROCESO_H
#define PROCESO_H


class proceso
{
protected:
    float tiempoCola;
    float entradaCola;
public:
    proceso();
    ~proceso();
    void sumarTiempoCola(float cantidad);
    void actualizarEntradaCola(float reloj);


    //lo mismo con io y cpu
    /*void sumarTiempoCola(float cantidad);
    void actualizarEntradaCola(float reloj);*/
};

#endif // PROCESO_H
