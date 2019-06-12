#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "serial.h"
#include "ui_serial.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("698SP V1.0");
    connect(ui->actionA,SIGNAL(triggered()),this,SLOT(about()));
    connect(ui->actionSd,SIGNAL(triggered()),this,SLOT(serial_config()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::about(){
    QMessageBox::information(this,"关于","698SP C++ V1.0",QMessageBox::Ok);
}

void MainWindow::serial_config(){
    serial = new Serial();
    serial->show();

}