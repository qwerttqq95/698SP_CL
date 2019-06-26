#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "ui_serial.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
    serial = new Serial();
    setWindowTitle("698SP V1.0");
    connect(ui->actionA, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionSd, SIGNAL(triggered()), this, SLOT(serial_config()));
    connect(ui->action, SIGNAL(triggered()), this, SLOT(send_find_add()));
    connect(serial,SIGNAL(send_message(QString)),this,SLOT(show_message(QString)));
}

void MainWindow::send_find_add() {
    QString add = "6817004345AAAAAAAAAAAA10DA5F0501034001020000900f16";
    emit serial->send_write(add);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::about() {
    QMessageBox::information(this, "关于", "698SP C++ V1.0", QMessageBox::Ok);
}

void MainWindow::serial_config() {
    serial->show();
}

void MainWindow::show_message(QString a) {
    ui->textEdit_2->append(a);
}

