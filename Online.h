//
// Created by admin on 2020/2/13.
//

#ifndef INC_698SP_CL_ONLINE_H
#define INC_698SP_CL_ONLINE_H

#pragma once

#include <QtWidgets/QDialog>
#include <ONLINE/Ftp_client.h>
#include "ui_Online.h"
#include "vector"
#include"ONLINE/Ftp_client.h"
#include"ONLINE/commandparameter.h"

using namespace std;
namespace Ui {
    class OnlineDialog;
}

class Online : public QDialog {
Q_OBJECT
public:
    explicit Online(QWidget *parent = nullptr);

    void clientrun();

    void login();

    void uploadfiles();

    string get_file_dir(string &temp);

private:
    Ui::OnlineDialog *ui;
    FTP client;
};


#endif //INC_698SP_CL_ONLINE_H
