#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "ui_serial.h"
#include <iostream>

using namespace std;

extern string DtoB(int);

extern QString StringAddSpace(QString &input);

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
    serial = new Serial();
    setWindowTitle("698SP V1.0");
    connect(ui->actionA, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionSd, SIGNAL(triggered()), this, SLOT(serial_config()));
    connect(ui->action, SIGNAL(triggered()), this, SLOT(send_find_add()));
    connect(serial, SIGNAL(send_message(QString)), this, SLOT(show_message_send(QString)));
    connect(serial, SIGNAL(receive_message(QString)), this, SLOT(show_message_receive(QString)));
    serial->show();
}

bool MainWindow::analysis(QString a) {
    QStringList list = a.split(' ', QString::SkipEmptyParts);
    int message_len = list[2].toInt(nullptr, 16) + list[1].toInt(nullptr, 16);  //报文长度
    int ctrl_zone = list[3].toInt(nullptr, 16); //控制域
    int SA_len = list[4].toInt(nullptr, 16) & 0xF;
    QString add = "";
    for (int i = 0; i <= SA_len; i++) {
        add = list[5 + i] + add;
    }
    ui->lineEdit->setText(add);
    revert_add = "";
    for (int i = 0; i <= SA_len; i++) {
        revert_add = revert_add + list[5 + i];
    }
    int apdu_0 = 10 + SA_len;
    switch (list[apdu_0].toInt(nullptr, 16)) {
        case 0x85: {
            switch (list[apdu_0 + 1].toInt(nullptr, 16))
                case 0x01: {
                    GET_RESPOND_NORMAL n;

                }break;
            case 0x03: {

            }

        }
            break;
        default:
            break;
    }

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

void MainWindow::show_message_send(QString a) {
    ui->textEdit_2->append("发送:");
    ui->textEdit_2->append(StringAddSpace(a));
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    QString x = tmp;
    ui->textEdit_2->append(x);
    ui->textEdit_2->append("———————————————————————————");
}

void MainWindow::show_message_receive(QString a) {
    ui->textEdit_2->append("收到:");
    ui->textEdit_2->append(a);
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    QString x = tmp;
    ui->textEdit_2->append(x);
    ui->textEdit_2->append("———————————————————————————");
    analysis(a);
}

