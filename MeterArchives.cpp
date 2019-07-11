//
// Created by admin on 5/7/2019.
//
#include "MeterArchives.h"
#include <ui_MeterArchives.h>
#include <thread>
#include <string>
#include <iostream>

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
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(send()));
    connect(addmeter, SIGNAL(send_list(QList<QString>)), this, SLOT(add_new(QList<QString>)));
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

void MeterArchives::add_new(QList<QString> a) {
    Archives_Configuration_Table n;
    n.NUM = a.takeFirst();
    n.TSA = a.takeFirst();
    n.baud_rate = a.takeFirst();
    n.meter_style = a.takeFirst();
    n.port = a.takeFirst();
    n.password = a.takeFirst();
    n.fee_count = a.takeFirst();
    int q = a.takeFirst().toInt(nullptr, 10);
    char st[3];
    sprintf(st, "%02X", q);
    n.user_style = (QString) st;
    n.connect_way = a.takeFirst();
    n.Rated_Voltage = a.takeFirst();
    n.Rated_Electric_current = a.takeFirst();
    n.collect_TSA = a.takeFirst();
    n.detail_num = a.takeFirst();
    n.PT = a.takeFirst();
    n.CT = a.takeFirst();
    ui->tableWidget->insertRow(row_count);
    QTableWidgetItem *checkBox = new QTableWidgetItem();
    checkBox->setCheckState(Qt::Unchecked);
    ui->tableWidget->setItem(row_count, 0, checkBox);
    ui->tableWidget->setItem(row_count, 1, new QTableWidgetItem(n.NUM));
    ui->tableWidget->setItem(row_count, 2, new QTableWidgetItem(n.TSA));
    ui->tableWidget->setItem(row_count, 3, new QTableWidgetItem(n.baud_rate));
    ui->tableWidget->item(row_count, 3)->setToolTip("300bps（0）， 600bps（1）， 1200bps（2），\n"
                                                    "2400bps（3）， 4800bps（4）， 7200bps（5），\n"
                                                    "9600bps（6）， 19200bps（7）， 38400bps（8），\n"
                                                    "57600bps（9），115200bps（10），自适应（255）");
    ui->tableWidget->setItem(row_count, 4, new QTableWidgetItem(n.meter_style));
    ui->tableWidget->item(row_count, 4)->setToolTip("未知 (0)\n"
                                                    "DL/T 645-1997 （1）\n"
                                                    "DL/T 645—2007 （2）\n"
                                                    "DL/T 698.45 （3）\n"
                                                    "CJ/T 188—2004 （4）");
    ui->tableWidget->setItem(row_count, 5, new QTableWidgetItem(n.port));
    ui->tableWidget->setItem(row_count, 6, new QTableWidgetItem(n.password));
    ui->tableWidget->setItem(row_count, 7, new QTableWidgetItem(n.fee_count));
    ui->tableWidget->setItem(row_count, 8, new QTableWidgetItem(n.user_style));
    ui->tableWidget->setItem(row_count, 9, new QTableWidgetItem(n.connect_way));
    ui->tableWidget->item(row_count, 9)->setToolTip("未知 （0）\n"
                                                    "单相 （1）\n"
                                                    "三相三线（2）\n"
                                                    "三相四线（3）");
    ui->tableWidget->setItem(row_count, 10, new QTableWidgetItem(n.Rated_Voltage));
    ui->tableWidget->setItem(row_count, 11, new QTableWidgetItem(n.Rated_Electric_current));
    ui->tableWidget->setItem(row_count, 12, new QTableWidgetItem(n.collect_TSA));
    ui->tableWidget->setItem(row_count, 13, new QTableWidgetItem(n.detail_num));
    ui->tableWidget->setItem(row_count, 14, new QTableWidgetItem(n.PT));
    ui->tableWidget->setItem(row_count, 15, new QTableWidgetItem(n.CT));
    row_count += 1;
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
        ui->tableWidget->item(row_count, 3)->setToolTip("300bps（0）， 600bps（1）， 1200bps（2），\n"
                                                        "2400bps（3）， 4800bps（4）， 7200bps（5），\n"
                                                        "9600bps（6）， 19200bps（7）， 38400bps（8），\n"
                                                        "57600bps（9），115200bps（10），自适应（255）");
        ui->tableWidget->setItem(row_count, 4, new QTableWidgetItem(n.meter_style));
        ui->tableWidget->item(row_count, 4)->setToolTip("未知 (0)\n"
                                                        "DL/T 645-1997 （1）\n"
                                                        "DL/T 645—2007 （2）\n"
                                                        "DL/T 698.45 （3）\n"
                                                        "CJ/T 188—2004 （4）");
        ui->tableWidget->setItem(row_count, 5, new QTableWidgetItem(n.port));
        ui->tableWidget->setItem(row_count, 6, new QTableWidgetItem(n.password));
        ui->tableWidget->setItem(row_count, 7, new QTableWidgetItem(n.fee_count));
        ui->tableWidget->setItem(row_count, 8, new QTableWidgetItem(n.user_style));
        ui->tableWidget->item(row_count, 8)->setToolTip(QString::number(n.user_style.toInt(nullptr, 16)));
        ui->tableWidget->setItem(row_count, 9, new QTableWidgetItem(n.connect_way));
        ui->tableWidget->item(row_count, 9)->setToolTip("未知 （0）\n"
                                                        "单相 （1）\n"
                                                        "三相三线（2）\n"
                                                        "三相四线（3）");
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

void MeterArchives::send() {
    Archives_Configuration_Table n;
    int check_count = 0;
    QList<QString> text;
    QString message;
    for (int i = 0; i <= ui->tableWidget->rowCount() - 1; i++) {
        if (ui->tableWidget->item(i, 0)->checkState() == Qt::Checked) {
            check_count += 1;
            n.NUM = ui->tableWidget->item(i, 1)->text();
            char a[5];
            sprintf(a, "%04x", n.NUM.toInt(nullptr, 10));
            message = "020412" + (QString) a + "020a550705";
            n.TSA = ui->tableWidget->item(i, 2)->text();
            message.append(n.TSA);
            n.baud_rate = ui->tableWidget->item(i, 3)->text();
            if (n.baud_rate.length() == 1) {
                n.baud_rate = "0" + n.baud_rate;
            }
            message.append("16" + n.baud_rate);
            n.meter_style = ui->tableWidget->item(i, 4)->text();
            if (n.meter_style.length() == 1) {
                n.meter_style = "0" + n.meter_style;
            }
            message.append("16" + n.meter_style);
            n.port = ui->tableWidget->item(i, 5)->text();
            message.append("51" + n.port + "090100");
            n.password = "090100";
            n.fee_count = ui->tableWidget->item(i, 7)->text();
            char b[3];
            sprintf(b, "%02x", n.fee_count.toInt(nullptr, 10));
            message.append("11" + (QString) b);
            n.user_style = ui->tableWidget->item(i, 8)->text();
            char c[3];
            sprintf(c, "%02x", n.user_style.toInt(nullptr, 16));
            message.append("11" + (QString) c);
            n.connect_way = ui->tableWidget->item(i, 9)->text();
            if (n.connect_way.length() == 1) {
                n.connect_way = "0" + n.connect_way;
            }
            message.append("16" + n.connect_way);
            n.Rated_Voltage = ui->tableWidget->item(i, 10)->text();
            char d[5];
            sprintf(d, "%04x", n.Rated_Voltage.toInt(nullptr, 10));
            message.append("12" + (QString) d);
            n.Rated_Electric_current = ui->tableWidget->item(i, 11)->text();
            char e[5];
            sprintf(e, "%04x", n.Rated_Voltage.toInt(nullptr, 10));
            message.append("12" + (QString) e + "0204");
            n.collect_TSA = ui->tableWidget->item(i, 12)->text();
            char f[3];
            sprintf(f, "%02x", (n.collect_TSA.length() / 2));
            message.append("55" + (QString) f + n.collect_TSA);
            n.detail_num = ui->tableWidget->item(i, 13)->text();
            message.append("0900");
            n.PT = ui->tableWidget->item(i, 14)->text();
            char g[5];
            sprintf(g, "%04x", n.PT.toInt(nullptr, 10));
            message.append("12" + (QString) g);
            n.CT = ui->tableWidget->item(i, 15)->text();
            char h[5];
            sprintf(h, "%04x", n.CT.toInt(nullptr, 10));
            message.append("12" + (QString) h + "0100");
            text.append(message);
        }
    }
    if (text.length() == 1) {
        QString send_message = "07010060007f00" + text[0] + "00";

    } else {
        int len = text.length();
        int j;
        QString send_message = "";
        while (len > 0) {
            for (j = 1; j < 15 and len > 0; j++, len--) {
                send_message = send_message + text.takeFirst();
            }
            char qw[3];
            sprintf(qw, "%02x", j - 1);
            send_message = "07010060007f0001" + (QString) qw + send_message + "00";
            emit send_write2(BuildMessage(send_message, add_));
            QEventLoop eventloop;
            QTimer::singleShot(2500, &eventloop, SLOT(quit()));
            eventloop.exec();
            send_message = "";
        }

    }


}


