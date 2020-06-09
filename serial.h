
#ifndef SOCK
#define SOCK
#include <winsock2.h>
#endif
#ifndef INC_698SP_CL_SERIAL_H
#define INC_698SP_CL_SERIAL_H
#include <QDialog>

#include <windows.h>

#include <process.h>
#include "tchar.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <cctype>
#include "XMLFile/tinyxml2.h"

#include <stdio.h>
#include <QString>


namespace Ui {
    class Dialog;
}
class Serial : public QDialog {
Q_OBJECT
public:
    bool run_flag;
    bool internet_or_serial;
    SOCKET clientSock;
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement *root;

    explicit Serial(QWidget *parent = nullptr);

    ~Serial() override;

    bool open_serial(const std::basic_string<TCHAR>&);

    QStringList getEnableCommPort(QList<QString> &PortList);

    BOOL CloseSerial();

    bool build_net(int com);

    bool write_(QList<QString>);

    BOOL IsSocketClosed(SOCKET clientSocket);

    HANDLE hCom{};


private:
    Ui::Dialog *ui;


public slots:

    bool write(const QList<QString>&);

    void creat_process();

    void warming();

signals:

    void send_message(QList<QString>);

    void receive_message(QString);

    void open_fail_message();

    void send_write(QList<QString>);


};

#endif //INC_698SP_CL_SERIAL_H


