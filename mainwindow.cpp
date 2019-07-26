#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "ui_serial.h"
#include <ui_Custom_APDU.h>
#include <MeterArchives.h>
#include <ui_MeterArchives.h>
#include <iostream>
#include <QScrollBar>

using namespace std;

extern QString BuildMessage(QString apdu, QString SA, QString ctrl_zone);

extern QString StringAddSpace(QString &input);

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new Serial();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->tableWidget->setToolTipDuration(50);
    setWindowTitle("698SP V1.0");
    connect(ui->actionA, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionSd, SIGNAL(triggered()), this, SLOT(serial_config()));
    connect(ui->actionAPDUzu, SIGNAL(triggered()), this, SLOT(custom()));
    connect(ui->action, SIGNAL(triggered()), this, SLOT(send_find_add()));
    connect(serial, SIGNAL(send_message(QString)), this, SLOT(show_message_send(QString)));
    connect(serial, SIGNAL(receive_message(QString)), this, SLOT(show_message_receive(QString)));
    connect(this, SIGNAL(send_analysis(QString)), this, SLOT(analysis_show(QString)));//解析
    connect(ui->actionbiaodangan, SIGNAL(triggered()), this, SLOT(open_MeterArchives()));
    connect(ui->actionSdf, SIGNAL(triggered()), this, SLOT(custom_test()));
    serial->show();
}

void MainWindow::custom_test()
{

}

void MainWindow::move_Cursor()
{
    ui->tableWidget->scrollToBottom();
}

void MainWindow::open_MeterArchives()
{
    MeterArchive = new MeterArchives(revert_add);
    connect(MeterArchive, SIGNAL(send_write(QString)), serial, SLOT(write(QString)), Qt::UniqueConnection);
    connect(MeterArchive, SIGNAL(send_write2(QString)), serial, SLOT(write(QString)));
    connect(this, SIGNAL(deal_with_meter(QList<QString>)), MeterArchive, SLOT(show_meter_message(QList<QString>)));
    MeterArchive->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    serial->close();
    close();
}

QString MainWindow::analysis(QString a)
{
    QStringList list = a.split(' ', QString::SkipEmptyParts);
    int message_len = (list[2] + list[1]).toInt(nullptr, 16);  //报文长度
    int ctrl_zone = list[3].toInt(nullptr, 16); //控制域
    int SA_len = list[4].toInt(nullptr, 16) & 0xF;
    QString add = "";
    for (int i = 0; i <= SA_len; i++)
    {
        add = list[5 + i] + add;
    }
    ui->lineEdit->setText(add);
    revert_add = "";
    for (int i = 0; i <= SA_len; i++)
    {
        revert_add = revert_add + list[5 + i];
    }
    int apdu_0 = 9 + SA_len;
//    qDebug() << "cheshi" << list[apdu_0].toInt(nullptr, 16) << endl << list[apdu_0 + 1].toInt(nullptr, 16);
    switch (list[apdu_0].toInt(nullptr, 16))
    {
        case 0x01:
        {
            LINK_REQUEST n;
            n.PIIDACD = list[apdu_0 + 1];
            n.LINK_REQUSET_TYPE = list[apdu_0 + 2];
            n.HEART_BEAT_INTERVAL = list[apdu_0 + 3] + list[apdu_0 + 4];
            n.REQUEST_TIMEDATE_TIME = "";
            for (int i = 1; i < 11; i++)
            {
                n.REQUEST_TIMEDATE_TIME = n.REQUEST_TIMEDATE_TIME + list[apdu_0 + 4 + i];
            }
            char year[5];
            time_t timep;
            time(&timep);
            strftime(year, sizeof(year), "%Y", localtime(&timep));
            QString y = year;
            sprintf(year, "%04X", y.toInt(nullptr, 10));
            char tmp[30];
            strftime(tmp, sizeof(tmp), "%m %d 0%w %H %M %S 00 00", localtime(&timep));
            QString mouth_to_s = tmp;
            QString date_times = "";
            QList<QString> date_time;
            date_time = mouth_to_s.split(' ');
            for (int i = 0; i < date_time.length(); i++)
            {
                char temp[3];
                sprintf(temp, "%02X", date_time[i].toInt(nullptr, 10));
                date_times = date_times + temp;
            }
            QString APDU = "81" + n.PIIDACD + "80" + n.REQUEST_TIMEDATE_TIME + year + date_times + year + date_times;
            emit
            serial->send_write(BuildMessage(APDU, revert_add, "01"));
            return "登录/心跳";
        }
            break;
        case 0x85:
        {
            switch (list[apdu_0 + 1].toInt(nullptr, 16))
            {
                case 0x1:
                {
                    GET_RESPOND_NORMAL n;
                    n.PIIDACD = list[apdu_0 + 2];
                    n.OAD = "";
                    for (int i = 1; i < 5; i++)
                    {
                        n.OAD = n.OAD + list[apdu_0 + 2 + i];
                    }
                    n.GET_RESULT_TYPE = list[apdu_0 + 7];
                    n.DATA = list.mid(apdu_0 + 8, list.length() - apdu_0 - 11);
                    if (n.OAD == "60000200")
                    {
                        qDebug() << "收到表档案信息";
                        emit deal_with_meter(n.DATA);
                    }

                    emit send_analysis(n.OAD + " : " + deal_data(n.DATA));//解析
                }
                    break;
                case 0x5:
                {
                    GetResponseNext n;
                    n.PIIDACD = list[apdu_0 + 2];
                    n.is_last_frame = list[apdu_0 + 3];
                    n.slicing_index = list[apdu_0 + 4] + list[apdu_0 + 5];

                    n.GetResponseNextType = list[apdu_0 + 6];
                    n.SequenceOf_ResultNormal = list[apdu_0 + 7];
                    n.OAD = "";
                    for (int i = 1; i < 5; i++)
                    {
                        n.OAD = n.OAD + list[apdu_0 + 7 + i];
                    }
                    n.GET_RESULT_TYPE = list[apdu_0 + 12];
                    n.DATA = list.mid(apdu_0 + 13, list.length() - apdu_0 - 11);

                    if (n.OAD == "60000200")
                    {
                        qDebug() << "收到多表档案信息";
                        emit deal_with_meter(n.DATA);
                    }

                    if (n.is_last_frame == "00")
                    {
                        QString text = "0505" + n.PIIDACD + n.slicing_index + "00";
                        emit
                        serial->send_write(BuildMessage(text, revert_add, "43"));
                        times++;
                        return QString().sprintf("收到分帧,第%d帧", times);
                    }
                    if (n.is_last_frame == "01")
                    {
                        times = 0;
                        return "最后一帧";
                    }
                }
                default:
                    qDebug() << "850?";
                    break;
            }
        }
            break;
        case 0x87:
        {
            switch (list[apdu_0 + 1].toInt(nullptr, 16))
            {
                case 0x1:
                {
                    switch (list[apdu_0 + 2].toInt(nullptr, 16))
                    {
                        case 0:
                            return "成功";
                        case 8:
                            return "越界";
                        case 15:
                            return "密码错误/未授权";
                            // 68 1a 00 c3 05 56 34 12 56 34 12 10 9e 98 87 01 1c 81 03 03 00 00 00 00 00 c4 80 16
                        default:
                            return "未知";
                    }


                }
            }
        }
            break;
    }
    return "";
}

QString MainWindow::deal_data(QStringList a)
{
    switch (a[0].toInt(nullptr, 16))
    {
        case DATA_OCT_STRING:
        {
            QString text = "";
            for (int i = 0; i < a[1].toInt(nullptr, 16); i++)
            {
                text = text + a[2 + i];
            }
            return text;
        }

        default:
            break;
    }
    return "";
}

void MainWindow::send_find_add()
{
    QString add = "6817004345AAAAAAAAAAAA10DA5F0501034001020000900f16";
    emit serial->send_write(add);                   ////发送
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::about()
{
    QMessageBox::information(this, "关于", "698SP C++ V1.0", QMessageBox::Ok);
}

void MainWindow::serial_config()
{
    serial->show();
}


void MainWindow::custom()
{
    Custom = new Custom_APDU(revert_add);
    connect(Custom, SIGNAL(send_write(QString)), serial, SLOT(write(QString)), Qt::UniqueConnection);
    Custom->show();
}

void MainWindow::show_message_send(QString a)
{
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%H:%M:%S", localtime(&timep));
    QString x = tmp;
    ui->tableWidget->insertRow(current);
    ui->tableWidget->setItem(current, 0, new QTableWidgetItem("发送:"));
    ui->tableWidget->setItem(current, 1, new QTableWidgetItem(StringAddSpace(a)));
    ui->tableWidget->setItem(current, 3, new QTableWidgetItem(x));
    ui->tableWidget->item(current, 1)->setToolTip(StringAddSpace(a));
    current += 1;
    move_Cursor();
}

void MainWindow::show_message_receive(QString a)
{
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%H:%M:%S", localtime(&timep));
    QString x = tmp;
    ui->tableWidget->insertRow(current);
    ui->tableWidget->setItem(current, 0, new QTableWidgetItem("收到:"));
    QString te = analysis(a);
    ui->tableWidget->setItem(current, 1, new QTableWidgetItem(a));
    ui->tableWidget->setItem(current, 2, new QTableWidgetItem(te));
    ui->tableWidget->setItem(current, 3, new QTableWidgetItem(x));
    ui->tableWidget->item(current, 1)->setToolTip(a);
    current += 1;
    move_Cursor();

}

void MainWindow::analysis_show(QString a)
{
//    ui->textEdit_2->append(a);
}

