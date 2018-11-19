#ifndef NODOESTADÍSTICAS_H
#define NODOESTADÍSTICAS_H

class nodoEstadisticas
{
    protected:
    double tiempoPromedioUsoCpu;
    double tiempoPromedioUsoIO;
    double tiempoPromedioColas;

    public:
    nodoEstadisticas();
    ~nodoEstadisticas();
    double obtenerPromedioCPU();
    double obtenerPromedioIO();
    double obtenerPromedioColas();
    void asignarPromedioCPU(double nuevo);
    void asignarPromedioIO(double nuevo);
    void asignarPromedioColas(double nuevo);
};

#endif // NODOESTADÍSTICAS_H
