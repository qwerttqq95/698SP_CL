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
    connect(this, SIGNAL(send_analysis(QString)), this, SLOT(analysis_show(QString)));
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
    int apdu_0 = 9 + SA_len;

    switch (list[apdu_0].toInt(nullptr, 16)) {
        case 0x85: {
            switch (list[apdu_0 + 1].toInt(nullptr, 16))
                case 0x1: {
                    GET_RESPOND_NORMAL n;
                    n.PIIDACD = list[apdu_0 + 2];
                    n.OAD = "";
                    for (int i = 1; i < 5; i++) {
                        n.OAD = n.OAD + list[apdu_0 + 2 + i];
                    }
                    n.GET_RESULT_TYPE = list[apdu_0 + 7];
                    n.DATA = list.mid(apdu_0 + 8, list.length() - apdu_0 - 11);
                    emit send_analysis(n.OAD + " : " + deal_data(n.DATA));
                }
            break;
        }
            break;
    }

}

QString MainWindow::deal_data(QStringList a) {
    switch (a[0].toInt(nullptr, 16)) {
        case DATA_OCT_STRING: {
            QString text = "";
            for (int i = 0; i < a[1].toInt(nullptr, 16); i++) {
                text = text + a[2 + i];
            }
            return text;
        }

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
    ui->textEdit_2->append("解析:");
    analysis(a);
    ui->textEdit_2->append("———————————————————————————");
}

void MainWindow::analysis_show(QString a) {
    ui->textEdit_2->append(a);
}


