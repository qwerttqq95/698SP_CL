#include "MessageCompose.h"
#include "ui_UI_MessageCompose.h"
#include "QMessageBox"
#include "io.h"
#include <string>
#include <fstream>
//#include "iostream"

using namespace std;

extern void getDir(std::string path, std::vector<std::string> &files);

MessageCompose::MessageCompose(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::MESSAGECOMPOSEForm)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(inset_line()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(delLine()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(done_save()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(add_line()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(add_delay()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(para_init()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(data_init()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(compare()));
    save_place();

}

void MessageCompose::open_exist(QString a)
{
    clear();
    show();
    QByteArray cdata = a.toLocal8Bit();
    std::ifstream file;
    file.open(std::string(cdata), std::ios::in);
    if (!file)
    {
        qDebug() << "error";
    } else
    {
        char c;
        int lineCnt = 0;
        while (file.get(c))
        {
            if (c == '\n')
                lineCnt++;
        }
        file.clear();
        file.seekg(0, std::ios::beg);
        std::string a;
        qDebug() << "a" << lineCnt;
        int line = 0;
        QList<QString> b;
        while (lineCnt)
        {

            std::getline(file, a);
            if (a.empty())
            {
                qDebug() << "kong";
                break;
            } else
            {
                b = QString::fromStdString(a).split("#");
                ui->tableWidget->insertRow(line);
                ui->tableWidget->setItem(line, 0, new QTableWidgetItem(b[0]));
                ui->tableWidget->setItem(line, 1, new QTableWidgetItem(b[1]));
            }
            line += 1;
            lineCnt--;
        }
        file.close();
    }
}

void MessageCompose::add_line()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}

void MessageCompose::inset_line()
{
    int rowCount = ui->tableWidget->currentRow();
    if (rowCount < 0)
        rowCount = 0;
    ui->tableWidget->insertRow(rowCount);
}

void MessageCompose::delLine()
{
    int posite = ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(posite);
}

void MessageCompose::add_delay()
{
    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount);
    ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(" 延时(s)"));
    ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(" 60"));
}

void MessageCompose::data_init()
{
    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount);
    ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem("数据初始化"));
    ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem("07 01 0a 43 00 03 00 00 00"));
}

void MessageCompose::para_init()
{
    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount);
    ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem("参数初始化"));
    ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem("07 01 0a 43 00 04 00 00 00"));
}

void MessageCompose::compare()
{
    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount);
    ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem("比较"));
}

void MessageCompose::done_save()
{
    QString name = ui->lineEdit->text();
    if (name == "")
    {
        QMessageBox::warning(this, "提示", "方案名称不能为空", QMessageBox::Yes);
        return;
    } else
    {
        QString temp = ui->comboBox->currentText();
        if (temp == "根目录")
            temp = R"(.\Data\check\)";
        string path = (temp + name).toStdString();
        ofstream outfile(path, ios::trunc);
        int rowcount = ui->tableWidget->rowCount();
        for (int i = 0; i < rowcount; i++)
        {
            QString describe = ui->tableWidget->item(i, 0)->text();
            QString APDU = ui->tableWidget->item(i, 1)->text();
            outfile << describe.toStdString() << '#' << APDU.toStdString() << endl;
        }
        outfile.close();
        close();
    }
}

void MessageCompose::save_place()
{
    std::vector<std::string> files;
    std::string path = R"(.\Data\check\)";
    getDir(path, files);
    for (const auto &i : files)
    {
        ui->comboBox->addItem(QString(QString::fromLocal8Bit(i.c_str())));
//        std::cout << "i: " << i << "\n";
    }
}

void MessageCompose::clear()
{
    int x = ui->tableWidget->rowCount();
    while (x)
    {
        x -= 1;
        ui->tableWidget->removeRow(0);
    }
}

