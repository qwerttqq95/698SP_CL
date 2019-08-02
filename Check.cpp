//
// Created by admin on 30/7/2019.
//

#include "Check.h"
#include <QString>
#include <ui_Check.h>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMessageBox>


Check::Check(QString add, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::CheckDialog)
{
    ui->setupUi(this);
    add_ = std::move(add);
    QDirModel *model = new QDirModel;
    model->setReadOnly(true);
    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(".\\Data\\check"));
    ui->treeView->resizeColumnToContents(0);


}
