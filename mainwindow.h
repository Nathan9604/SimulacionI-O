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
    void actualiceReloj(int reloj);
    void actualiceEvento(int evento);
    void actualiceCpu(bool usoCpu);
    void actualiceIo(bool usoIo);
    void actualiceNumCola(int numCola);
    void actualiceNumSal(int numSal);

private:
    Ui::MainWindow *ui;
    controller *con = nullptr;
};

#endif // MAINWINDOW_H
