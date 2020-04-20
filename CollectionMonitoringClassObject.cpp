//
// 采集监控类
//

#include "CollectionMonitoringClassObject.h"
#include "QAction"
#include "vector"

#pragma execution_character_set("utf-8")

extern auto BuildMessage(const QString &apdu, const QString &SA, const QString &ctrl_zone) -> QString;

extern QString time_deal(const QString &);

extern QString fre(const QString &);

extern QString re_rever_add();

extern QString run_style(const QString &);

extern QString mision_style(const QString &);

extern QString saved_time(const QString &);

extern QString StringAddSpace(QString &input);

QString ReTimeHex(QString time) {
    auto date = time.split(" ");
    auto date_ = date[0].split("/");

    auto year = QString().sprintf("%04x", date_[0].toInt());
    auto mouth = QString().sprintf("%02x", date_[1].toInt());
    auto day = QString().sprintf("%02x", date_[2].toInt());

    auto time_ = date[1].split(":");

    auto hour = QString().sprintf("%02x", time_[0].toInt());
    auto min = QString().sprintf("%02x", time_[1].toInt());
    auto sec = QString().sprintf("%02x", time_[2].toInt());
    return year + mouth + day + hour + min + sec;
}

QString ReCollect(int x) {
    switch (x) {
        default: {
            qDebug() << "ERROR 46";
        }
        case 0: {

        }
            break;
        case 1:
            return "50020200";
        case 2:
            return "50040200";
        case 3:
            return "50060200";
    }

}

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
    Tab_2_init();
    ui->tabWidget->setCurrentIndex(0);
}

void CollectionMonitoringClass::analysis6012(QList<QString> list6012) {
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
            if (n.stat == "01") {
                ui->tableWidget->setItem(rowcount, 13, new QTableWidgetItem("启用"));
                ui->tableWidget->item(rowcount, 13)->setForeground(QBrush(QColor(0, 255, 0)));
            } else {
                ui->tableWidget->setItem(rowcount, 13, new QTableWidgetItem("禁用"));
                ui->tableWidget->item(rowcount, 13)->setForeground(QBrush(QColor(255, 0, 0)));
            }
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
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
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
            qDebug() << "mission ID " + QString::number(n.No);
            int ncount = -1;
            for (int l = 0; l < ui->tableWidget->rowCount(); ++l) {
                if (ui->tableWidget->item(l, 3)->text() == QString::number(n.No))
                    if (ui->tableWidget->item(l, 2)->text() != "事件采集方案") {
                        ncount = l;
                        QPushButton *read = new QPushButton();
                        read->setObjectName(QString::number(l));
                        read->setFixedSize(45, 30);
                        read->setText("读取");
                        ui->tableWidget->setCellWidget(l, 17, (QWidget *) read);
                        connect(read, SIGNAL(clicked()), this, SLOT(ClickedRead()));
                    }

            }
            if (ncount == -1) {
                qDebug() << "match failed";
                return;
            }
            int deep = (*(pos + 2) + *(pos + 3)).toInt(nullptr, 16);
            ui->tableWidget->setItem(ncount, 16, new QTableWidgetItem(QString::number(deep)));
            pos += 7;
            qDebug() << "pos += 7" << *(pos - 1) << (*pos) << *(pos + 1);
            switch ((*pos).toInt()) {
                default: {
                    qDebug() << "ERROR 215";
                    return;
                }
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
                    pos += 2;
                    ui->tableWidget->setItem(ncount, 4, new QTableWidgetItem(QString("采集上%1次").arg((*pos).toInt(nullptr,16))));
                    QString showtext("");
                    QString OAD("");
                    pos+=2;
                    const int timess = (*pos).toInt(nullptr, 16);
                    for (int i = 0; i < timess; i++) {
                        pos += 2;
                        if (*pos == "01") {
                            QString ROAD("");
                            for (int j = 0; j < 4; ++j) {
                                pos++;
                                ROAD.append(*pos);
                            }
                            showtext.append(ROAD + ":");
                            qDebug()<<"showtext"<<showtext;
                            pos++;
                            int const timesss = (*pos).toInt(nullptr, 16);
                            QString OAD_list("");
                            for (int k = 0; k < timesss; ++k) {
                                OAD="";
                                for (int j = 0; j < 4; ++j) {
                                    pos++;
                                    OAD.append(*pos);
                                }
                                OAD_list.append("\n        " + OAD);
                            }

                            showtext.append(OAD_list);
                            qDebug()<<"showtext"<<showtext;

                        } else {
                            for (int j = 0; j < 4; ++j) {
                                pos++;
                                OAD.append(*pos);
                            }
                            OAD.append('\n');
                        }

                    }
                    ui->tableWidget->setItem(ncount, 5, new QTableWidgetItem(showtext));
                    ui->tableWidget->item(ncount, 5)->setToolTip(showtext);
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
            qDebug() << "ncount :" << *(pos - 1) << (*pos) << *(pos + 1);
            switch ((*pos).toInt()) {
                default: {
                    qDebug() << "ERROR ON 3986";
                }
                    break;
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
                case 4: {
                    qDebug() << "一组配置序号";
                    pos++;
                    int len = (*pos).toInt(nullptr, 16);
                    QString mest("");
                    QString left;
                    QString right;
                    for (int i = 0; i < len; ++i) {
                        pos++;
                        left = *pos;
                        pos++;
                        right = *pos;
                        mest.append(" " + QString::number((left + right).toInt(nullptr, 16)));
                    }
                    ui->tableWidget->setItem(ncount, 7, new QTableWidgetItem("一组配置序号:" + mest));
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
                qDebug() << ui->tableWidget->item(l, 2)->text();
                if (ui->tableWidget->item(l, 3)->text() == QString::number(n.No) and
                    ui->tableWidget->item(l, 2)->text().contains("上报")) {
                    ncount = l;
                    break;
                }
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

//tab2
void CollectionMonitoringClass::Tab_2_init() {
    ui->dateTimeEdit->setDate(QDate::currentDate());
    ui->dateTimeEdit_2->setDate(QDate::currentDate());
    method_4();
    connect(ui->radioButton, SIGNAL(clicked()), this, SLOT(method_4()));
    connect(ui->radioButton_2, SIGNAL(clicked()), this, SLOT(method_5()));
    connect(ui->radioButton_4, SIGNAL(clicked()), this, SLOT(method_6()));
    connect(ui->radioButton_3, SIGNAL(clicked()), this, SLOT(method_7()));
    connect(ui->radioButton_6, SIGNAL(clicked()), this, SLOT(method_8()));
    connect(ui->radioButton_5, SIGNAL(clicked()), this, SLOT(method_9()));
    connect(ui->radioButton_7, SIGNAL(clicked()), this, SLOT(method_10()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(getData()));
}

void CollectionMonitoringClass::method_4() {
//采集启动时间
    ui->label->show();
    ui->dateTimeEdit->show();
    ui->label->setText("采集启动时间");
//采集结束时间
    ui->label_2->hide();
    ui->dateTimeEdit_2->hide();
//时间间隔
    ui->label_3->hide();
    ui->lineEdit->hide();
    ui->comboBox->hide();
//上N次
    ui->label_5->hide();
    ui->lineEdit_3->hide();
    //集合
    ui->label_4->show();
    ui->comboBox_2->show();
    ui->lineEdit_2->show();
}

void CollectionMonitoringClass::method_5() {
//采集启动时间
    ui->label->show();
    ui->label->setText("采集存储时间");
    ui->dateTimeEdit->show();
//采集结束时间
    ui->label_2->hide();
    ui->dateTimeEdit_2->hide();
//时间间隔
    ui->label_3->hide();
    ui->lineEdit->hide();
    ui->comboBox->hide();
//上N次
    ui->label_5->hide();
    ui->lineEdit_3->hide();
    //集合
    ui->label_4->show();
    ui->comboBox_2->show();
    ui->lineEdit_2->show();
}

void CollectionMonitoringClass::method_6() {
//采集启动时间
    ui->label->show();
    ui->label->setText("采集启动时间");
    ui->dateTimeEdit->show();
//采集结束时间
    ui->label_2->show();
    ui->label_2->setText("采集启动结束时间");
    ui->dateTimeEdit_2->show();
//时间间隔
    ui->label_3->show();
    ui->lineEdit->show();
    ui->comboBox->show();
//上N次
    ui->label_5->hide();
    ui->lineEdit_3->hide();
    //集合
    ui->label_4->show();
    ui->comboBox_2->show();
    ui->lineEdit_2->show();
}

void CollectionMonitoringClass::method_7() {
//采集启动时间
    ui->label->show();
    ui->label->setText("采集存储起始时间");
    ui->dateTimeEdit->show();
//采集结束时间
    ui->label_2->show();
    ui->label_2->setText("采集存储结束时间");
    ui->dateTimeEdit_2->show();
//时间间隔
    ui->label_3->show();
    ui->lineEdit->show();
    ui->comboBox->show();
//上N次
    ui->label_5->hide();
    ui->lineEdit_3->hide();
    //集合
    ui->label_4->show();
    ui->comboBox_2->show();
    ui->lineEdit_2->show();
}

void CollectionMonitoringClass::method_8() {
//采集启动时间
    ui->label->show();
    ui->label->setText("采集成功起始时间");
    ui->dateTimeEdit->show();
//采集结束时间
    ui->label_2->show();
    ui->label_2->setText("采集成功结束时间");
    ui->dateTimeEdit_2->show();
//时间间隔
    ui->label_3->show();
    ui->lineEdit->show();
    ui->comboBox->show();
//上N次
    ui->label_5->hide();
    ui->lineEdit_3->hide();
    //集合
    ui->label_4->show();
    ui->comboBox_2->show();
    ui->lineEdit_2->show();
}

void CollectionMonitoringClass::method_9() {
    ui->label->hide();
    ui->dateTimeEdit->hide();
//采集结束时间
    ui->label_2->hide();
    ui->dateTimeEdit_2->hide();
//时间间隔
    ui->label_3->hide();
    ui->lineEdit->hide();
    ui->comboBox->hide();
//上N次
    ui->label_5->show();
    ui->lineEdit_3->show();
//集合
    ui->label_4->hide();
    ui->comboBox_2->hide();
    ui->lineEdit_2->hide();
}

void CollectionMonitoringClass::method_10() {
//采集启动时间
    ui->label->hide();
    ui->dateTimeEdit->hide();
//采集结束时间
    ui->label_2->hide();
    ui->dateTimeEdit_2->hide();
//时间间隔
    ui->label_3->hide();
    ui->lineEdit->hide();
    ui->comboBox->hide();
//上N次
    ui->label_5->show();
    ui->lineEdit_3->show();
    //集合
    ui->label_4->show();
    ui->comboBox_2->show();
    ui->lineEdit_2->show();
}


void CollectionMonitoringClass::getData() {
    QString APDU = "05030060120300";
    if (ui->radioButton->isChecked() or ui->radioButton_2->isChecked()) {//方法4/5
        if (ui->radioButton->isChecked())
            APDU.append("04");
        else
            APDU.append("05");
        auto time = ui->dateTimeEdit->text();
        APDU.append(ReTimeHex(time));
    } else {
        if (ui->radioButton_4->isChecked() or ui->radioButton_3->isChecked() or ui->radioButton_6->isChecked()) {
            if (ui->radioButton_4->isChecked())
                APDU.append("06");
            if (ui->radioButton_3->isChecked())
                APDU.append("07");
            if (ui->radioButton_6->isChecked())
                APDU.append("08");
            auto time = ui->dateTimeEdit->text();
            auto time2 = ui->dateTimeEdit_2->text();
            APDU.append(ReTimeHex(time));
            APDU.append(ReTimeHex(time2));
            APDU.append(QString().sprintf("%02d", ui->comboBox->currentIndex()) +
                        QString().sprintf("%04x", ui->lineEdit->text().toInt()));
        } else {
            if (ui->radioButton_5->isChecked()) {//9
                APDU.append("09" + QString().sprintf("%02x", ui->lineEdit_3->text().toInt()));
            } else {//10
                APDU.append("0a" + QString().sprintf("%02x", ui->lineEdit_3->text().toInt()));
            }
        }
    }

    switch (ui->comboBox_2->currentIndex()) {  //MS
        case 0: {
            qDebug() << "ERROR 878";
            return;
        }
        case 1: {//全部用户地址
            APDU.append("01");
        }
            break;
        case 2: {//用户类型
            APDU.append("02");
            auto meter = ui->lineEdit_2->text();
            meter.append(",");
            auto meter_sp = meter.split(",", QString::SkipEmptyParts);
            auto count = QString().sprintf("%02x", meter_sp.count());
            APDU.append(count);
            for (int i = 0; i < meter_sp.count(); ++i) {
                APDU.append(QString().sprintf("%02x", meter_sp[i].toInt()));
            }
        }
            break;
        case 3: {//用户地址
            APDU.append("03");
            auto meter = ui->lineEdit_2->text();
            meter.append(",");
            auto meter_sp = meter.split(",", QString::SkipEmptyParts);
            auto count = QString().sprintf("%02x", meter_sp.count());
            APDU.append(count);
            for (int i = 0; i < meter_sp.count(); ++i) {
                auto x = StringAddSpace(meter_sp[i]).split(" ");
                for (int j = 0; j < x.length() / 2; ++j) {
                    auto c = x[j];
                    x[j] = x[x.length() - 1 - j];
                    x[x.length() - 1 - j] = c;
                }
                QString text("");
                for (int k = 0; k < x.length(); ++k) {
                    text.append(x[k]);
                }
                APDU.append("0705" + text);
            }
        }
            break;
        case 4: {//用户序号
            APDU.append("04");
            auto meter = ui->lineEdit_2->text();
            meter.append(",");
            auto meter_sp = meter.split(",", QString::SkipEmptyParts);
            auto count = QString().sprintf("%02x", meter_sp.count());
            APDU.append(count);
            for (int i = 0; i < meter_sp.count(); ++i) {
                APDU.append(QString().sprintf("%04x", meter_sp[i].toInt()));
            }
        }


    }

    switch (ui->comboBox_3->currentIndex()) {  //采集类型
        default: {
            qDebug() << "ERROR 935";
            return;
        }
        case 0: { //实时
            auto OAD = ui->comboBox_4->currentText().split(",", QString::SkipEmptyParts);
            auto count = QString().sprintf("%02x", OAD.length());
            APDU.append(count);
            for (int i = 0; i < OAD.length(); ++i) {
                APDU.append("00" + OAD[i]);
            }
            APDU.append("00");
        }
            break;
        case 1: { //曲线
            auto OAD = ui->comboBox_4->currentText().split(",", QString::SkipEmptyParts);
            auto count = QString().sprintf("%02x", OAD.length());
            APDU.append("020150020200");
            APDU.append(count);
            for (int i = 0; i < OAD.length(); ++i) {
                APDU.append(OAD[i]);
            }
            APDU.append("00202a020000");
        }
            break;
        case 2: { //日冻结
            auto OAD = ui->comboBox_4->currentText().split(",", QString::SkipEmptyParts);
            auto count = QString().sprintf("%02x", OAD.length());
            APDU.append("020150040200");
            APDU.append(count);
            for (int i = 0; i < OAD.length(); ++i) {
                APDU.append(OAD[i]);
            }
            APDU.append("00202a020000");
        }
            break;

        case 3: { //月冻结
            auto OAD = ui->comboBox_4->currentText().split(",", QString::SkipEmptyParts);
            auto count = QString().sprintf("%02x", OAD.length());
            APDU.append("020150060200");
            APDU.append(count);
            for (int i = 0; i < OAD.length(); ++i) {
                APDU.append(OAD[i]);
            }
            APDU.append("00202a020000");
        }
            break;
    }
    qDebug() << "APDU:" << APDU;
    if (APDU == "")
        return;
    emit send_message({BuildMessage(APDU, re_rever_add(), "43"), ""});
}


void CollectionMonitoringClass::ClickedRead() {
    auto *rec = (QAction *) sender();
    QString CSD_data = ui->tableWidget->item(rec->objectName().toInt(), 5)->text();
    QStringList sp, OAD;
    if (ui->tableWidget->item(rec->objectName().toInt(), 4)->text() == "采集当前数据") {
        ui->comboBox_3->setCurrentIndex(0);
        OAD = CSD_data.split("\n", QString::SkipEmptyParts);
        qDebug() << OAD[0];
    } else {
        sp = CSD_data.split(":");
        qDebug() << sp[0] << " " << sp[1];
        if (sp[0] == "50040200") {
            ui->comboBox_3->setCurrentIndex(2);
        } else {
            if (sp[0] == "50020200") {
                ui->comboBox_3->setCurrentIndex(1);
            } else {
                ui->comboBox_3->setCurrentIndex(3);
            }
        }
        OAD = sp[1].split("\n        ", QString::SkipEmptyParts);
    }
    QString OAD_TEXT;
    for (int i = 0; i < OAD.count(); ++i) {
        OAD_TEXT.append(OAD[i] + ",");
    }
    ui->comboBox_4->insertItem(0, OAD_TEXT);
    ui->comboBox_4->setCurrentIndex(0);

    ui->tabWidget->setCurrentIndex(1);
}
