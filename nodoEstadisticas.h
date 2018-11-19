#ifndef NODOESTADÍSTICAS_H
#define NODOESTADÍSTICAS_H

class nodoEstadisticas
{
    protected:
    double tiempoPromedioUsoCpu;
    double tiempoPromedioUsoIO;
    double tiempoPromedioColas;
    double tiempoPromedioTotalSistema;

    public:
    nodoEstadisticas();
    ~nodoEstadisticas();
    double obtenerPromedioCPU();
    double obtenerPromedioIO();
    double obtenerPromedioColas();
    double obtenerPromedioTotalSistema();

    void asignarPromedioTotalSistema(double nuevo);
    void asignarPromedioCPU(double nuevo);
    void asignarPromedioIO(double nuevo);
    void asignarPromedioColas(double nuevo);
};

#endif // NODOESTADÍSTICAS_H
