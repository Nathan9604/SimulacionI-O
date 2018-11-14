#include "proceso.h"

proceso::proceso()
{
    tiempoCola = 0;
    entradaCola = 0;
}

proceso::sumarTiempoCola(float cantidad)
{
    tiempoCola += cantidad;
}

proceso::actualizarEntradaCola(float reloj)
{
    entradaCola = reloj;
}
