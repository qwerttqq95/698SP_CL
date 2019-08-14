#include "MessageCompose.h"
#include "ui_UI_MessageCompose.h"
#include "QMessageBox"
#include <string>
#include <fstream>


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

void MessageCompose::open_exist(const QString &add)
{
    clear();
    show();
    QByteArray cdata = add.toLocal8Bit();
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
        QList<QString> name;
        name = add.split("/");
        ui->lineEdit->setText(name.last());
        QString qwe;
        QString new_add = "";
        name.takeLast();
        while (true)
        {
            qwe = name.takeLast();
            if (qwe == "Data")
            {
                new_add = "./Data" + new_add;
                break;
            } else
                new_add = "/" + qwe +
                          new_add;
        }
        qDebug() << "new_add" << new_add;
        if (new_add == "./Data/check")
            new_add = "根目录";
        int i = 0;
        while (true)
        {
            qDebug() << "ui->comboBox->currentIndex() " << ui->comboBox->currentIndex();
            qDebug() << "real_add " << new_add;
            if (ui->comboBox->currentIndex() == -1)
            {
                qDebug() << "break";
                break;
            }
            if (ui->comboBox->currentText() == new_add)
            {
                break;
            } else
            {
                i += 1;
                ui->comboBox->setCurrentIndex(i);
            }
        }

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
            temp = "./Data/check/";
        QByteArray cdata = (temp + '/' + name).toLocal8Bit();
        string path = std::string(cdata);
        int rowcount = ui->tableWidget->rowCount();
        for (int i = 0; i < rowcount; i++)
        {
            QString describe = ui->tableWidget->item(i, 0)->text();
            QString APDU = ui->tableWidget->item(i, 1)->text();
            if (APDU.replace(" ", "").size() % 2 == 1)
            {
                QMessageBox::warning(this, "Waring", "APDU长度错误在" + (QString) i + "行");
                return;
            }
        }
        ofstream outfile(path, ios::trunc);
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
    std::string path = "./Data/check";
    getDir(path, files);
    for (const auto &i : files)
    {
        ui->comboBox->addItem(QString(QString::fromLocal8Bit(i.c_str())));
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

