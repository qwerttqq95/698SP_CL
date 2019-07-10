//
// Created by admin on 5/7/2019.
//
#include "MeterArchives.h"
#include <ui_MeterArchives.h>
#include <thread>

extern QString BuildMessage(QString apdu, QString SA);

extern VALUE_LEFT Data_deal(QList<QString> a);

MeterArchives::MeterArchives(QString add, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::myMeterArchives) {
    ui->setupUi(this);
    addmeter = new AddMeters();
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(show_add()));
    add_ = std::move(add);
//    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(clearlist()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(Get_6000200()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(clearlist()));
    connect(ui->checkBox, SIGNAL(clicked()), this, SLOT(select_all_checkbox()), Qt::DirectConnection);
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(del()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(clear_6000200()));
    for (int i = 0; i != ui->tableWidget->columnCount(); i++) {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }

}

void MeterArchives::show_add() {
    addmeter->show();
}
void MeterArchives::Get_6000200() {
    QString text = "0501006000020000";
    QString re_message = BuildMessage(text, add_);
    emit send_write(re_message);
}

void MeterArchives::clear_6000200() {
    QString text = "070101600086000000";
    QString re_message = BuildMessage(text, add_);
    emit send_write(re_message);
}

void MeterArchives::clearlist() {
    row_count = 0;
    for (int row = ui->tableWidget->rowCount(); row >= 0; --row) {
        ui->tableWidget->removeRow(row);
    }

}


void MeterArchives::show_meter_message(QList<QString> a) {
    Archives_Configuration_Table n;
    a.removeFirst();
    int times = (a.takeFirst()).toInt(nullptr, 16);
    for (int i = 0; i < times; i++) {
        VALUE_LEFT m, n1;
        m = Data_deal(a);
        n.NUM = m.value;
        m = Data_deal(m.left);
        n.TSA = m.value;
        m = Data_deal(m.left);
        n.baud_rate = m.value;
        m = Data_deal(m.left);
        n.meter_style = m.value;
        m = Data_deal(m.left);
        n.port = m.value;
        m = Data_deal(m.left);
        n.password = m.value;
        m = Data_deal(m.left);
        n.fee_count = m.value;
        m = Data_deal(m.left);
        n.user_style = m.value;
        m = Data_deal(m.left);
        n.connect_way = m.value;
        m = Data_deal(m.left);
        n.Rated_Voltage = m.value;
        m = Data_deal(m.left);
        n.Rated_Electric_current = m.value;
        m = Data_deal(m.left);
        n.collect_TSA = m.value;
        m = Data_deal(m.left);
        n.detail_num = m.value;
        m = Data_deal(m.left);
        n.PT = m.value;
        m = Data_deal(m.left);
        n.CT = m.value;
        a = m.left;
        ui->tableWidget->insertRow(row_count);

        QTableWidgetItem *checkBox = new QTableWidgetItem();
        checkBox->setCheckState(Qt::Unchecked);
        ui->tableWidget->setItem(row_count, 0, checkBox);

        ui->tableWidget->setItem(row_count, 1, new QTableWidgetItem(n.NUM));
        ui->tableWidget->setItem(row_count, 2, new QTableWidgetItem(n.TSA));
        ui->tableWidget->setItem(row_count, 3, new QTableWidgetItem(n.baud_rate));
        ui->tableWidget->setItem(row_count, 4, new QTableWidgetItem(n.meter_style));
        ui->tableWidget->setItem(row_count, 5, new QTableWidgetItem(n.port));
        ui->tableWidget->setItem(row_count, 6, new QTableWidgetItem(n.password));
        ui->tableWidget->setItem(row_count, 7, new QTableWidgetItem(n.fee_count));
        ui->tableWidget->setItem(row_count, 8, new QTableWidgetItem(n.user_style));
        ui->tableWidget->setItem(row_count, 9, new QTableWidgetItem(n.connect_way));
        ui->tableWidget->setItem(row_count, 10, new QTableWidgetItem(n.Rated_Voltage));
        ui->tableWidget->setItem(row_count, 11, new QTableWidgetItem(n.Rated_Electric_current));
        ui->tableWidget->setItem(row_count, 12, new QTableWidgetItem(n.collect_TSA));
        ui->tableWidget->setItem(row_count, 13, new QTableWidgetItem(n.detail_num));
        ui->tableWidget->setItem(row_count, 14, new QTableWidgetItem(n.PT));
        ui->tableWidget->setItem(row_count, 15, new QTableWidgetItem(n.CT));
        row_count += 1;
    }
}

void MeterArchives::all() {
    if (ui->checkBox->checkState() == Qt::Checked) {
        for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
            ui->tableWidget->item(i, 0)->setCheckState(Qt::CheckState::Checked);
        }
    } else {
        for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
            ui->tableWidget->item(i, 0)->setCheckState(Qt::CheckState::Unchecked);
        }
    }
    qApp->processEvents();
}

void MeterArchives::del() {
    for (int i = ui->tableWidget->rowCount() - 1; i >= 0; i--) {
        if (ui->tableWidget->item(i, 0)->checkState() == Qt::Checked) {
            ui->tableWidget->removeRow(i);
        }
    }
}

void MeterArchives::select_all_checkbox() {
    std::thread t1(&MeterArchives::all, this);
    t1.detach();
}

