#ifndef PROCESO_H
#define PROCESO_H


class proceso
{
protected:
    float tiempoCola;
    float entradaCola;
public:
    proceso();
    void sumarTiempoCola(float cantidad);
    void actualizarEntradaCola(float reloj);
};

#endif // PROCESO_H
