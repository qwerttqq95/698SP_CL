#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <MeterArchives.h>
#include <iostream>
#include <QScrollBar>
#include <QtWidgets/QInputDialog>
#include "XMLFile/tinyxml2.h"
#include <QSize>
#include <QEvent>
#include <QKeyEvent>
#include <QApplication>
#include <QClipboard>


using namespace std;

extern QString BuildMessage(QString apdu, const QString &SA, const QString &ctrl_zone);

extern QString StringAddSpace(QString &input);

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new Serial();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->tableWidget->setToolTipDuration(50);
    setWindowTitle("698SP v1.4.0");

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("Database.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }

    connect(ui->actionA, SIGNAL(triggered()), this, SLOT(about())); //关于
    connect(ui->actionSd, SIGNAL(triggered()), this, SLOT(serial_config())); //打开参数设置
    connect(ui->actionAPDUzu, SIGNAL(triggered()), this, SLOT(custom()));
    connect(ui->action, SIGNAL(triggered()), this, SLOT(send_find_add()));//广播读地址
    connect(serial, SIGNAL(send_message(QList<QString>)), this, SLOT(show_message_send(QList<QString>)));
    connect(serial, SIGNAL(receive_message(QString)), this, SLOT(show_message_receive(QString)));
    connect(ui->actionbiaodangan, SIGNAL(triggered()), this, SLOT(open_MeterArchives()));
    connect(ui->actionSdf, SIGNAL(triggered()), this, SLOT(custom_test()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(clear_view()));
    connect(ui->actionC, SIGNAL(triggered()), this, SLOT(op_analy()));
    setWindowState(Qt::WindowMaximized);
    QAction *attach4520;
    attach4520 = new QAction();
    attach4520->setObjectName(QStringLiteral("Build_4520"));
    attach4520->setText("Build_4520");
    ui->menu_4->addAction(attach4520);
    connect(attach4520, SIGNAL(triggered()), this, SLOT(open_attach()));


    Custom = new Custom_APDU();
    Custom_point = ui->mdiArea->addSubWindow(Custom, Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    connect(Custom, SIGNAL(send_write(QList<QString>)), serial, SLOT(write(QList<QString>)), Qt::UniqueConnection);


    MeterArchive = new MeterArchives();
    MeterArchive_point = ui->mdiArea->addSubWindow(MeterArchive,
                                                   Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    connect(MeterArchive, SIGNAL(send_write(QList<QString>)), serial, SLOT(write(QList<QString>)),
            Qt::UniqueConnection);
    connect(this, SIGNAL(deal_with_meter(QList<QString>)), MeterArchive, SLOT(
            show_meter_message(QList<QString>)));


    Parametric_variable = new _4_Parametric_variable();
    Parametric_variable_point = ui->mdiArea->addSubWindow(Parametric_variable,Qt::WindowMinimizeButtonHint);
    Parametric_variable_point->widget()->showMaximized();
    connect(Parametric_variable, SIGNAL(send_write(QList<QString>)), serial, SLOT(write(QList<QString>)), Qt::UniqueConnection);

    CollectionMonitoring = new CollectionMonitoringClass();
    CollectionMonitoring_point = ui->mdiArea->addSubWindow(CollectionMonitoring,Qt::WindowMinimizeButtonHint);
    CollectionMonitoring_point->widget()->showMaximized();

    QList<QMdiSubWindow *> p = ui->mdiArea->subWindowList();
    for (auto &j : p)
    {
        j->widget()->showMaximized();
    }


    QAction *shijian_init;
    shijian_init = new QAction();
    shijian_init->setObjectName(QStringLiteral("shijian_init"));
    shijian_init->setText("事件初始化");
    ui->menu_5->addAction(shijian_init);

    QList<QAction *> act = ui->menu_10->actions();
    for (int i = 0, b = act.size(); i < b; i++)
    {
        connect(act.takeFirst(), SIGNAL(triggered()), this, SLOT(function()));
    }
    QList<QAction *> act2 = ui->menu_11->actions();
    for (int i = 0, b = act2.size(); i < b; i++)
    {
        connect(act2.takeFirst(), SIGNAL(triggered()), this, SLOT(function()));
    }
    QList<QAction *> act5 = ui->menu_5->actions();
    for (int i = 0, b = act5.size(); i < b; i++)
    {
        connect(act5.takeFirst(), SIGNAL(triggered()), this, SLOT(function()));
    }
    QList<QAction *> act8 = ui->menu_8->actions();
    for (int i = 0, b = act8.size(); i < b; i++)
    {
        connect(act8.takeFirst(), SIGNAL(triggered()), this, SLOT(function()));
    }
    serial->show();
    Communication_parameters();
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(add_change_event(QString)));
    connect(ui->tableWidget, SIGNAL(doubleClicked(
                                            const QModelIndex)), this, SLOT(double_click_analysis(
                                                                                    const QModelIndex)));
    connect(ui->tableWidget, SIGNAL(itemSelectionChanged()), this, SLOT(copy_message()));
}

void MainWindow::function()
{
    QAction *f_action = (QAction *) sender();
    ifstream in;
    in.open(".\\Data\\Default", ios::in);
    string temp;
    while (getline(in, temp))
    {
        QString temp2 = QString::fromStdString(temp);
        if (temp2 == f_action->text())
        {
            while (getline(in, temp))
            {
                if (QString::fromStdString(temp) == "")
                {
                    break;
                }
                temp2 = QString::fromStdString(temp);
                qDebug() << temp2;
                QList<QString> temp_list = temp2.split("#");
                serial->send_write({BuildMessage(temp_list[1], revert_add, "43"), temp_list[0]});
                QEventLoop
                        eventloop;
                QTimer::singleShot(1500, &eventloop, SLOT(quit()));
                eventloop.exec();
            }
            break;
        }

    }
    in.close();

}

void MainWindow::custom_test()
{
    check = new Check();
    connect(check, SIGNAL(send_message(QList<QString>)), serial, SLOT(write(QList<QString>)));
    connect(check, SIGNAL(compare_signal(QString)), this, SLOT(compare(QString)));
    check->show();
}

void MainWindow::move_Cursor()
{
    ui->tableWidget->scrollToBottom();
}

void MainWindow::open_MeterArchives()
{
    ui->mdiArea->setActiveSubWindow(MeterArchive_point);
    QMdiSubWindow *p = ui->mdiArea->activeSubWindow();
    p->widget()->showMaximized();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    serial->close();
    close();
}

QString MainWindow::analysis(QString a)
{
    QStringList list = a.split(' ', QString::SkipEmptyParts);
    while (true)
    {
        if (list.size() < 10)
            return "";
        if (list[0] == "68")
            break;
        else
            list.removeFirst();
    }
//    int message_len = (list[2] + list[1]).toInt(nullptr, 16);  //报文长度
//    int ctrl_zone = list[3].toInt(nullptr, 16); //控制域
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
    tinyxml2::XMLDocument doc;
    doc.LoadFile("config.xml");
    tinyxml2::XMLElement *root = doc.RootElement();
    tinyxml2::XMLElement *first_child1 = root->FirstChildElement("add");
    const char *content2 = add.toLocal8Bit();
    first_child1->SetText(content2);

    tinyxml2::XMLElement *first_child = root->FirstChildElement("revert_add");
    const char *content = revert_add.toLocal8Bit();
    first_child->SetText(content);
    doc.SaveFile("config.xml");
    int apdu_0 = 9 + SA_len;
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
            QString
                    y = year;
            sprintf(year, "%04X", y.toInt(nullptr, 10));
            char tmp[30];
            strftime(tmp, sizeof(tmp), "%m %d 0%w %H %M %S 00 00", localtime(&timep));
            QString
                    mouth_to_s = tmp;
            QString
                    date_times = "";
            QList<QString> date_time;
            date_time = mouth_to_s.split(' ');
            for (int i = 0; i < date_time.length(); i++)
            {
                char temp[3];
                sprintf(temp, "%02X", date_time[i].toInt(nullptr, 10));
                date_times = date_times + temp;
            }
            QString
                    APDU = "81" + n.PIIDACD + "80" + n.REQUEST_TIMEDATE_TIME + year + date_times + year + date_times;
            if (n.LINK_REQUSET_TYPE == "00")
            {
                emit
                serial->send_write({BuildMessage(APDU, revert_add, "01"), "登录响应"});
                return "登录";
            } else
            {
                emit
                serial->send_write({BuildMessage(APDU, revert_add, "01"), "心跳响应"});
                return "心跳";
            }


        }

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
                        qDebug() << "收到表档案信息: " << n.DATA;
                        emit deal_with_meter(n.DATA);
                    }

//                    emit send_analysis(n.OAD + " : " + deal_data(n.DATA));//解析
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
                        QString
                                text = "0505" + n.PIIDACD + n.slicing_index + "00";
                        emit
                        serial->send_write({BuildMessage(text, revert_add, "43"), ""});
                        times++;
                        return QString().sprintf("收到分帧,第%d帧", times);
                    }
                    if (n.is_last_frame == "01")
                    {
                        times = 0;
                        return "最后一帧";
                    }
                }
                    break;
                default:
                    qDebug() << "850?";
                    break;
            }
        }
            break;
        case 0x86:
        {
            switch (list[apdu_0 + 1].toInt(nullptr, 16))
            {
                case 0x1:
                {
                    return DARType(list[apdu_0 + 7].toInt(nullptr, 16));
                }
            }
        }
        case 0x87:
        {
            switch (list[apdu_0 + 1].toInt(nullptr, 16))
            {
                case 0x1:
                {
                    return DARType(list[apdu_0 + 7].toInt(nullptr, 16));
                }
            }
        }
            break;
        case 0x88:
        {
            switch (list[apdu_0 + 1].toInt(nullptr, 16))
            {
                case 0x1:
                { //未处理完
                    ReportNotificationList n;
                    n.PIIDACD = list[apdu_0 + 2];
                    n.SequenceOfLen = list[apdu_0 + 3];
                    n.OAD = "";
                    for (int i = 1; i < 5; i++)
                    {
                        n.OAD = n.OAD + list[apdu_0 + 3 + i];
                    }
                    QString APDU = "0801" + n.PIIDACD + n.SequenceOfLen + n.OAD + "00";
                    if (!ui->actionshangbao->isChecked())
                    {
                        serial->send_write({BuildMessage(APDU, revert_add, "03"), "8801上报响应"});
                        n.GetResultType = list[apdu_0 + 8];
                    }
                    return "上报消息";
                }
                case 0x2: //未处理完
                {
                    ReportNotificationRecordList n;
                    n.PIIDACD = list[apdu_0 + 2];
                    n.SequenceOfLen = list[apdu_0 + 3];
                    n.OAD = "";
                    for (int i = 1; i < 5; i++)
                    {
                        n.OAD = n.OAD + list[apdu_0 + 3 + i];
                    }
                    QString APDU = "0802" + n.PIIDACD + n.SequenceOfLen + n.OAD + "00";
                    if (!ui->actionshangbao->isChecked())
                    {
                        serial->send_write({BuildMessage(APDU, revert_add, "03"), "8802上报响应"});
                        n.RCSD = list[apdu_0 + 8];
                    }
                    return "上报消息";

                }
                default:
                    qDebug() << "880?";
                    break;
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
            QString
                    text = "";
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
    QString
            add = "6817004345AAAAAAAAAAAA10DA5F0501034001020000900f16";
    emit
    serial->send_write({add, "读地址"});                   ////发送
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::about()
{
    QMessageBox::information(this, "关于", "698SP CLION V1.4 \n QT版本: 5.11.3", QMessageBox::Ok);
}

void MainWindow::serial_config()
{
    serial->show();
}


void MainWindow::custom()
{
    ui->mdiArea->setActiveSubWindow(Custom_point);
    QMdiSubWindow *p = ui->mdiArea->activeSubWindow();
    p->widget()->showMaximized();
}

void MainWindow::show_message_send(QList<QString> a)
{
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%H:%M:%S", localtime(&timep));
    QString
            x = tmp;
    ui->tableWidget->insertRow(current);
    ui->tableWidget->setItem(current, 0, new QTableWidgetItem("发送:"));
    ui->tableWidget->setItem(current, 1, new QTableWidgetItem(StringAddSpace(a[0])));
    ui->tableWidget->setItem(current, 2, new QTableWidgetItem(a[1].replace("\n", "")));
    ui->tableWidget->setItem(current, 3, new QTableWidgetItem(x));
//    ui->tableWidget->item(current, 1)->setToolTip(StringAddSpace(a[0]));
//    ui->tableWidget->item(current, 2)->setToolTip((a[1]));
    if (a[1].contains("心跳") or a[1].contains("登录"))
    {
        ui->tableWidget->item(current, 2)->setForeground(QBrush(QColor(0,139,139)));
    }else
    if (a[1].contains("上报")){
        ui->tableWidget->item(current, 2)->setForeground(QBrush(QColor(205,92,92)));

    }
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
    if (te.contains("心跳") or te.contains("登录"))
    {
        ui->tableWidget->item(current, 2)->setForeground(QBrush(QColor(0,139,139)));
    } else
        if (te.contains("上报")){
            ui->tableWidget->item(current, 2)->setForeground(QBrush(QColor(205,92,92)));
        }

    current += 1;
    move_Cursor();

}

void MainWindow::Communication_parameters()
{
    QMenu *menu_comm;
    menu_comm = new QMenu(ui->menu_12);
    ui->menu_12->addAction(menu_comm->menuAction());
    menu_comm->setObjectName(QStringLiteral("menu_comm"));
    menu_comm->setEnabled(true);
    menu_comm->setTitle("通信参数");

    QAction *wrieless_station_ip;
    wrieless_station_ip = new QAction();
    wrieless_station_ip->setObjectName(QStringLiteral("wrieless_station_ip"));
    wrieless_station_ip->setText("设置无线公网主站IP");
    menu_comm->addAction(wrieless_station_ip);
    connect(wrieless_station_ip, SIGNAL(triggered()), this, SLOT(set_ip()));

    QAction *eth_station_ip;
    eth_station_ip = new QAction();
    eth_station_ip->setObjectName(QStringLiteral("eth_station_ip"));
    eth_station_ip->setText("设置以太网主站IP");
    menu_comm->addAction(eth_station_ip);
    connect(eth_station_ip, SIGNAL(triggered()), this, SLOT(set_ip()));
}

void MainWindow::set_ip()
{
    QAction *f_action = (QAction *) sender();
    tinyxml2::XMLDocument doc;
    doc.LoadFile("config.xml");
    tinyxml2::XMLElement *root = doc.RootElement();
    tinyxml2::XMLElement *first_child = root->FirstChildElement("Eth");
    tinyxml2::XMLElement *child_child = first_child->FirstChildElement();
    const char *content;
    content = child_child->GetText();
    QString item_text;
    item_text = (QString) content;
    QStringList item_text_list = item_text.split(';', QString::SkipEmptyParts);
    bool ok;
    QString text = QInputDialog::getItem(this, f_action->text(), "主站IP:", item_text_list, 0, true, &ok);
    if (ok && !item_text_list.isEmpty())
    {
        int index = item_text_list.indexOf(text);
        if (index == -1)
        {
            qDebug() << "-1";
            item_text_list.insert(0, text);
        } else if (index > 0)
            item_text_list.insert(0, item_text_list.takeAt(index));
        if (item_text_list.length() > 10)
            item_text_list.removeLast();
        QString new_string = item_text_list.join(";");
        QByteArray sr = new_string.toLocal8Bit();
        int len = sr.length();
        char *buf = new char[len + 2];
        buf[len] = buf[len + 1] = 0;
        strcpy(buf, sr.data());
        cout << buf;
        child_child->SetText(buf);
        QStringList list1 = text.split(':', QString::SkipEmptyParts);
        QStringList list2 = list1[0].split('.', QString::SkipEmptyParts);
        if (list2.size() != 4)
            QMessageBox::warning(this, "Warming", "IP格式错误");
        QString text_ip = "";
        for (int i = 0; i < 4; i++)
        {
            char temp[3];
            sprintf(temp, "%02X", list2[i].toInt());
            text_ip = text_ip + temp;
        }
        char temp2[5];
        sprintf(temp2, "%02X", list1[1].toInt());
        QString message;
        if (f_action->text().contains(tr("无线")))
            message = "06010045000300010102020904" + text_ip + "12" + temp2;
        else
            message = "06010045100300010102020904" + text_ip + "12" + temp2;
        qDebug() << "message: " << message << f_action->text();
        serial->send_write({BuildMessage(message, revert_add, "43"), f_action->text()});
        doc.SaveFile("config.xml");
    }

}

void MainWindow::compare(QString recive)
{
    QString last_message = ui->tableWidget->item(current - 1, 1)->text().replace(" ", "");
    show_message_receive("比对: " + recive);
    if (last_message.contains(recive.replace(" ", "")))
    {
        show_message_receive("比对结果一致");
    } else
        show_message_receive("比对结果不一致");
}

void MainWindow::open_attach()
{
    QAction *f_action = (QAction *) sender();
//    qDebug() << "path" << f_action->text();
    QString current_path = QDir::currentPath().replace("/", "\\");
    QString path = current_path + "\\attach\\" + f_action->text();
    QString runPath = current_path + "\\attach";
//    qDebug() << "path" << path;
//    qDebug() << "runPath" << runPath;
    QProcess *process = new QProcess;
    process->setWorkingDirectory(runPath);
    process->start("\"" + path + "\"");

}

void MainWindow::clear_view()
{
    while (current--)
        ui->tableWidget->removeRow(0);
    current += 1;
}

void MainWindow::add_change_event(QString a)
{
    if (a.size() == 12)
    {
        tinyxml2::XMLDocument doc;
        doc.LoadFile("config.xml");
        tinyxml2::XMLElement *root = doc.RootElement();
        tinyxml2::XMLElement *first_child1 = root->FirstChildElement("add");
        const char *content2 = a.toLocal8Bit();
        first_child1->SetText(content2);

        a = StringAddSpace(a);
        QString re_add = "";
        QList<QString> b = a.split(" ", QString::SplitBehavior::SkipEmptyParts);
        for (int i = 0; i < b.size(); i++)
        {
            re_add = b[i] + re_add;
        }
        tinyxml2::XMLElement *first_child2 = root->FirstChildElement("revert_add");
//        qDebug() << "a.size()" << re_add;
        const char *content3 = re_add.toLocal8Bit();
        first_child2->SetText(content3);
        doc.SaveFile("config.xml");
    }
}

void MainWindow::double_click_analysis(const QModelIndex &index)
{
//    if (QMouseEvent->button() == Qt::LeftButton)
    {
        auto m = index.row();
        auto message = index.sibling(m, 1).data().toString();
        analy = new Analysis(message);
        analy->show();
    }
}

void MainWindow::op_analy()
{
    analy = new Analysis();
    analy->show();
}

void MainWindow::copy_message()
{
    QList<QTableWidgetItem *> message_list = ui->tableWidget->selectedItems();
    QString copy_board = "";
            foreach(QTableWidgetItem *item, message_list)
        {
            copy_board.append(item->text() + '\n');
        }
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(copy_board);
}


QString MainWindow::DARType(int a)
{
    QSqlQuery sql_query;
    sql_query.exec("select * from dar where Number= " + QString::number(a));
    if (!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    } else
    {
        sql_query.next();
        QString detail = sql_query.value(0).toString();
        qDebug() << QString("detail:%1").arg(detail);
        return detail;
    }
}