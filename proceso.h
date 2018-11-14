#ifndef PROCESO_H
#define PROCESO_H


class proceso
{
protected:
    float tiempoCola;
    float entradaCola;
public:
    proceso();
    sumarTiempoCola(float cantidad);
    actualizarEntradaCola(float reloj);
};

#endif // PROCESO_H
