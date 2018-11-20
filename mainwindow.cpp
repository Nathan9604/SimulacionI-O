#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabla->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Botón de aceptar
void MainWindow::on_OkButtom_2_accepted()
{
    if( ui->numSims->value() >= 1 && ui->tiemSims->value() >= 1 && ui->quanSims->value() >= 1
            && (ui->normal->isChecked() == true || ui->exponencial->isChecked() == true) ){

        // Deshabilita la inicialización y pasa a la página de la simulación.
        ui->tabla->setCurrentIndex(1);
        ui->errorText->setText("");
        ui->tabla->setTabEnabled(0, false);

        // Crea y vincula las señales.
        this->con = new controller(this);

        // Conección de signals y sloths
        this->connect( this->con, &controller::actualiceReloj, this, &MainWindow::actualiceReloj );
        this->connect( this->con, &controller::actualiceEvento, this, &MainWindow::actualiceEvento );
        this->connect( this->con, &controller::actualiceCpu, this, &MainWindow::actualiceCpu );
        this->connect( this->con, &controller::actualiceIo, this, &MainWindow::actualiceIo );
        this->connect( this->con, &controller::actualiceNumCola, this, &MainWindow::actualiceNumCola );
        this->connect( this->con, &controller::actualiceNumSal, this, &MainWindow::actualiceNumSal );
        this->connect( this->con, &controller::actualiceNumColaIO, this, &MainWindow::actualiceNumColaIO );
        this->connect( this->con, &controller::mostrarResultados, this, &MainWindow::mostrarResultados );

        // Llamado al programa
        this->con->simular( ui->numSims->value(), ui->tiemSims->value(), ui->quanSims->value(), ui->exponencial->isChecked() );

        // Carga en pantalla los datos.
        ui->stats->setModel(con);

        // Limpia todo antes de terminar.
        ui->numSims->setValue(1);
        ui->tiemSims->setValue(1);
        ui->quanSims->setValue(1);

        //Habilita la inicialización.
        ui->tabla->setTabEnabled(0, true);
    }
    else{
        // Error intente de nuevo.
        ui->errorText->setText("Faltan datos, ingreselos.");
        ui->errorText->setStyleSheet("QLabel { color : red; }");
    }
}

// Botón de cancelar
void MainWindow::on_OkButtom_2_rejected()
{
    // Inicialice los valores de nuevo.
    ui->numSims->setValue(1);
    ui->tiemSims->setValue(1);
    ui->quanSims->setValue(1);
}

// Actualiza reloj en pantalla
void MainWindow::actualiceReloj(float reloj){
    ui->reloj->setText( QString::number(reloj) );
}

// Actualiza el número de evento en pantalla
void MainWindow::actualiceEvento(int evento){
    ui->numEvRes->setText( QString::number(evento) );
}

// Actualiza el uso de CPU en pantalla
void MainWindow::actualiceCpu(bool cpuLibre){
    if(cpuLibre == false){
        ui->cpuVal->setText("Ocupado");
        ui->cpuVal->setStyleSheet("QLabel { color : red; }");
    }
    else{
        ui->cpuVal->setText("Libre");
        ui->cpuVal->setStyleSheet("QLabel { color : green; }");
    }
}

// Actualiza el uso de IO en pantalla
void MainWindow::actualiceIo(bool ioLibre){
    if(ioLibre == false){
        ui->ioVal->setText("Ocupado");
        ui->ioVal->setStyleSheet("QLabel { color : red; }");
    }
    else{
        ui->ioVal->setText("Libre");
        ui->ioVal->setStyleSheet("QLabel { color : green; }");
    }
}

// Actualiza la cantidad de procesos en cola de listos
void MainWindow::actualiceNumCola(int numCola){
    ui->numCol->setText( QString::number(numCola) );
}

// Actualiza la cantidad de procesos que salieron del sistema
void MainWindow::actualiceNumSal(int numSal){
    ui->numTer->setText( QString::number(numSal) );
}

// Actualiza la cantidad de procesos en cola de IO
void MainWindow::actualiceNumColaIO(int numColaIO){
    ui->numColIO->setText( QString::number(numColaIO) );
}

// Muestra resultados al finalizar las simulaciones
void MainWindow::mostrarResultados(){
    ui->tabla->setCurrentIndex(2);
}
