
///自定义测试方案


#include "Check.h"
#include <QString>
#include <ui_Check.h>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMessageBox>
#include <utility>
#include <fstream>

Check::Check(QString add, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::CheckDialogForm)
{
    ui->setupUi(this);
    add_ = std::move(add);
    model = new QFileSystemModel(this);
    model->setReadOnly(true);
    model->sort(0, Qt::AscendingOrder);
    model->setRootPath("./Data");
    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index("./Data/check"));
    ui->treeView->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(remove()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(creat_dir()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(creat_file()));
    connect(ui->treeView, SIGNAL(doubleClicked(
                                         const QModelIndex)), this, SLOT(doubleclick(
                                                                                 const QModelIndex)));
    compose = new MessageCompose();
    connect(this, SIGNAL(open_signal(QString)), compose, SLOT(open_exist(QString)));
    connect(ui->pushButton, SIGNAL(clicked(
    )), this, SLOT(send_archeive()));
}

void Check::send_archeive()
{
    auto index = ui->treeView->currentIndex();
    QFile file(model->filePath(index));
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QFileInfo fileinfo(model->filePath(index));
    if (fileinfo.isFile())
    {
        while (!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString str(line);
            str.replace("\n", "");
            qDebug() << "str" << str;
        }

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
    if (!model->mkdir(index_creat_dir, "new").isValid())
    {
        index_creat_dir = ui->treeView->rootIndex();
        model->mkdir(index_creat_dir, "new");
    }
    model->setReadOnly(true);
}

void Check::creat_file()
{
    compose->clear();
    compose->show();
}





