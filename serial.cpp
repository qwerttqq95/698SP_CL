#include "serial.h"
#include "ui_serial.h"
#include "Qt"
#include <thread>
#include <QtWidgets/QMessageBox>
#include <QList>
#include <QDebug>

using namespace std;
#pragma comment (lib, "ws2_32")
#pragma comment (lib, "winmm")

extern int Stringlist2Hex_char(QString &str, char *pOut);

extern int String2Hex(string &str, BYTE *pOut, DWORD *pLenOut, DWORD nMaxLen);

extern string StringAddSpace(string &input);

extern string StringAddSpace(QString &input);

extern int check(QString);


Serial::Serial(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("通讯配置");
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(creat_process()));
    connect(this, SIGNAL(open_fail_message()), this, SLOT(warming()));
    connect(this, SIGNAL(send_write(QList<QString>)), this, SLOT(write(QList<QString>)));
    QList<QString> PortList;
    PortList = getEnableCommPort(PortList);
    for (const auto &i : PortList)
    {
        ui->comboBox->addItem(i);
    }
    doc.LoadFile("config.xml");
    root = doc.RootElement();
    tinyxml2::XMLElement *first_child1 = root->FirstChildElement("port");
    const char *port;
    port = first_child1->GetText();
    QString COM = (QString) port;
    ui->lineEdit->setText(COM);
}

void Serial::creat_process()
{
    if (ui->radioButton->isChecked())  //串口
    {
        if (ui->pushButton->text() == "打开")
        {
            run_flag = true;
            ui->pushButton->setText("关闭");
            ui->comboBox->setDisabled(true);
            ui->comboBox_2->setDisabled(true);
            ui->lineEdit->setDisabled(true);
            ui->radioButton_2->setDisabled(true);
            QString str = ui->comboBox->currentText();
            char *ch;
            QByteArray ba = str.toLatin1();
            ch = ba.data();
            std::basic_string<TCHAR> s1 = ch;
            std::thread t1(&Serial::open_serial, this, s1);
            t1.detach();
            close();
            internet_or_serial = true;
        } else
        {
            ui->pushButton->setText("打开");
            ui->comboBox->setDisabled(false);
            ui->comboBox_2->setDisabled(false);

            ui->lineEdit->setDisabled(false);
            ui->radioButton_2->setDisabled(false);
            CloseSerial();
        }

    } else //以太网
    {
        qDebug() << "以太网状态";
        tinyxml2::XMLElement *first_child1 = root->FirstChildElement("port");
        int com = ui->lineEdit->text().toInt();
        first_child1->SetText(com);
        doc.SaveFile("config.xml");
        if (ui->pushButton->text() == "打开")
        {
            run_flag = true;
            ui->pushButton->setText("关闭");
            std::thread t2(&Serial::build_net, this, ui->lineEdit->text().toInt());
            t2.detach();
            close();
            internet_or_serial = false;
            ui->comboBox->setDisabled(true);
            ui->comboBox_2->setDisabled(true);
            ui->lineEdit->setDisabled(true);
            ui->radioButton->setDisabled(true);

        } else
        {
            ui->pushButton->setText("打开");
            ui->comboBox->setDisabled(false);
            ui->comboBox_2->setDisabled(false);
            ui->lineEdit->setDisabled(false);
            ui->radioButton_2->setDisabled(false);
            ui->radioButton->setDisabled(false);
            CloseSerial();
        }
    }
}


bool Serial::open_serial(const std::basic_string<TCHAR> &s1)
{
    char str[1000] = {0};
    DWORD wCount;//读取的字节数
    BOOL bReadStat;
    std::basic_string<TCHAR> s2 = R"(\\.\)";
    std::basic_string<TCHAR> s3 = s2 + s1;
    LPCTSTR a3 = s3.c_str();
    hCom = CreateFile(a3,
                      GENERIC_READ | GENERIC_WRITE, //允许读和写
                      0, //独占方式
                      nullptr,
                      OPEN_EXISTING, //打开而不是创建
                      0, //同步方式
                      nullptr);
    SetupComm(hCom, 1024, 1024); //输入缓冲区和输出缓冲区的大小都是1024
    if (hCom == (HANDLE) -1)
    {
        cout << "open com fail!";
        emit open_fail_message();
        return FALSE;
    }
    run_flag = true;
    COMMTIMEOUTS TimeOuts;
    TimeOuts.ReadIntervalTimeout = 0;
    TimeOuts.ReadTotalTimeoutMultiplier = 0;
    TimeOuts.ReadTotalTimeoutConstant = 200;
    TimeOuts.WriteTotalTimeoutMultiplier = 0;
    TimeOuts.WriteTotalTimeoutConstant = 0;
    SetCommTimeouts(hCom, &TimeOuts); //设置超时
    DCB dcb;
    GetCommState(hCom, &dcb);
    dcb.BaudRate = (unsigned) ui->comboBox_2->currentText().toLong(nullptr);
    dcb.ByteSize = 8;
    dcb.Parity = EVENPARITY;
    dcb.StopBits = ONESTOPBIT;
    SetCommState(hCom, &dcb);
    PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);//清空缓冲区
    QString add = "6817004345AAAAAAAAAAAA10DA5F0501034001020000900f16";
    emit send_write({add, ""});
    PurgeComm(hCom, PURGE_TXABORT |
                    PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
    string temp1;
    int times = 0;
    while (run_flag)
    {
        bReadStat = ReadFile(hCom, str, 700, &wCount, nullptr);
        if (!bReadStat)
        {
            cout << "Read data fail!";
            return FALSE;
        } else
        {
            string output;
            char temp[10] = {0};
            for (int i = 0; i < wCount; i++)
            {
                sprintf(temp, "%02X ", (BYTE) str[i]);
                output = output + temp;
            }
            if (output.empty())
            {
                continue;
            }
            if (!temp1.empty())
            {
                output = temp1 + output;
                times += 1;
                if (times > 4000)
                {
                    temp1 = "";
                    times = 0;
                    continue;
                }
            }
            switch (check(QString::fromStdString(output)))
            {
                case 0:
                {
//                    qDebug()<<"case 0";
                }
                    break;
                case 1:
                {
                    cout << "Receive: " << output << endl;
                    emit receive_message(QString::fromStdString(output));   //接收显示
                    PurgeComm(hCom, PURGE_TXABORT |
                                    PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
                    temp1 = "";
                }
                    break;
                case 2:
                {
//                    qDebug()<<"case 2";
                    temp1 = output;
                }
                    break;
                default:
//                    qDebug()<<"default";
                    break;
            }
        }
    }
    cout << "quit cir\n";
    CloseHandle(hCom);
    return false;
}

bool Serial::write(const QList<QString> &add)
{

    std::thread t3(&Serial::write_, this, add);
    t3.detach();
    return true;
}

bool Serial::write_(QList<QString> add) //发送
{
    if (internet_or_serial == 1) //串口
    {
        BYTE Apdu[1500] = {0};
        DWORD nApduLen = 0;
        string new_add = add[0].toStdString();
        transform(new_add.begin(), new_add.end(), new_add.begin(), ::tolower);
        String2Hex(new_add, Apdu, &nApduLen, sizeof(Apdu));
        COMSTAT ComStat;
        DWORD dwErrorFlags;
        BOOL bWriteStat;
        ClearCommError(hCom, &dwErrorFlags, &ComStat);
        DWORD dwBytesWrite = nApduLen;
        cout << "Send: " << StringAddSpace(new_add) << endl;
        emit send_message(add);
        bWriteStat = WriteFile(hCom, Apdu, dwBytesWrite, &dwBytesWrite, nullptr);
        if (!bWriteStat)
        {
            cout << "Write data fail!!" << endl;
            return false;
        }

    } else  //以太网
    {
        char Apdu[1500] = {0};
        Stringlist2Hex_char(add[0], Apdu);
        send(clientSock, Apdu, add[0].length() / 2, 0);
        string new_add = add[0].toStdString();
        cout << "Eth Send: " << StringAddSpace(new_add) << endl;
        emit send_message(add);
    }
    return true;
}

bool Serial::build_net(int com)
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in addr{};
    addr.sin_addr.S_un.S_addr = inet_addr("0.0.0.0");
    addr.sin_port = htons(com);
    addr.sin_family = PF_INET;
    bind(s, (SOCKADDR *) &addr, sizeof(SOCKADDR));
    listen(s, 1);
    SOCKADDR clientAddr;
    int nSize = sizeof(SOCKADDR);
    int recvTimeout = 4000; 
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *) &recvTimeout, sizeof(int));
    clientSock = ::accept(s, &clientAddr, &nSize);
    int is_head = 1;
    QStringList list_backup;
    while (run_flag)
    {
        char buff[4000] = {0};
        int i;
        i = recv(clientSock, buff, 4000, 0);
        if (i == -1)
        {
            if (IsSocketClosed(clientSock) and run_flag)
            {
                qDebug() << "try to reconnect";
                clientSock = ::accept(s, &clientAddr, &nSize);
                continue;
            } else
                continue;
        }
        if (i == 0)
        {
//            qDebug() << "i=0";//终端下线
            break;
        }
        char a[4] = {0};
        string output = string("");
        for (int x = 0; x <i; x++)
        {
            sprintf(a, "%02X ", (BYTE) buff[x]);
            output = output + a;
        }
        QStringList list = QString::fromStdString(output).split(' ', QString::SkipEmptyParts);
        if (is_head == 1)
        {
            judge:
            int message_len = (list[2] + list[1]).toInt(nullptr, 16);
            qDebug() << "message_len " << message_len;
            qDebug() << "list.size() " << list.size();

            if (list[0] == "68" and list.endsWith("16") and message_len + 2 == list.size())
            {
                auto full = list.join(" ");
                is_head = 1;
                qDebug() << "Receive from client :" << full << endl;
                receive_message(full);

            } else if (list[0] == "68")
            {
                qDebug() << "need more"<<list;
                list_backup = list;
                is_head = 0;
            }
        } else
        {
            qDebug() << "detach"<<list;
            list = list_backup +  list ;
            is_head = 1;
            goto judge;
        }
    }
    qDebug() << "qiute eth";
    qDebug() << "runflag " << run_flag;
    closesocket(clientSock);
    closesocket(s);
    WSACleanup();
    return true;
}


BOOL Serial::IsSocketClosed(SOCKET clientSocket)
{
    bool ret = false;
    HANDLE closeEvent = WSACreateEvent();
    WSAEventSelect(clientSocket, closeEvent, FD_CLOSE);

    DWORD dwRet = WaitForSingleObject(closeEvent, 0);

    if (dwRet == WSA_WAIT_EVENT_0)
        ret = true;
    else if (dwRet == WSA_WAIT_TIMEOUT)
        ret = false;

    WSACloseEvent(closeEvent);
//    qDebug() << "ret " << ret;
    return ret;
}

BOOL Serial::CloseSerial()
{
    run_flag = false;
    return true;
}

QStringList Serial::getEnableCommPort(QList<QString> &PortList)
{
    PortList.clear();
    HKEY hkey;
    LONG lRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0,
                             KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS | KEY_READ, &hkey);
    if (lRes == ERROR_SUCCESS)
    {
        TCHAR tchKey[MAX_PATH];
        TCHAR tchValue[20];
        DWORD dwIndex = 0;
        DWORD dwType = REG_SZ;
        while (lRes == ERROR_SUCCESS)
        {
            DWORD dwCount = MAX_PATH;
            DWORD dwVCount = 20;
            lRes = RegEnumValue(hkey, dwIndex++, tchKey, &dwCount, nullptr, &dwType, (LPBYTE) tchValue, &dwVCount);
            if (lRes == ERROR_SUCCESS)
            {
                if ((dwVCount > 0) && (dwCount > 0))
                {
                    QString str;
                    str = tchValue;
                    PortList.append(str);
                }
            }
        }
    }
    RegCloseKey(hkey);
//    qDebug() << "Date:" << PortList;
    return PortList;
}


Serial::~Serial()
= default;

void Serial::warming()
{
    QMessageBox::warning(this, "ERROR", "串口打开失败!", QMessageBox::Ok);
    ui->pushButton->setText("打开");
    ui->comboBox->setDisabled(false);
    ui->comboBox_2->setDisabled(false);
}

