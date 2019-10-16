#include "MeterArchives.h"
#include <ui_MeterArchives.h>
#include <thread>
#include <string>
#include <QMessageBox>
#include "QScrollBar"
#include <typeinfo.h>
#include <XMLFile/tinyxml2.h>
#include <stringapiset.h>


extern QString BuildMessage(QString apdu,  const QString& SA,  const QString& ctrl_zone);

extern VALUE_LEFT Data_deal(QList<QString> a);

extern QString re_rever_add();


char *UTF8ToUnicode(char *szUTF8)
{
    int wcscLen = ::MultiByteToWideChar(CP_UTF8, 0, szUTF8, strlen(szUTF8), NULL, 0);//得到所需空间的大小
    wchar_t *wszcString = new wchar_t[wcscLen + 1];//给'\0'分配空间
    ::MultiByteToWideChar(CP_UTF8, 0, szUTF8, strlen(szUTF8), wszcString, wcscLen);   //转换
    wszcString[wcscLen] = '\0';
    char *m_char;
    int len = WideCharToMultiByte(CP_ACP, 0, wszcString, wcslen(wszcString), NULL, 0, NULL, NULL);
    m_char = new char[len + 1];
    WideCharToMultiByte(CP_ACP, 0, wszcString, wcslen(wszcString), m_char, len, NULL, NULL);
    m_char[len] = '\0';
    return m_char;
}


MeterArchives::MeterArchives(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::myMeterArchives)
{
    ui->setupUi(this);
    addmeter = new AddMeters();
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(show_add()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(clearlist()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(Get_6000200()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(clearlist()));
    connect(ui->checkBox, SIGNAL(clicked()), this, SLOT(select_all_checkbox()), Qt::DirectConnection);
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(del()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(clear_6000200()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(send()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(output()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(input()));
    connect(addmeter, SIGNAL(send_list(QList<QString>)), this, SLOT(add_new(QList<QString>)));
    for (int i = 0; i != ui->tableWidget->columnCount(); i++)
    {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }

}

void MeterArchives::show_add()
{
    addmeter->show();
}

void MeterArchives::Get_6000200()
{
    QString add = re_rever_add();
    QString re_message = BuildMessage("0501006000020000", add, "43");
    emit send_write({re_message, "查询表档案"});
}

void MeterArchives::clear_6000200()
{
    QString add = re_rever_add();
    QString
            text = "070101600086000000";
    QString
            re_message = BuildMessage(text, add, "43");
    emit send_write({re_message, "清空表档案"});
}

void MeterArchives::clearlist()
{
    row_count = 0;
    for (int row = ui->tableWidget->rowCount(); row >= 0; --row)
    {
        ui->tableWidget->removeRow(row);
    }

}

void MeterArchives::add_new(QList<QString> a)
{
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

void MeterArchives::show_meter_message(QList<QString> a)
{
    Archives_Configuration_Table n;
    a.removeFirst();
    int times = (a.takeFirst()).toInt(nullptr, 16);
    if (times == 0)
    {
        QMessageBox::information(this, "Information", "无表档案", QMessageBox::Ok);
        return;
    }
    for (int i = 0; i < times; i++)
    {
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

void MeterArchives::all()
{
    if (ui->checkBox->checkState() == Qt::Checked)
    {
        for (int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            ui->tableWidget->item(i, 0)->setCheckState(Qt::CheckState::Checked);
        }
    } else
    {
        for (int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            ui->tableWidget->item(i, 0)->setCheckState(Qt::CheckState::Unchecked);
        }
    }
    QScrollBar *a = ui->tableWidget->horizontalScrollBar();
    a->setValue(1);

}


void MeterArchives::del()
{
    for (int i = ui->tableWidget->rowCount() - 1; i >= 0; i--)
    {
        if (ui->tableWidget->item(i, 0)->checkState() == Qt::Checked)
        {
            ui->tableWidget->removeRow(i);
            row_count -= 1;
        }
    }
}

void MeterArchives::select_all_checkbox()
{
    std::thread t1(&MeterArchives::all, this);
    t1.detach();
}

void MeterArchives::send()
{
    Archives_Configuration_Table n;
    int check_count = 0;
    QList<QString> text;
    QString
            message;
    for (int i = 0; i <= ui->tableWidget->rowCount() - 1; i++)
    {
        if (ui->tableWidget->item(i, 0)->checkState() == Qt::Checked)
        {
            check_count += 1;
            n.NUM = ui->tableWidget->item(i, 1)->text();
            char a[5];
            sprintf(a, "%04x", n.NUM.toInt(nullptr, 10));
            message = "020412" + (QString) a + "020a550705";
            qDebug() << "message 1:" << message;
            n.TSA = ui->tableWidget->item(i, 2)->text();
            message.append(n.TSA);
            qDebug() << "message 2 :" << message;
            n.baud_rate = ui->tableWidget->item(i, 3)->text();
            if (n.baud_rate.length() == 1)
            {
                n.baud_rate = "0" + n.baud_rate;
            }
            message.append("16" + n.baud_rate);
            qDebug() << "message 3:" << message;
            n.meter_style = ui->tableWidget->item(i, 4)->text();
            if (n.meter_style.length() == 1)
            {
                n.meter_style = "0" + n.meter_style;
            }
            message.append("16" + n.meter_style);
            qDebug() << "message 4:" << message;
            n.port = ui->tableWidget->item(i, 5)->text();
            qDebug() << "n.port :" << n.port;
            message.append("51" + n.port + "090100");
            qDebug() << "message 5:" << message;
            n.password = "090100";
            n.fee_count = ui->tableWidget->item(i, 7)->text();
            char b[3];
            sprintf(b, "%02x", n.fee_count.toInt(nullptr, 10));
            message.append("11" + (QString) b);
            qDebug() << "message 6:" << message;
            n.user_style = ui->tableWidget->item(i, 8)->text();
            char c[3];
            sprintf(c, "%02x", n.user_style.toInt(nullptr, 16));
            message.append("11" + (QString) c);
            qDebug() << "message 7:" << message;
            n.connect_way = ui->tableWidget->item(i, 9)->text();
            if (n.connect_way.length() == 1)
            {
                n.connect_way = "0" + n.connect_way;
            }
            message.append("16" + n.connect_way);
            qDebug() << "message 8:" << message;
            n.Rated_Voltage = ui->tableWidget->item(i, 10)->text();
            char d[5];
            sprintf(d, "%04x", n.Rated_Voltage.toInt(nullptr, 10));
            message.append("12" + (QString) d);
            qDebug() << "message 9:" << message;
            n.Rated_Electric_current = ui->tableWidget->item(i, 11)->text();
            char e[5];
            sprintf(e, "%04x", n.Rated_Voltage.toInt(nullptr, 10));
            message.append("12" + (QString) e + "0204");
            n.collect_TSA = ui->tableWidget->item(i, 12)->text();
            message.append("550705000000000000");
            qDebug() << "message 10:" << message;
            n.detail_num = ui->tableWidget->item(i, 13)->text();
            message.append("0900");

            n.PT = ui->tableWidget->item(i, 14)->text();
            char g[5];
            sprintf(g, "%04x", n.PT.toInt(nullptr, 10));
            message.append("12" + (QString) g);
            n.CT = ui->tableWidget->item(i, 15)->text();
            char j[5];
            sprintf(j, "%04x", n.CT.toInt(nullptr, 10));
            message.append("12" + (QString) j + "0100");
            text.append(message);
            qDebug() << "message 11:" << message;
        }
    }

    QString add = re_rever_add();
    if (text.length() == 1)
    {
        QString
                send_message = "07010060007f00" + text.takeFirst() + "00";
//        qDebug()<<"send_message"<<send_message;
        emit send_write({BuildMessage(send_message, add, "43"), ""});//2

    } else
    {
        int len = text.length();
        int j;
        QString
                send_message = "";
        while (len > 0)
        {
            for (j = 1; j < 15 and len > 0; j++, len--)
            {
                send_message = send_message + text.takeFirst();
            }
            char qw[3];
            sprintf(qw, "%02x", j - 1);
            send_message = "0701006000800001" + (QString) qw + send_message + "00";
            emit send_write({BuildMessage(send_message, add, "43"), ""});//2
            send_message = "";
            QEventLoop eventloop;
            QTimer::singleShot(3500, &eventloop, SLOT(quit()));
            eventloop.exec();
        }
        QMessageBox::information(this, "提示", "批量下发完成");
    }
}

void MeterArchives::output()
{
    QString
            filename = QFileDialog::getSaveFileName(this, tr("Save"), ".", tr(" (*.xls)"));
    YExcel::BasicExcel excelTermInfo;
    excelTermInfo.New();
    YExcel::BasicExcelWorksheet *pSheet = excelTermInfo.GetWorksheet((size_t) 0);
    YExcel::BasicExcelCell *pCell;
    int nItemNum = ui->tableWidget->rowCount();
    int nCol, nRow, i;
    nCol = 0;
    nRow = 0;
    pCell = pSheet->Cell(nRow, nCol++);
    pCell->SetWString(L"序号");
    pCell = pSheet->Cell(nRow, nCol++);
    pCell->SetWString(L"表地址");
    pCell = pSheet->Cell(nRow, nCol++);
    pCell->SetWString(L"波特率");
    pCell = pSheet->Cell(nRow, nCol++);
    pCell->SetWString(L"规约号");
    pCell = pSheet->Cell(nRow, nCol++);
    pCell->SetWString(L"端口号");
    pCell = pSheet->Cell(nRow, nCol++);
    pCell->SetWString(L"密码");
    pCell = pSheet->Cell(nRow, nCol++);
    pCell->SetWString(L"费率");
    pCell = pSheet->Cell(nRow, nCol++);
    pCell->SetWString(L"用户类型");
    pCell = pSheet->Cell(nRow, nCol++);
    pCell->SetWString(L"点表类型");
    pCell = pSheet->Cell(nRow, nCol++);
    pCell->SetWString(L"额定电压");
    pCell = pSheet->Cell(nRow, nCol++);
    pCell->SetWString(L"额定电流");
    pCell = pSheet->Cell(nRow, nCol++);
    pCell->SetWString(L"采集器地址");
    pCell = pSheet->Cell(nRow, nCol++);
    pCell->SetWString(L"资产号");
    pCell = pSheet->Cell(nRow, nCol++);
    pCell->SetString("PT");
    pCell = pSheet->Cell(static_cast<size_t>(nRow), nCol++);
    pCell->SetString("CT");
    nRow = 1;
    for (i = 0; i < ui->tableWidget->rowCount(); i++, nRow++)
    {
        nCol = 0;
        pCell = pSheet->Cell(nRow, nCol++);
        pCell->SetString(ui->tableWidget->item(i, nCol)->text().toStdString().c_str());
        pCell = pSheet->Cell(nRow, nCol++);
        pCell->SetString(ui->tableWidget->item(i, nCol)->text().toStdString().c_str());

        pCell = pSheet->Cell(nRow, nCol++);
        pCell->SetString(ui->tableWidget->item(i, nCol)->text().toStdString().c_str());

        pCell = pSheet->Cell(nRow, nCol++);
        pCell->SetString(ui->tableWidget->item(i, nCol)->text().toStdString().c_str());

        pCell = pSheet->Cell(nRow, nCol++);
        pCell->SetString(ui->tableWidget->item(i, nCol)->text().toStdString().c_str());

        pCell = pSheet->Cell(nRow, nCol++);
        pCell->SetString(ui->tableWidget->item(i, nCol)->text().toStdString().c_str());

        pCell = pSheet->Cell(nRow, nCol++);
        pCell->SetString(ui->tableWidget->item(i, nCol)->text().toStdString().c_str());

        pCell = pSheet->Cell(nRow, nCol++);
        pCell->SetString(ui->tableWidget->item(i, nCol)->text().toStdString().c_str());
        pCell = pSheet->Cell(nRow, nCol++);
        pCell->SetString(ui->tableWidget->item(i, nCol)->text().toStdString().c_str());

        pCell = pSheet->Cell(nRow, nCol++);
        pCell->SetString(ui->tableWidget->item(i, nCol)->text().toStdString().c_str());

        pCell = pSheet->Cell(nRow, nCol++);
        pCell->SetString(ui->tableWidget->item(i, nCol)->text().toStdString().c_str());

        pCell = pSheet->Cell(nRow, nCol++);
        pCell->SetString(ui->tableWidget->item(i, nCol)->text().toStdString().c_str());

        pCell = pSheet->Cell(nRow, nCol++);
        pCell->SetString(ui->tableWidget->item(i, nCol)->text().toStdString().c_str());

        pCell = pSheet->Cell(nRow, nCol++);
        pCell->SetString(ui->tableWidget->item(i, nCol)->text().toStdString().c_str());

        pCell = pSheet->Cell(nRow, nCol++);
        pCell->SetString(ui->tableWidget->item(i, nCol)->text().toStdString().c_str());
    }
    excelTermInfo.SaveAs(filename.toStdString().c_str());
}


void MeterArchives::input()
{
    QString
            filename = QFileDialog::getOpenFileName(nullptr, "open", ".", "*.xls");
    YExcel::BasicExcel excelTermInfo;
    const wchar_t *wstr = reinterpret_cast<const wchar_t *>(filename.utf16());
    if (!excelTermInfo.Load(wstr))
    {
        qDebug() << "dont know chinese? " << filename.toStdString().c_str();
        qDebug() << wstr;
        return;
    }
    clearlist();
    YExcel::BasicExcelWorksheet *pSheet = excelTermInfo.GetWorksheet((size_t) 0);
    YExcel::BasicExcelCell *pCell;

    int nMaxRows = pSheet->GetTotalRows();
    int nMaxCols = pSheet->GetTotalCols();
    int nCol, nRow;
    QString strTmp;
    for (nRow = 1; nRow < nMaxRows; nRow++)
    {
        QList<QString> li;
        auto *pArch = new Archives_Configuration_Table;
        nCol = 0;
        pCell = pSheet->Cell(nRow, nCol++);
        GetExcelValue(pCell, pArch->NUM);
        li.append(pArch->NUM);

        pCell = pSheet->Cell(nRow, nCol++);
        GetExcelValue(pCell, pArch->TSA);
        li.append(pArch->TSA);

        pCell = pSheet->Cell(nRow, nCol++);
        GetExcelValue(pCell, pArch->baud_rate);
        li.append(pArch->baud_rate);

        pCell = pSheet->Cell(nRow, nCol++);
        GetExcelValue(pCell, pArch->meter_style);
        li.append(pArch->meter_style);

        pCell = pSheet->Cell(nRow, nCol++);
        GetExcelValue(pCell, pArch->port);
        if (pArch->port.size() < 4)
        {
            int num = pArch->port.toInt();
            switch (num)
            {
                case 0:
                {
                    pArch->port = "F2080201";
                }
                    break;
                case 1:
                {
                    pArch->port = "F2010201";
                }
                    break;
                case 2:
                {
                    pArch->port = "F2010202";
                }
                    break;
                case 3:
                {
                    pArch->port = "F2090201";
                }
                    break;
                default:
                    pArch->port = "F2010201";

            }
        }

        li.append(pArch->port);

        pCell = pSheet->Cell(nRow, nCol++);
        GetExcelValue(pCell, pArch->password);
        li.append(pArch->password);

        pCell = pSheet->Cell(nRow, nCol++);
        GetExcelValue(pCell, pArch->fee_count);
        li.append(pArch->fee_count);

        pCell = pSheet->Cell(nRow, nCol++);
        GetExcelValue(pCell, pArch->user_style);
        li.append(pArch->user_style);

        pCell = pSheet->Cell(nRow, nCol++);
        GetExcelValue(pCell, pArch->connect_way);
        li.append(pArch->connect_way);

        pCell = pSheet->Cell(nRow, nCol++);
        GetExcelValue(pCell, pArch->Rated_Voltage);
        li.append(pArch->Rated_Voltage);

        pCell = pSheet->Cell(nRow, nCol++);
        GetExcelValue(pCell, pArch->Rated_Electric_current);
        li.append(pArch->Rated_Electric_current);

        pCell = pSheet->Cell(nRow, nCol++);
        GetExcelValue(pCell, pArch->collect_TSA);
        li.append(pArch->collect_TSA);

        pCell = pSheet->Cell(nRow, nCol++);
        GetExcelValue(pCell, pArch->detail_num);
        li.append(pArch->detail_num);

        pCell = pSheet->Cell(nRow, nCol++);
        GetExcelValue(pCell, pArch->PT);
        li.append(pArch->PT);

        pCell = pSheet->Cell(nRow, nCol++);
        GetExcelValue(pCell, pArch->CT);
        li.append(pArch->CT);

        add_new(li);
    }


}

bool MeterArchives::GetExcelValue(YExcel::BasicExcelCell *pCell, QString &str)
{
    QString strTemp;
    str = QString(pCell->GetString());
    str.replace(" ", "");
    if (str == "")
    {
        int num;
        num = pCell->GetInteger();
        str = QString::number(num, 10);
    }
    return true;
}




