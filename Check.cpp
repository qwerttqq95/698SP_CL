
///自定义测试方案

#include "Check.h"
#include <QString>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMessageBox>
#include <fstream>
#include <ui_Check.h>

extern QString BuildMessage(QString apdu, const QString &SA, const QString &ctrl_zone);

extern QString re_rever_add();

Check::Check(QWidget *parent)
        : QDialog(parent), ui(new Ui::CheckDialogForm)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    model->setReadOnly(true);
    model->sort(0, Qt::AscendingOrder);
    model->setRootPath("./Data");
    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index("./Data/check"));
    ui->treeView->header()->setSectionResizeMode(0,
                                                 QHeaderView::ResizeToContents);
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(remove()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(creat_dir()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(creat_file()));
    connect(ui->treeView, SIGNAL(doubleClicked(
                                         const QModelIndex)), this,
            SLOT(doubleclick(
                         const QModelIndex)));
    compose = new MessageCompose();
    connect(this, SIGNAL(open_signal(QString)), compose,
            SLOT(open_exist(QString)));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(send_archeive()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(stop()));
}

void Check::send_archeive()
{
    run_flag = true;
    auto index = ui->treeView->currentIndex();
    QFile file(model->filePath(index));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QFileInfo fileinfo(model->filePath(index));
    QList<QString> message;
    if (fileinfo.isFile())
    {
        while (!file.atEnd())
        {
            if (!run_flag)
            {
                run_flag = true;
                QMessageBox::information(this, "提示", "已停止");
                return;
            }
            message.empty();
            QByteArray line = file.readLine();
            QString str(line);
            str.replace("\n", "");
            qDebug() << "str" << str;
            if (str == "")
            {
                continue;
            }
            message = str.split("#");
            if (message[0].contains("比较"))
            {
                emit compare_signal(message[1]);
                continue;
            } else
            {
                if (message[0].contains("延时"))
                {
                    QEventLoop eventloop;
                    QTimer::singleShot(message[1].toInt() * 1000, &eventloop, SLOT(quit()));
                    eventloop.exec();
                } else
                {
                    QString add = re_rever_add();
                    emit send_message({BuildMessage(message[1], add, "43"), message[0]});
                    QEventLoop eventloop;
                    QTimer::singleShot(3000, &eventloop, SLOT(quit()));
                    eventloop.exec();
                }
            }
        }
        QMessageBox::information(this, "提示", "下发完成");
    }
    file.close();
}


void Check::doubleclick(const QModelIndex &index)
{
    auto m = index.row();
    auto fo = index.sibling(m, 0).data().toString();
    auto fath = index.parent().data().toString();
    qDebug() << "position " << model->filePath(index);
    QFileInfo fileinfo(model->filePath(index));
    if (fileinfo.isFile())
            emit open_signal(model->filePath(index));
}

void Check::remove()
{
    model->setReadOnly(false);
    QModelIndex index_remove = ui->treeView->currentIndex();
    model->remove(index_remove);
    model->setReadOnly(true);
}

void Check::creat_dir()
{
    model->setReadOnly(false);
    QModelIndex index_creat_dir = ui->treeView->currentIndex();
    QString text = QInputDialog::getText(this, "新建文件夹", "文件名:");

    if (!model->mkdir(index_creat_dir, text).isValid())
    {
        index_creat_dir = ui->treeView->rootIndex();
        model->mkdir(index_creat_dir, text);
    }
    model->setReadOnly(true);
}

void Check::creat_file()
{
    compose->clear();
    compose->show();
}

void Check::stop()
{
    run_flag = false;
}
