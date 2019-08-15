//
// Created by admin on 30/7/2019.
//

#ifndef INC_698SP_CL_CHECK_H
#define INC_698SP_CL_CHECK_H

#include <QtCore>
#include <QDialog>
#include <QDebug>
#include <QtGui/QStandardItem>
#include <QtWidgets/QDirModel>
#include <QtWidgets/QFileSystemModel>
#include "MessageCompose.h"
#include "QFile"

namespace Ui
{
    class CheckDialogForm;
}

class Check : public QDialog
{
Q_OBJECT
public:
    explicit Check(QString add, QWidget *parent = nullptr);

    bool run_flag;
    QFileSystemModel *model;
    QString add_;
private:
    Ui::CheckDialogForm *ui;
    MessageCompose *compose;

public slots:

    void remove();

    void creat_dir();

    void creat_file();

    void doubleclick(const QModelIndex &index);

    void send_archeive();

    void stop();
signals:

    void compare_signal(QString);

    void send_message(QList<QString>);

    void open_signal(QString);
};

#endif //INC_698SP_CL_CHECK_H
