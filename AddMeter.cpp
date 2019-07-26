#include "AddMeter.h"
#include <ui_AddMeter.h>
#include <QMessageBox>

AddMeters::AddMeters(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::myAddMeter)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ok()));

}

void AddMeters::ok()
{
    QString bat = ui->lineEdit_9->text();
    QList<QString> SENT;
    Archives_Configuration_Table n;
    n.NUM = ui->lineEdit->text();
    SENT.append(n.NUM);
    n.TSA = ui->lineEdit_2->text();
    SENT.append(n.TSA);
    n.baud_rate = "0" + QString::number(ui->comboBox->currentIndex());
    SENT.append(n.baud_rate);
    n.meter_style = "0" + QString::number(ui->comboBox_2->currentIndex());
    SENT.append(n.meter_style);
    n.port = ui->comboBox_3->currentText();
    SENT.append(n.port);
    n.password = ui->lineEdit_3->text();
    SENT.append(n.password);
    n.fee_count = "0" + ui->lineEdit_4->text();
    SENT.append(n.fee_count);
    n.user_style = ui->lineEdit_5->text();
    SENT.append(n.user_style);
    n.connect_way = "0" + QString::number(ui->comboBox_4->currentIndex());
    SENT.append(n.connect_way);
    n.Rated_Voltage = ui->lineEdit_6->text();
    SENT.append(n.Rated_Voltage);
    n.Rated_Electric_current = ui->lineEdit_12->text();
    SENT.append(n.Rated_Electric_current);
    n.collect_TSA = ui->lineEdit_7->text();
    SENT.append(n.collect_TSA);
    n.detail_num = ui->lineEdit_11->text();
    SENT.append(n.detail_num);
    n.PT = ui->lineEdit_8->text();
    SENT.append(n.PT);
    n.CT = ui->lineEdit_10->text();
    SENT.append(n.CT);
    if (n.NUM == "" or n.TSA == "" or n.TSA.length() < 12)
    {
        QMessageBox::warning(this, "错误", "输入错误", QMessageBox::Ok);
    } else
    {
        if (ui->lineEdit_9->text() != "0")
        {
            int times = ui->lineEdit_9->text().toInt(nullptr, 10) - 1;
            emit send_list(SENT);
            while (times)
            {
                SENT[0] = (QString) (SENT[0].toInt(nullptr, 10) + 1);
                SENT[1] = (QString) (SENT[1].toInt(nullptr, 10) + 1);

                times -= 1;
            }
        } else
        {
            emit send_list(SENT);
            close();
        }

    }

}

