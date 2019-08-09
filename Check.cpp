//
// Created by admin on 30/7/2019.
//

#include "Check.h"
#include <QString>
#include <ui_Check.h>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMessageBox>
#include <utility>


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
    compose = new MessageCompose();
    compose->show();


//    model->setReadOnly(false);
//    QModelIndex index_creat_file = ui->treeView->currentIndex();
//    QFile file("./Data/check/test");
//    file.open(QFile::WriteOnly|QFile::Truncate);
//    QTextStream textStream(&file);
//    textStream<<"123";
//    file.close();
//    model->setReadOnly(true);
}


