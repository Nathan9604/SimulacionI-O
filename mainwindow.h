#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtCore>
#include <QMainWindow>

#include "controller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_OkButtom_2_accepted();
    void on_OkButtom_2_rejected();
    void actualiceReloj(float reloj);
    void actualiceEvento(int evento);
    void actualiceCpu(bool cpuLibre);
    void actualiceIo(bool ioLibre);
    void actualiceNumCola(int numCola);
    void actualiceNumSal(int numSal);
    void actualiceNumColaIO(int numColaIO);
    void mostrarResultados();

private:
    Ui::MainWindow *ui;
    controller *con = nullptr;
};

#endif // MAINWINDOW_H
