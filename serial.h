#ifndef INC_698SP_CL_SERIAL_H
#define INC_698SP_CL_SERIAL_H

#include <QDialog>
#include <process.h>
#include "TChar.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <Windows.h>


namespace Ui {
    class Dialog;
}
class Serial : public QDialog {
Q_OBJECT
public:
    bool run_flag;
    explicit Serial(QWidget *parent = nullptr);

    ~Serial() override;

    bool open_serial(std::basic_string<TCHAR>);

    QStringList getEnableCommPort(QList<QString> &PortList);

    BOOL CloseSerial();

    static bool build_net();

    HANDLE hCom;


private:
    Ui::Dialog *ui;


public slots:

    void creat_process();

};

#endif //INC_698SP_CL_SERIAL_H


