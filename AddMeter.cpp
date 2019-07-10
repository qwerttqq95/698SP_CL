#include "AddMeter.h"
#include <ui_AddMeter.h>

AddMeters::AddMeters(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::myAddMeter) {
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(ok()));
}

void AddMeters::ok() {
    Archives_Configuration_Table n;
    n.NUM = ui->lineEdit->text();
    n.TSA = ui->lineEdit_2->text();
    n.baud_rate = ui->comboBox->currentText();
    n.meter_style = ui->comboBox_2->currentIndex();
    n.port = ui->comboBox_3->currentIndex();
    n.password = ui->lineEdit_3->text();
    n.fee_count = ui->lineEdit_4->text();
    n.user_style = ui->lineEdit_5->text();
    n.connect_way = ui->comboBox_4->currentIndex();
    n.Rated_Voltage = ui->lineEdit_6->text();
    n.Rated_Electric_current = ui->lineEdit_12->text();
    n.collect_TSA = ui->lineEdit_7->text();
    n.detail_num = ui->lineEdit_11->text();
    n.PT = ui->lineEdit_8->text();
    n.CT = ui->lineEdit_10->text();
    QString bat = ui->lineEdit_9->text();


}

