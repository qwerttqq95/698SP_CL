//
// Created by admin on 2020/2/13.
//
#include <memory>
#include <QtGui/QStandardItemModel>
#include <QtWidgets/QTreeWidgetItem>
#include "Online.h"
#include "iostream"
#include "QDebug"
#include "string"
#include "QMessageBox"
#include "cstring"

Online::Online(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::OnlineDialog) {
    ui->setupUi(this);
    setWindowTitle(QString::fromLocal8Bit("线上自定义测试项"));
    client = FTP();
    clientrun();
}

void Online::clientrun() {
    login();
}

string Online::get_file_dir(string &temp) {
    string file_dir;
    int i;
    for (i = 0; i < temp.length(); i++) {
        if (temp[i] != ' ')
            break;
    }
    file_dir.assign(temp, i, temp.length() - i);
    if (file_dir[file_dir.length() - 1] != ' ')
        return file_dir;
    else {
        for (i = file_dir.length() - 1; i >= 0 && file_dir[i] != ' '; i--);
        file_dir.assign(file_dir, 0, i);
        return file_dir;
    }
}

void Online::login() {
    shared_ptr<usr_psd> ptr(new usr_psd());
    string name("anonymous");
    string url("172.18.51.79");
    string password("none");
    string command("check");
    ptr->set_paramater(url, name, password);
    client.set_userInfo(ptr);
    if (!client.creatSock()) {
        cout << "create socket failed" << endl;
        return;
    }
    try {
        if (!client.login()) {
            cout << "failed because of the internet" << endl;
            QMessageBox::warning(this, "Warming", "Failed because of the network");
            return;
        } else {
            if (!client.cmd_list()) {
                cout << "could not fetch the files and directories from the server.please try the LS command!" << endl;
                QMessageBox::warning(this, "Warming",
                                     "Could not fetch the files and directories from the server.please try the LS command!");
                return;
            }
        }
    }
    catch (string &e) {
        cout << e << endl;
        return;
    }
    cout << "login success,the directory is listed above " << endl;
    string dir;
    dir = get_file_dir(command);
    client.CD_command(dir);
    char x[4096];
    strcpy(x, client.recbuffer);
    QString list = QString::fromLocal8Bit(x);
    auto list_split = list.split("\r\n");
    QStandardItemModel *model = new QStandardItemModel(0, 4);
    model->setHeaderData(0, Qt::Horizontal, tr("Date"));
    model->setHeaderData(1, Qt::Horizontal, tr("Modify"));
    model->setHeaderData(2, Qt::Horizontal, tr("Att/Size"));
    model->setHeaderData(3, Qt::Horizontal, tr("Name"));
    ui->treeView->setModel(model);
    int ti = 0;
    for (const auto &xx :list_split) {
        auto signal = xx.split(" ", QString::SplitBehavior::SkipEmptyParts);
        if (!signal.isEmpty()) {
            qDebug() << "list_split: " << signal;
            model->setItem(ti, 0, new QStandardItem(signal[0]));
            model->setItem(ti, 1, new QStandardItem(signal[1]));
            model->setItem(ti, 2, new QStandardItem(signal[2]));
            model->setItem(ti, 3, new QStandardItem(signal[3]));
            ti++;
        }

    }

}

void Online::uploadfiles() {
    cout << "pleas input the file path correctly,if no more,just input \"end\"" << endl;
    char name[1024];
    client.ClearVector();
    while (1) {
        memset(name, 0, sizeof(name));
        cin.getline(name, 1024, '\n');
        if (string(name) == "end")
            break;
        client.add_file_path(string(name));
        //	cout << "name: " << name << endl;
    }
    try {
        client.upload_file();
    }
    catch (string &e) {
        cout << e << endl;
    }
    cout << "total " << client.getFileCount() << " files have been uploaded" << endl;
}
