#include "serial.h"
#include "ui_serial.h"
#include "Qt"
#include <string>
#include <iostream>
#include <iomanip>
#include <pthread.h>
#include <c++/thread>
#include <QtWidgets/QMessageBox>
#include <QList>
#include <QDebug>

using namespace std;

extern int String2Hex(string &str, BYTE *pOut, DWORD *pLenOut, DWORD nMaxLen);

extern string StringAddSpace(string &input);

Serial::Serial(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Dialog) {
    ui->setupUi(this);
    setWindowTitle("通讯配置");
    setWindowFlags(Qt::WindowStaysOnTopHint);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(creat_process()));
    QList<QString> PortList;
    PortList = getEnableCommPort(PortList);
    for (int i = 0; i<PortList.size(); i++) {
        ui->comboBox->addItem(PortList[i]);
    }
}

void Serial::creat_process() {
    if (ui->radioButton->isChecked()) {
        if (ui->pushButton->text() == "打开") {
            ui->pushButton->setText("关闭");
            QString  str = ui->comboBox->currentText();
            char*  ch;
            QByteArray ba = str.toLatin1(); // must
            ch=ba.data();
            std::basic_string<TCHAR> s1 = ch;
            std::thread t1(open_serial,this,s1);
            t1.detach();

        } else {
            ui->pushButton->setText("打开");
            CloseSerial();

        }


    } else {
        std::thread t2(build_net);
        t2.detach();
    }
}

bool Serial::open_serial(std::basic_string<TCHAR> s1) {
    HANDLE hCom;
//    std::basic_string<TCHAR> s1 = "COM13";
    std::basic_string<TCHAR> s2 = "\\\\.\\";
    std::basic_string<TCHAR> s3 = s2 + s1;
    LPCTSTR a3 = s3.c_str();
    hCom = CreateFile(a3,
                      GENERIC_READ | GENERIC_WRITE, //允许读和写
                      0, //独占方式
                      NULL,
                      OPEN_EXISTING, //打开而不是创建
                      0, //同步方式
                      NULL);
    SetupComm(hCom, 1024, 1024); //输入缓冲区和输出缓冲区的大小都是1024
    if (hCom == (HANDLE) -1) {
        cout << "open com fail!";
        return FALSE;
    }
    COMMTIMEOUTS TimeOuts;
//设定读超时
    TimeOuts.ReadIntervalTimeout = 1000;
    TimeOuts.ReadTotalTimeoutMultiplier = 500;
    TimeOuts.ReadTotalTimeoutConstant = 5000;
//设定写超时
    TimeOuts.WriteTotalTimeoutMultiplier = 500;
    TimeOuts.WriteTotalTimeoutConstant = 2000;
    SetCommTimeouts(hCom, &TimeOuts); //设置超时

    DCB dcb;
    GetCommState(hCom, &dcb);
    dcb.BaudRate = 9600;
    dcb.ByteSize = 8;
    dcb.Parity = EVENPARITY;
    dcb.StopBits = ONESTOPBIT;
    SetCommState(hCom, &dcb);
    PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);//清空缓冲区

    char str[400] = {0};
    DWORD wCount;//读取的字节数
    BOOL bReadStat;

    BYTE Apdu[400] = {0};
    DWORD nApduLen = 0;
    string add = "6817004345AAAAAAAAAAAA10DA5F0501034001020000900f16";
    transform(add.begin(), add.end(), add.begin(), ::tolower);
    String2Hex(add, Apdu, &nApduLen, sizeof(Apdu));
    COMSTAT ComStat;
    DWORD dwErrorFlags;
    BOOL bWriteStat;
    ClearCommError(hCom, &dwErrorFlags, &ComStat);
    DWORD dwBytesWrite = nApduLen;
    cout << "Send: " << StringAddSpace(add) << endl;
    bWriteStat = WriteFile(hCom, Apdu, dwBytesWrite, &dwBytesWrite, NULL);
    if (!bWriteStat) {
        cout << "Write data fail!!" << endl;
    } else {
//            cout << "send success" << endl;
    }
    while (true) {
        PurgeComm(hCom, PURGE_TXABORT |
                        PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
        bReadStat = ReadFile(hCom, str, 200, &wCount, nullptr);
        if (!bReadStat) {
            cout << "Read data fail!";
            return FALSE;
        } else {
            string output = "";
            char temp[10] = {0};
            for (int i = 0; i < wCount; i++) {
                sprintf(temp, "%02X ", (BYTE) str[i]);
                output = output + temp;
            }
            cout << "Receive: " << output << endl;
        }
    }
//    return true;
}


bool Serial::build_net() { //#todo
    return false;
}

BOOL Serial::CloseSerial() {
    CloseHandle(hCom);
}

QStringList Serial::getEnableCommPort(QList<QString> &PortList) {
    PortList.clear();
    HKEY hkey;
    LONG lRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0,
                             KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS | KEY_READ, &hkey);
    if (lRes == ERROR_SUCCESS) {
        TCHAR tchKey[MAX_PATH];
        TCHAR tchValue[20];
        DWORD dwIndex = 0;
        DWORD dwType = REG_SZ;
        while (lRes == ERROR_SUCCESS) {
            DWORD dwCount = MAX_PATH;
            DWORD dwVCount = 20;
            lRes = RegEnumValue(hkey, dwIndex++, tchKey, &dwCount, NULL, &dwType, (LPBYTE) tchValue, &dwVCount);
            if (lRes == ERROR_SUCCESS) {
                if ((dwVCount > 0) && (dwCount > 0)) {
                    QString str;
                    str = tchValue;
                    PortList.append(str);
                }
            }
        }
    }
    RegCloseKey(hkey);
    qDebug() << "Date:" << PortList;
    return PortList;
}


Serial::~Serial() {
    cout << "out";
};
