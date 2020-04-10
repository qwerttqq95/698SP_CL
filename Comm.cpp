#include <string>
#include <QString>
#include <QtCore/QStringList>
#include <QDebug>
#include <MeterArchives.h>
//#include <mainwindow.h>
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <vector>
#include <XMLFile/tinyxml2.h>
#include <QtWidgets/QTreeWidgetItem>
#include "io.h"

#define PPPINITFCS16 0xffff
#define DATA_NULL                        0
#define DATA_ARRAY                       1
#define DATA_STRUCT                      2
#define DATA_BOOL                        3
#define DATA_BITSTRING                   4
#define DATA_DOUBLE_LONG                 5
#define DATA_DOUBLE_LONG_UNSIGNED        6
#define DATA_OCT_STRING                  9
#define DATA_VISIBLE_STRING             10
#define DATA_UTF8_STRING                12
#define DATA_INTEGER                    15
#define DATA_LONG                       16
#define DATA_UNSIGNED                   17
#define DATA_LONG_UNSIGNED              18
#define DATA_LONG64                        20
#define DATA_LONG64_UNSIGNED            21
#define DATA_ENUM                        22
#define DATA_FLOAT32                    23
#define DATA_FLOAT64                    24
#define DATA_DATE_TIME                    25
#define DATA_DATE                        26
#define DATA_TIME                        27
#define DATA_DATE_TIME_S                28
#define DATA_OI                            80
#define DATA_OAD                        81
#define DATA_ROAD                        82
#define DATA_OMD                        83
#define DATA_TI                            84
#define DATA_TSA                        85
#define DATA_MAC                        86
#define DATA_RN                            87
#define DATA_REGION                        88
#define DATA_SCALER_UNIT                89
#define DATA_RSD                        90
#define DATA_CSD                        91
#define DATA_MS                            92
#define DATA_SID                        93
#define DATA_SID_MAC                    94
#define DATA_COMDCB                        95
#define DATA_RCSD                        96

using namespace std;


QString binToDec(QString strBin) {  //二进制转十进制
    QString decimal;
    int nDec = 0, nLen;
    int i, j, k;
    nLen = strBin.length();
    for (i = 0; i < nLen; i++) {
        if (strBin[nLen - i - 1] == "0")
            continue;
        else {
            k = 1;
            for (j = 0; j < i; j++)
                k = k * 2;
            nDec += k;
        }
    }
    decimal = QString::number(nDec);
    return decimal;
}

void getDir(string path, vector<string> &files) {
    long hFile = 0;
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
                    files.push_back(p.assign(path).append("/").append(fileinfo.name));
                    getDir(p.assign(path).append("/").append(fileinfo.name), files);
                }
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

int Stringlist2Hex(QString &str, BYTE *pOut);

QString message_swap(const QString &a) {
    QList<QString> list;
    for (int i = 0; i <= a.length() / 2; i += 2) {
        list.append(a.mid(i, i + 2));
    }
    QString re = "";
    for (int y = list.length() - 1; y >= 0; y--) {
        re = re + list[y];
    }
    return re;
}

int String2Hex(string &str, BYTE *pOut, DWORD *pLenOut, DWORD nMaxLen) {
    int i, j = 0;
    DWORD len;
    TCHAR x;
    for (i = 0, x = 0, len = 0;
         i < (int) str.length() && len < (int) nMaxLen;
         i++) {
        if (j >= 2) {
            pOut[len++] = (BYTE) x;
            x = 0;
            j = 0;
        }
        if (str[i] >= '0' && str[i] <= '9') {
            x <<= 4;
            x |= str[i] - '0';
            j++;
        } else if ((str[i] >= 'A' && str[i] <= 'F')
                   || (str[i] >= 'a' && str[i] <= 'f')) {
            x <<= 4;
            x |= _toupper (str[i]) - 'A' + 10;
            j++;
        } else if (j) {
            pOut[len++] = (BYTE) x;
            x = 0;
            j = 0;
        }
    }
    if (j) {
        pOut[len++] = (BYTE) x;
        x = 0;
        j = 0;
    }

    if (pLenOut)
        *pLenOut = len;

    return 0;
}

const static WORD fcstab[256] = {
        0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
        0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
        0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
        0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
        0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
        0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
        0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
        0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
        0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
        0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
        0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
        0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
        0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
        0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
        0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
        0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
        0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
        0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
        0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
        0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
        0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
        0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
        0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
        0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
        0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
        0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
        0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
        0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
        0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
        0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
        0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
        0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};

unsigned short pppfcs16(unsigned short fcs, unsigned char *p, unsigned int len) {
    while (len--) {
        fcs = (fcs >> 8) ^ fcstab[(fcs ^ *p++) & 0xff];
    }
    return (fcs ^ 0xffff);
}

QString DealDataType(const int NoDataType, int len, QTreeWidgetItem *item) {
    switch (NoDataType) {
        default:
            return NULL;
        case 0://NULL
        {
            return "00";
        }
        case 1://ARRAY
        {
            return QString("%1%2").arg(NoDataType, 2, 16, QLatin1Char('0')).arg(item->text(2).toInt(), 2, 16,
                                                                                QLatin1Char('0'));
        }
        case 2://STRUCTURE
        {
            return QString("%1%2").arg(NoDataType, 2, 16, QLatin1Char('0')).arg(item->text(2).toInt(), 2, 16,
                                                                                QLatin1Char('0'));
        }
        case 3://BOOL
        {
            return QString("%1%2").arg(NoDataType, 2, 16, QLatin1Char('0')).arg(item->text(2).toInt(), 2, 16,
                                                                                QLatin1Char('0'));
        }
        case 4://bit-string
        {
            return QString("%1").arg(NoDataType, 2, 16, QLatin1Char('0')) + "01" +
                   QString("%1").arg(binToDec(item->text(2)).toInt(), 2, 16, QLatin1Char('0'));
        }
        case 9://octet-string
        {
            if (item->text(2).contains(".")) {
                QString content("");
                QString lenth = "04";
                        foreach(auto x, item->text(2).split(".")) {
                        content.append(QString("%1").arg(x.toInt(), 2, 16, QLatin1Char('0')));
                    }
                return QString("%1").arg(NoDataType, 2, 16, QLatin1Char('0')) + lenth + content;
            } else if (item->text(2).contains(":")) {
                return QString("0906" + item->text(2).remove(":"));
            }
        }
        case 10://visible-string
        {
            QString Data = item->text(2);
            if (Data == "00") {
                return "0a00";
            } else {
                QString content = item->text(2).toUtf8().toHex();
                QString lenth = QString("%1").arg(content.length() / 2, 2, 16, QLatin1Char('0'));
                return QString("%1").arg(NoDataType, 2, 16, QLatin1Char('0')) + lenth + content;
            }
        }
        case 17://unsigned
        {
            return QString("%1%2").arg(NoDataType, 2, 16, QLatin1Char('0')).arg(item->text(2).toInt(), 2, 16,
                                                                                QLatin1Char('0'));
        }
        case 18://long-unsigned
        {
            return QString("%1%2").arg(NoDataType, 2, 16, QLatin1Char('0')).arg(item->text(2).toInt(), len * 2, 16,
                                                                                QLatin1Char('0'));
        }
        case 22://ENUM
        {
            return QString("%1%2").arg(NoDataType, 2, 16, QLatin1Char('0')).arg(item->text(2).toInt(), 2, 16,
                                                                                QLatin1Char('0'));
        }
        case 28://date_time_s
        {
            QString date = item->text(2).split(" ")[0];
            QString data("");
            QStringList temp = date.split("-");
            QString Year = QString("%1").arg(temp[0].toInt(), 4, 16, QLatin1Char('0'));
            QString Mouth = QString("%1").arg(temp[1].toInt(), 2, 16, QLatin1Char('0'));
            QString Day = QString("%1").arg(temp[2].toInt(), 2, 16, QLatin1Char('0'));
            QString re = "1c" + Year + Mouth + Day;
            QStringList times = item->text(2).split(" ")[1].split(":");
                    foreach(auto x, times) {
                    re.append(QString("%1").arg(x.toInt(), 2, 16, QLatin1Char('0')));
                }
            return re;
        }
    }
}


QString BuildMessage(const QString &apdu, const QString &SA, const QString &ctrl_zone) {
    qDebug() << "apdu:" << apdu;
    qDebug() << "SA:" << SA;
    qDebug() << "ctrl_zone:" << ctrl_zone;
//    qDebug() << "apdu" << apdu;
    int len = SA.length() / 2 - 1;
    if (len == -1 or len == 0) {
        qDebug() << "BuildMessage 1 error";
        return "0";
    }
    QString SA_sign = QString("%1").arg(len);
    int apdulen = apdu.length() / 2;
    int Total_length = 10 + len + apdulen;
    int lenth1 = Total_length & 0x00ff;
    int lenth2 = Total_length >> 8;
    char len1[3] = {'0', '0'};
    char len2[3] = {'0', '0'};
    sprintf(len1, "%02X", lenth1);
    sprintf(len2, "%02X", lenth2);
    char full_len[5];
    sprintf(full_len, "%.2s%.2s", len1, len2);
    QString text(full_len);
    QString Head = text + ctrl_zone + "0" + SA_sign + SA + "10";
    qDebug() << "maybe a problem!!!!" << Head;
    BYTE text1[600] = {0};
    Stringlist2Hex(Head, text1);
    unsigned short TempLen = pppfcs16(PPPINITFCS16, text1, (unsigned) Head.length() / 2);
//    unsigned short TempLen = pppfcs16(PPPINITFCS16, text1, );
    char hcs[5];
    sprintf(hcs, "%04X", TempLen);
    QString HCS = message_swap((QString) hcs);
    Head = Head + HCS + apdu;
    BYTE text2[2000] = {0};
    Stringlist2Hex(Head, text2);
    unsigned short TempLen2 = pppfcs16(PPPINITFCS16, text2, (unsigned) Head.length() / 2);
    char fcs[5];
    sprintf(fcs, "%04X", TempLen2);
    QString FCS = message_swap((QString) fcs);
    Head = "68" + Head + FCS + "16";
//    qDebug() << "BuildMessage kankna " << Head;
    return Head;

}

int check(QString a) {
    QStringList list = a.split(' ', QString::SkipEmptyParts);
    if (list.length() < 5) {
        return 2;
    }
    while (true) {
        if (list[0] == "FE")
            list.removeFirst();
        else
            break;
    }

//    qDebug()<<"shuchu"<<(list[2]+ list[1]).toInt(nullptr, 16);
    if (list[0] == "68" and (list.length() >= ((list[2] + list[1]).toInt(nullptr, 16)))) {
        qDebug() << "check granted";
        return 1;
    } else {
        if (list[0] == "68") {
//            qDebug() << "check denied but find 68 with start: " << list;
            return 2;
        } else {
            int temp = list.indexOf("68");
            if (temp == -1)
                return 2;
            qDebug() << "temp " << temp;
            qDebug() << "list" << list;
            while (temp) {
                temp--;
                list.removeFirst();
            }
            QString a2 = list.join(' ');
            if (check(a2) == 1)
                return 1;
            else
                qDebug() << "check denied: " << list;
        }
        return 0;
    }
}

string DtoB(int d) {
    if (d / 2)
        DtoB(d / 2);
    char x[] = {0};
    sprintf(x, "%d", d % 2);
    string a = x;
    return a;
}

string StringAddSpace(string &input) {
    string output = "";
    for (int i = 0; i < input.length(); i += 2) {
        output = output + input[i] + input[i + 1] + ' ';
    }
    return output;
}

QString StringAddSpace(QString &input) {
    QString output = "";
    for (int i = 0; i < input.length(); i += 2) {
        output = output + input[i] + input[i + 1] + ' ';
    }
    qDebug() << "output: " << output;
    return output;
}

int Stringlist2Hex(QString &str, BYTE *pOut) {
    QList<QString> str_list;
    str_list = (StringAddSpace(str)).split(' ');
    int len = str_list.length();
    for (int i = 0; i < len; i++) {
        int qwe = str_list[i].toInt(nullptr, 16);
        pOut[i] = (BYTE) qwe;
    }
    return 0;
}

int Stringlist2Hex_char(QString &str, char *pOut) {
    QList<QString> str_list;
    str_list = StringAddSpace(str).split(' ');
    int len = str_list.length();
    for (int i = 0; i < len; i++) {
        int qwe = str_list[i].toInt(nullptr, 16);
        pOut[i] = qwe;
    }
    return 0;
}

VALUE_LEFT Data_deal(QList<QString> a) {
    int qwe = (a.takeFirst()).toInt(nullptr, 16);
    VALUE_LEFT m;
    switch (qwe) {
        case DATA_ARRAY: {
            (a.takeFirst()).toInt(nullptr, 16);
            return Data_deal(a);
        }
        case DATA_STRUCT : {
            (a.takeFirst()).toInt(nullptr, 16);
            return Data_deal(a);
        }
        case DATA_OCT_STRING: {
            m.value = "";
            int b = (a.takeFirst()).toInt(nullptr, 16);
            for (int i = 0; i < b; i++) {
                m.value = m.value + a.takeFirst();
            }
            m.left = a;
            return m;
        }
        case DATA_UNSIGNED: {
            m.value = a.takeFirst();
            m.left = a;
            return m;
        }
        case DATA_LONG_UNSIGNED: {
            int nu = (a[0] + a[1]).toInt(nullptr, 16);
            m.value = QString::number(nu);
            a.removeFirst();
            a.removeFirst();
            m.left = a;
            return m;
        }
        case DATA_ENUM: {
            m.value = a.takeFirst();
            m.left = a;
            return m;
        }
        case DATA_OAD: {
            m.value = "";
            for (int i = 0; i < 4; i++) {
                m.value = m.value + a.takeFirst();
            }
            m.left = a;
            return m;
        }
        case DATA_TSA: {
            int len = (a.takeFirst()).toInt(nullptr, 16);
            QString tsa = "";
            a.removeFirst();
            for (int i = 1; i < len; i++) {
                tsa = tsa + a.takeFirst();
            }
            m.value = tsa;
            m.left = a;
            return m;
        }
    }
    m.value = "";
    m.left = {""};
    return m;
}

QString re_rever_add() {
    tinyxml2::XMLDocument doc;
    doc.LoadFile("config.xml");
    tinyxml2::XMLElement *root = doc.RootElement();
    tinyxml2::XMLElement *first_child = root->FirstChildElement("revert_add");
    const char *content;
    content = first_child->GetText();
    QString add = QString::fromLocal8Bit(content);
    return add;
}

QString fre(const QString &text) {

    QString t = text.mid(1, 1);
    int value = text.mid(2).toInt(nullptr, 16);
    switch (t.toInt()) {
        case 0:
            return QString("%1%2").arg(QString::number(value), "秒");
        case 1:
            return QString("%1%2").arg(QString::number(value), "分");
        case 2:
            return QString("%1%2").arg(QString::number(value), "时");
        case 3:
            return QString("%1%2").arg(QString::number(value), "日");
        case 4:
            return QString("%1%2").arg(QString::number(value), "月");
        case 5:
            return QString("%1%2").arg(QString::number(value), "年");
        default:
            return "???";
    }
}

QString time_deal(const QString &text) {
    int year = text.mid(2, 4).toInt(nullptr, 16);
    int mouth = text.mid(6, 2).toInt(nullptr, 16);
    int day = text.mid(8, 2).toInt(nullptr, 16);
    int hour = text.mid(10, 2).toInt(nullptr, 16);
    int min = text.mid(12, 2).toInt(nullptr, 16);
    int sec = text.mid(14, 2).toInt(nullptr, 16);

    return QString::number(year) + "-" + QString::number(mouth) + "-" + QString::number(day) + " " +
           QString::number(hour) + ":" +
           QString::number(min) + ":" + QString::number(sec);
}

QString run_style(const QString &text) {
    switch (text.toInt()) {
        case 0:
            return "前闭后开";
        case 1:
            return "前开后闭";
        case 2:
            return "前闭后闭";
        case 3:
            return "前开后开";
        default:
            return "???";
    }

}

QString mision_style(const QString &text) {
    switch (text.toInt()) {
        case 1:
            return "普通采集方案";
        case 2:
            return "事件采集方案";
        case 3:
            return "透明方案";
        case 4:
            return "上报方案";
        case 5:
            return "脚本方案";
        default:
            return "???方案";
    }
}

QString saved_time(const QString &text) {
    switch (text.toInt(nullptr, 16)) {
        case 0:
            return "未定义";
        case 1:
            return "任务开始时间";
        case 2:
            return "相对于当日0点0分";
        case 3:
            return "相对于上日23点59分";
        case 4:
            return "相对于上日0点0分";
        case 5:
            return "相对于当月1日0点0分";
        case 6:
            return "数据冻结时标";
        case 7:
            return "相对于上月月末0点0分";
        default:
            return "???";
    }
}