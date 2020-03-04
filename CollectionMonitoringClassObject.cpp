//
// 采集监控类
//

#include "CollectionMonitoringClassObject.h"
#include "QAction"

extern QString BuildMessage(QString apdu, const QString &SA, const QString &ctrl_zone);

extern QString fre(const QString &);

extern QString re_rever_add();

CollectionMonitoringClass::CollectionMonitoringClass(QWidget *parent) : QDialog(parent),
                                                                        ui(new Ui::FormCOLLECTIONMONITORINGCLASSOBJECT) {
    ui->setupUi(this);
    this->setWindowTitle("采集监控");
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setAlternatingRowColors(true);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(sendmessage()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(sendmessage()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(sendmessage()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(clearlist()));
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    for (int i = 0; i != ui->tableWidget->columnCount(); i++) {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
}

void CollectionMonitoringClass::analysis6012(QList<QString> list6012) {
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    auto pos = list6012.begin();
    if (*pos == "01") {
        pos++;
        int rowcount = 0;
        qDebug() << "asd" << (*pos).toInt(nullptr, 16);
        int const times = (*pos).toInt(nullptr, 16);
        for (int xx = 0; xx < times; xx++) {
            analy_6012 n;
            pos += 4;
            n.ID = (*pos).toInt(nullptr, 16);
            ui->tableWidget->insertRow(rowcount);
            ui->tableWidget->setItem(rowcount, 0, new QTableWidgetItem(QString::number(n.ID)));
            n.freq = "";
            pos++;
            pos++;
            for (int i = 0; i < 3; i++) {
                n.freq.append(*pos);
                pos++;
            }
            ui->tableWidget->setItem(rowcount, 1, new QTableWidgetItem(fre(n.freq)));
            pos++;
            n.style = *pos;
            ui->tableWidget->setItem(rowcount, 2, new QTableWidgetItem(n.style));
            pos += 2;
            n.No = (*pos).toInt(nullptr, 16);
            ui->tableWidget->setItem(rowcount, 3, new QTableWidgetItem(QString::number(n.No)));
            pos++;
            n.start_time = "";
            for (int i = 0; i < 8; i++) {
                n.start_time.append(*pos);
                pos++;
            }

            ui->tableWidget->setItem(rowcount, 9, new QTableWidgetItem(n.start_time));
            n.end_time = "";
            for (int i = 0; i < 8; i++) {
                n.end_time.append(*pos);
                pos++;
            }
            ui->tableWidget->setItem(rowcount, 10, new QTableWidgetItem(n.end_time));
            pos++;
            n.delay = "";
            for (int i = 0; i < 3; i++) {
                n.delay.append(*pos);
                pos++;
            }
            ui->tableWidget->setItem(rowcount, 11, new QTableWidgetItem(fre(n.delay)));
            pos++;
            n.prio = *pos;
            ui->tableWidget->setItem(rowcount, 12, new QTableWidgetItem(n.prio));
            pos += 2;
            n.stat = *pos;
            ui->tableWidget->setItem(rowcount, 13, new QTableWidgetItem(n.stat));
            pos += 10;
            n.run_style = *pos;
            ui->tableWidget->setItem(rowcount, 14, new QTableWidgetItem(n.run_style));
            pos += 2;
            n.meter_times = "";
            for (int i = 0; i < 10; i++) {
                pos++;
                n.meter_times.append(*pos);
            }
            ui->tableWidget->setItem(rowcount, 15, new QTableWidgetItem(n.meter_times));
            rowcount++;
        }
    }

}

void CollectionMonitoringClass::analysis6014(QList<QString>) {
    qDebug() << "ana6014";
}

void CollectionMonitoringClass::analysis601C(QList<QString>) {
    qDebug() << "ana601C";
}

void CollectionMonitoringClass::sendmessage() {
    QAction *action = (QAction *) sender();
    QString add = re_rever_add();
    qDebug() << action->objectName();
    if (action->objectName() == "pushButton")
            emit send_message({BuildMessage("05010060120200", add, "43"), ""});
    else {
        if (action->objectName() == "pushButton_3")
                emit send_message({BuildMessage("05010060140200", add, "43"), ""});
        else
                emit send_message({BuildMessage("050100601c0200", add, "43"), ""});
    }
}

void CollectionMonitoringClass::clearlist() {
    for (int row = ui->tableWidget->rowCount(); row >= 0; --row) {
        ui->tableWidget->removeRow(row);
    }
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
}
