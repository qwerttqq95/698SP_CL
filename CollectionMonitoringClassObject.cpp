//
// 采集监控类
//

#include "CollectionMonitoringClassObject.h"
#include "QAction"
#include "vector"


extern QString BuildMessage(QString apdu, const QString &SA, const QString &ctrl_zone);

extern QString time_deal(const QString &);

extern QString fre(const QString &);

extern QString re_rever_add();

extern QString run_style(const QString &);

extern QString mision_style(const QString &);

extern QString saved_time(const QString &);

CollectionMonitoringClass::CollectionMonitoringClass(QWidget *parent) : QDialog(parent),
                                                                        ui(new Ui::FormCOLLECTIONMONITORINGCLASSOBJECT) {
    ui->setupUi(this);
    this->setWindowTitle("采集监控");
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setAlternatingRowColors(true);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(sendmessage()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(clearlist()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(sendmessage()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(sendmessage()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(clearlist()));
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    for (int i = 0; i != ui->tableWidget->columnCount(); i++) {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);

    }
//    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void CollectionMonitoringClass::analysis6012(QList<QString> list6012) {
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    auto pos = list6012.begin();
    if (*pos == "01") {
        pos++;
        int rowcount = ui->tableWidget->rowCount();
        int const times = (*pos).toInt(nullptr, 16);
        for (int xx = 0; xx < times; xx++) {
            QApplication::processEvents();
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
                QApplication::processEvents();
            }
            ui->tableWidget->setItem(rowcount, 1, new QTableWidgetItem(fre(n.freq)));
            pos++;
            n.style = *pos;

            ui->tableWidget->setItem(rowcount, 2, new QTableWidgetItem(mision_style(n.style)));
            pos += 2;
            n.No = (*pos).toInt(nullptr, 16);
            ui->tableWidget->setItem(rowcount, 3, new QTableWidgetItem(QString::number(n.No)));
            pos++;
            n.start_time = "";
            for (int i = 0; i < 8; i++) {
                n.start_time.append(*pos);
                pos++;
                QApplication::processEvents();
            }

            ui->tableWidget->setItem(rowcount, 9, new QTableWidgetItem(time_deal(n.start_time)));
            n.end_time = "";
            for (int i = 0; i < 8; i++) {
                n.end_time.append(*pos);
                pos++;
                QApplication::processEvents();
            }
            ui->tableWidget->setItem(rowcount, 10, new QTableWidgetItem(time_deal(n.end_time)));
            pos++;
            n.delay = "";
            for (int i = 0; i < 3; i++) {
                n.delay.append(*pos);
                pos++;
                QApplication::processEvents();
            }
            ui->tableWidget->setItem(rowcount, 11, new QTableWidgetItem(fre(n.delay)));
            pos++;
            n.prio = *pos;
            ui->tableWidget->setItem(rowcount, 12, new QTableWidgetItem(n.prio));
            pos += 2;
            n.stat = *pos;
            if (n.stat == "01")
                ui->tableWidget->setItem(rowcount, 13, new QTableWidgetItem("启用"));
            else
                ui->tableWidget->setItem(rowcount, 13, new QTableWidgetItem("禁用"));
            pos += 10;
            n.run_style = *pos;
            ui->tableWidget->setItem(rowcount, 14, new QTableWidgetItem(run_style(n.run_style)));
            pos += 2;
            n.meter_times = "";
            std::vector<QString> meter_times;
            int timess = (*pos).toInt(nullptr, 16);
            for (int j = 0; j < timess; ++j) {
                for (int i = 0; i < 10; i++) {
                    pos++;
                    QApplication::processEvents();
                    meter_times.push_back(*pos);
                }
            }
            auto p = meter_times.begin() + 3;
            auto st_hour = QString::number((*p).toInt(nullptr, 16));
            auto st_min = QString::number((*(p + 2)).toInt(nullptr, 16));
            auto en_hour = QString::number((*(p + 4)).toInt(nullptr, 16));
            auto en_min = QString::number((*(p + 6)).toInt(nullptr, 16));
            ui->tableWidget->setItem(rowcount, 15, new QTableWidgetItem(
                    QString("%1:%2-%3:%4").arg(st_hour, st_min, en_hour, en_min)));//运行时段
            rowcount++;
            QApplication::processEvents();
        }
    }

    for (int j = 0; j < ui->tableWidget->rowCount(); ++j) {
        ui->tableWidget->item(j, 0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->item(j, 1)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->item(j, 3)->setTextAlignment(Qt::AlignCenter);
    }
}

void CollectionMonitoringClass::analysis6014(QList<QString> list6014) {
    auto pos = list6014.begin();
    if (*pos == "01") {
        pos++;
        int const times = (*pos).toInt(nullptr, 16);
        for (int xx = 0; xx < times; xx++) {
            QApplication::processEvents();
            pos += 4;
            analy_6014 n;
            n.No = (*pos).toInt(nullptr, 16);
            int ncount = -1;
            for (int l = 0; l < ui->tableWidget->rowCount(); ++l) {
                if (ui->tableWidget->item(l, 3)->text() == QString::number(n.No))
                    if (ui->tableWidget->item(l, 2)->text() != "事件采集方案")
                        ncount = l;
            }
            if (ncount == -1) {
                qDebug() << "match failed";
                return;
            }
            int deep = (*(pos + 2) + *(pos + 3)).toInt(nullptr,16);
            ui->tableWidget->setItem(ncount,16,new QTableWidgetItem(QString::number(deep)));
            pos += 7;
            switch ((*pos).toInt()) {
                case 0: {
                    pos += 3;
                    const int timess = (*pos).toInt(nullptr, 16);
                    qDebug() << "timess " << timess;
                    QString showtext("");
                    QString OAD("");
                    for (int i = 0; i < timess; i++) {
                        pos += 2;
                        if (*pos == "01") {
                            QString ROAD("");
                            for (int j = 0; j < 4; ++j) {
                                pos++;
                                ROAD.append(*pos);
                            }
                            showtext.append(ROAD + ":");
                            pos++;
                            int const timesss = (*pos).toInt(nullptr, 16);
                            QString OAD_list("");
                            for (int k = 0; k < timesss; ++k) {
                                for (int j = 0; j < 4; ++j) {
                                    pos++;
                                    OAD.append(*pos);
                                }
                                OAD_list.append("\n        " + OAD);
                            }
                            showtext.append(OAD_list);
                            ui->tableWidget->setItem(ncount, 4, new QTableWidgetItem("采集当前数据"));
                            ui->tableWidget->setItem(ncount, 5, new QTableWidgetItem(showtext));
                            ui->tableWidget->item(ncount, 5)->setToolTip(showtext);

                        } else {
                            for (int j = 0; j < 4; ++j) {
                                pos++;
                                OAD.append(*pos);
                            }
                            OAD.append('\n');
                        }
                        ui->tableWidget->setItem(ncount, 4, new QTableWidgetItem("采集当前数据"));
                        ui->tableWidget->setItem(ncount, 5, new QTableWidgetItem(OAD));
                        ui->tableWidget->item(ncount, 5)->setToolTip(OAD);
                    }
                }   // 采集当前数据
                    break;
                case 1: {
                    qDebug() << "上N次暂不支持";
                    return;
                }
                    break;
                case 2: {

                    pos += 3;
                    const int timess = (*pos).toInt(nullptr, 16);
                    QString showtext("");
                    for (int i = 0; i < timess; i++) {
                        pos += 2;
                        if (*pos == "01") {
                            QString ROAD("");
                            for (int j = 0; j < 4; ++j) {
                                pos++;
                                ROAD.append(*pos);
                            }
                            showtext.append(ROAD + ":");
                            pos++;
                            int const timesss = (*pos).toInt(nullptr, 16);
                            QString OAD_list("");
                            for (int k = 0; k < timesss; ++k) {
                                QString OAD("");
                                for (int j = 0; j < 4; ++j) {
                                    pos++;
                                    OAD.append(*pos);
                                }
                                OAD_list.append("\n        " + OAD);
                            }
                            showtext.append(OAD_list);
                            ui->tableWidget->setItem(ncount, 4, new QTableWidgetItem("按冻结时标采集"));
                            ui->tableWidget->setItem(ncount, 5, new QTableWidgetItem(showtext));
                            ui->tableWidget->item(ncount, 5)->setToolTip(showtext);
                            break;
                        }

                    }
                }   //冻结时标
                    break;
                case 3: {
                    pos += 2;
                    QString xx("");//时间
                    for (int i = 0; i < 3; ++i) {
                        xx.append(*pos);
                        pos++;
                    }
                    pos += 1;
                    const int timess = (*pos).toInt(nullptr, 16);
                    QString showtext("");
                    for (int i = 0; i < timess; i++) {
                        pos += 2;
                        if (*pos == "01") {
                            QString ROAD("");
                            for (int j = 0; j < 4; ++j) {
                                pos++;
                                ROAD.append(*pos);
                            }
                            showtext.append(ROAD + ":");
                            pos++;
                            int const timesss = (*pos).toInt(nullptr, 16);
                            QString OAD_list("");
                            for (int k = 0; k < timesss; ++k) {
                                QString OAD("");
                                for (int j = 0; j < 4; ++j) {
                                    pos++;
                                    OAD.append(*pos);
                                }
                                OAD_list.append("\n        " + OAD);
                            }
                            showtext.append(OAD_list);
                            ui->tableWidget->setItem(ncount, 4,
                                                     new QTableWidgetItem(QString("按时间(%1)间隔采集 ").arg(fre(xx))));
                            ui->tableWidget->setItem(ncount, 5, new QTableWidgetItem(showtext));
                            ui->tableWidget->item(ncount, 5)->setToolTip(showtext);

                            break;
                        }

                    }
                } //时标间隔
                    break;
                case 4: {
                    pos += 4;
                    QString date("");
                    for (int i = 0; i < 3; ++i) {
                        date.append(*pos);
                        pos++;
                    }
                    QString timess("");
                    for (int j = 0; j < 2; ++j) {
                        pos++;
                        timess.append(*pos);
                    }
                    int cishu = timess.toInt(nullptr, 16);
                    ui->tableWidget->setItem(ncount, 4,
                                             new QTableWidgetItem(QString("补抄上%1次 间隔:").arg(cishu) + fre(date)));
                    pos += 2;
                    const int timesxs = (*pos).toInt(nullptr, 16);
                    qDebug() << "timesxs: " << timesxs;
                    QString showtext("");
                    for (int i = 0; i < timesxs; i++) {
                        pos += 2;
                        if (*pos == "01") {
                            QString ROAD("");
                            for (int j = 0; j < 4; ++j) {
                                pos++;
                                ROAD.append(*pos);
                            }
                            showtext.append(ROAD + ":");
                            pos++;
                            int const timesss = (*pos).toInt(nullptr, 16);
                            QString OAD_list("");
                            for (int k = 0; k < timesss; ++k) {
                                QString OAD("");
                                for (int j = 0; j < 4; ++j) {
                                    pos++;
                                    OAD.append(*pos);
                                }
                                OAD_list.append("\n        " + OAD);
                            }
                            showtext.append(OAD_list);
                            ui->tableWidget->setItem(ncount, 5, new QTableWidgetItem(showtext));
                            ui->tableWidget->item(ncount, 5)->setToolTip(showtext);

                        }

                    }

                } //补抄
                    break;
            }
            pos += 2;
            qDebug() << "ncount :" << ncount;
            switch ((*pos).toInt()) {
                case 0: {
                    ui->tableWidget->setItem(ncount, 7, new QTableWidgetItem("无电表"));
                    pos += 2;
                    ui->tableWidget->setItem(ncount, 8, new QTableWidgetItem(saved_time(*pos)));
                }
                    break;
                case 1: {
                    ui->tableWidget->setItem(ncount, 7, new QTableWidgetItem("全部电表"));
                    pos += 2;
                    ui->tableWidget->setItem(ncount, 8, new QTableWidgetItem(saved_time(*pos)));
                }
                    break;
                case 2: {
                    pos++;
                    int len = (*pos).toInt(nullptr, 16);
                    QString mest("");
                    for (int i = 0; i < len; ++i) {
                        pos++;
                        mest.append(" " + QString::number((*pos).toInt(nullptr, 16)));

                    }
                    ui->tableWidget->setItem(ncount, 7, new QTableWidgetItem("一组用户类型:" + mest));
                    pos++;
                    pos++;
                    ui->tableWidget->setItem(ncount, 8, new QTableWidgetItem(saved_time(*pos)));
                }
                    break;
            }


        }
    }
}

void CollectionMonitoringClass::analysis601C(QList<QString> list601C) {
    qDebug() << "ana601C";
    auto pos = list601C.begin();
    if (*pos == "01") {
        pos++;
        int const times = (*pos).toInt(nullptr, 16);
        for (int xx = 0; xx < times; xx++) {
            QApplication::processEvents();
            analy_601C n;
            pos += 4;
            n.No = (*pos).toInt(nullptr, 16);
            qDebug() << "No: " << n.No;
            int ncount = -1;
            for (int l = 0; l < ui->tableWidget->rowCount(); ++l) {
                if (ui->tableWidget->item(l, 3)->text() == QString::number(n.No))

                    ncount = l;
            }
            if (ncount == -1) {
                qDebug() << "match failed";
                return;
            }
            pos += 2;
            int shangbaotongdaoshuliang = (*pos).toInt(nullptr, 16);
            qDebug() << "shangbaotongdaoshuliang " << shangbaotongdaoshuliang;
            QString tunle("");
            for (int i = 0; i < shangbaotongdaoshuliang; ++i) {
                pos += 1;
                for (int j = 0; j < 4; ++j) {
                    pos++;
                    tunle.append(*pos);
                }
                tunle.append(" ");
            }
            qDebug() << "tunle " << tunle;
            pos++;
            n.report_time = "";
            pos++;
            for (int k = 0; k < 3; ++k) {
                n.report_time.append(*pos);
                pos++;
            }
            qDebug() << "report_time " << n.report_time;
            pos++;
            n.report_times = *pos;
            pos += 4;
            qDebug() << "pos += 4; " << *pos;
            if (*pos == "00")//上报
            {
                pos++;
                QString OAD("");
                for (int i = 0; i < 4; ++i) {
                    pos++;
                    OAD.append(*pos);
                }
                ui->tableWidget->setItem(ncount, 6, new QTableWidgetItem(OAD));
                ui->tableWidget->item(ncount, 6)->setToolTip(OAD);

            } else {
                pos += 4;
                QString mainOAD("");
                for (int i = 0; i < 4; i++) {
                    mainOAD.append(*pos);
                    pos++;
                }
                qDebug() << "mainOAD " << mainOAD;
                pos++;
                QString secOAD("");
                int timess = (*pos).toInt(nullptr, 16);
                qDebug() << "timess" << timess;
                for (int j = 0; j < timess; ++j) {
                    pos++;
                    QString stat = *pos;
//                    qDebug() << "stat " << stat;
                    if (stat == "00") {//一般属性描述符
                        for (int i = 0; i < 4; ++i) {
                            pos++;
                            secOAD.append(*pos);
                        }
                        secOAD.append("\n");
                    } else {
                        QString ROAD("");
                        for (int i = 0; i < 4; ++i) {
                            pos++;
                            ROAD.append(*pos);
                        }
                        ROAD.append("\n");
                        qDebug() << "ROAD " << ROAD;
                        pos++;
                        int timesss = (*pos).toInt(nullptr, 16);
                        qDebug() << "timesss " << timesss;
                        QString content("       ");
                        pos++;
                        for (int k = 0; k < timesss; ++k) {
                            for (int i = 0; i < 4; ++i) {
                                content.append(*pos);
                                pos++;
                            }
                            content.append("\n       ");
                        }
                        qDebug() << "content " << content;
                        pos++;
                        ROAD.append(content);
                        secOAD.append(ROAD);
                    }
                }
                qDebug() << "secOAD " << secOAD;
                ui->tableWidget->setItem(ncount, 6, new QTableWidgetItem(secOAD));
                ui->tableWidget->item(ncount, 6)->setToolTip(secOAD);


                if ((*pos) == "00")
                    pos += 2;
                int RSDstyle = (*pos).toInt(nullptr, 16);
                qDebug() << "RSDstyle " << RSDstyle;
                switch (RSDstyle) {
                    default: {
                        qDebug() << "RSDstyle UKNOW!";
                        return;
                    }
                    case 6: {
                        QString str_time("");
                        for (int i = 0; i < 7; ++i) {
                            pos++;
                            str_time.append(*pos);
                        }
                        QString end_time("");
                        for (int i = 0; i < 7; ++i) {
                            pos++;
                            end_time.append(*pos);
                        }
                        QString time_gap("");
                        pos++;
                        for (int i = 0; i < 2; ++i) {
                            pos++;
                            time_gap.append(*pos);
                        }
                        pos++;
                    }
                        break;
                    case 7: {
                        QString str_time("");
                        for (int i = 0; i < 7; ++i) {
                            pos++;
                            str_time.append(*pos);
                        }
                        QString end_time("");
                        for (int i = 0; i < 7; ++i) {
                            pos++;
                            end_time.append(*pos);
                        }
                        QString time_gap("");
                        pos++;
                        for (int i = 0; i < 2; ++i) {
                            pos++;
                            time_gap.append(*pos);
                        }
                        pos++;
                    }
                        break;
                    case 8: {
                        QString str_time("");
                        for (int i = 0; i < 7; ++i) {
                            pos++;
                            str_time.append(*pos);
                        }
                        QString end_time("");
                        for (int i = 0; i < 7; ++i) {
                            pos++;
                            end_time.append(*pos);
                        }
                        QString time_gap("");
                        pos++;
                        for (int i = 0; i < 2; ++i) {
                            pos++;
                            time_gap.append(*pos);
                        }
                        pos++;
                    }
                        break;
                    case 10: {
                        pos++;
                        QString BeTime = *pos;
                        int preTimes = (*pos).toInt();//上N次
                        qDebug() << "preTimes " << preTimes;
                        pos++;
                    }
                        break;
                }


                QString MSstyle = *pos;
                qDebug() << "MSstyle " << MSstyle;
                switch (MSstyle.toInt()) {
                    default: {
                        qDebug() << "MSstyle UKNOW!";
                        return;
                    }
                    case 1: {

                    }
                        break;
                    case 2: {
                        pos++;
                        int len = (*pos).toInt(nullptr, 16);
                        qDebug() << "len " << len;
                        QString content("");
                        for (int l = 0; l < len; ++l) {
                            pos++;
                            int dec = (*pos).toInt(nullptr, 16);
                            content.append(QString::number(dec) + " ");
                        }
                        qDebug() << "content " << content;
                        ui->tableWidget->setItem(ncount, 7, new QTableWidgetItem("一组用户类型: " + content));
                    }
                        break;//一组用户类型
                }


            }


        }
    }
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

