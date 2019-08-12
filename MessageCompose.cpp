#include "MessageCompose.h"
#include "ui_UI_MessageCompose.h"
#include "QMessageBox"
#include "io.h"
#include <string>

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

    }


}

void MessageCompose::save_place()
{
    std::cout << "shuchu";
    std::vector<std::string> files;
    std::string path = R"(.\Data\check\)";

    getDir(path, files);
    for (const auto &i : files)
    {
        ui->comboBox->addItem(QString::fromStdString(i));
        std::cout << "i: " << i << "\n";
    }
}
