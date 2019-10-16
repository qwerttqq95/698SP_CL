#include <string>
#include <QString>
#include <QtCore/QStringList>
#include <QDebug>
#include <MeterArchives.h>
#include <mainwindow.h>
#include <windows.h>
#include <vector>
#include "io.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


#define PPPINITFCS16 0xffff

using namespace std;

void getDir(string path, vector<string> &files)
{
    long hFile = 0;
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                {
                    files.push_back(p.assign(path).append("/").append(fileinfo.name));
                    getDir(p.assign(path).append("/").append(fileinfo.name), files);
                }
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

int Stringlist2Hex(QString &str, BYTE *pOut);

QString message_swap(const QString &a)
{
    QList<QString> list;
    for (int i = 0; i <= a.length() / 2; i += 2)
    {
        list.append(a.mid(i, i + 2));
    }
    QString re = "";
    for (int y = list.length() - 1; y >= 0; y--)
    {
        re = re + list[y];
    }
    return re;
}

int String2Hex(string &str, BYTE *pOut, DWORD *pLenOut, DWORD nMaxLen)
{
    int i, j = 0;
    DWORD len;
    TCHAR x;
    for (i = 0, x = 0, len = 0;
         i < (int) str.length() && len < (int) nMaxLen;
         i++)
    {
        if (j >= 2)
        {
            pOut[len++] = (BYTE) x;
            x = 0;
            j = 0;
        }
        if (str[i] >= '0' && str[i] <= '9')
        {
            x <<= 4;
            x |= str[i] - '0';
            j++;
        } else if ((str[i] >= 'A' && str[i] <= 'F')
                   || (str[i] >= 'a' && str[i] <= 'f'))
        {
            x <<= 4;
            x |= _toupper (str[i]) - 'A' + 10;
            j++;
        } else if (j)
        {
            pOut[len++] = (BYTE) x;
            x = 0;
            j = 0;
        }
    }
    if (j)
    {
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

unsigned short pppfcs16(unsigned short fcs, unsigned char *p, unsigned int len)
{
    while (len--)
    {
        fcs = (fcs >> 8) ^ fcstab[(fcs ^ *p++) & 0xff];
    }
    return (fcs ^ 0xffff);
}

void BtoD(int a, int *b)
{
    *b = 0;
    while (a--)
    {
        *b *= 2;
        *b += getchar() - '0';
    }

}

QString DARType(int a)
{
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("Database.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    QSqlQuery sql_query;
    sql_query.exec("select * from dar where Number= " + QString::number(a));
    if (!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    } else
    {
        sql_query.next();
        QString detail = sql_query.value(0).toString();
        qDebug() << QString("detail:%1").arg(detail);
        return detail;
    }

}

QString BuildMessage(QString apdu, const QString& SA, const QString& ctrl_zone)
{
    qDebug() << "apdu:"<<apdu;
    qDebug() << "SA:"<<SA;
    qDebug() << "ctrl_zone:"<<ctrl_zone;
    apdu.remove(' ');
//    qDebug() << "apdu" << apdu;
    int len = SA.length() / 2 - 1;
    if (len == -1)
    {
        qDebug() << "BuildMessage 1 error";
        return "0";
    }
    QString SA_sign = QString("%1").arg(len);
    int apdu_len = apdu.length() / 2;
    int Total_length = 10 + len + apdu_len;
    int lenth1 = Total_length & 0x00ff;
    int lenth2 = Total_length >> 8;
    char len1[3] = {'0', '0'};
    char len2[3] = {'0', '0'};
    sprintf(len1, "%02X", lenth1);
    sprintf(len2, "%02X", lenth2);
    char full_len[4];
    sprintf(full_len, "%.2s%.2s", len1, len2);
    QString text(full_len);
    QString Head = text + ctrl_zone + "0" + SA_sign + SA + "10";
    BYTE text1[600] = {0};
    Stringlist2Hex(Head, text1);
    unsigned short TempLen = pppfcs16(PPPINITFCS16, text1, (unsigned) Head.length() / 2);
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

int check(QString a)
{
    QStringList list = a.split(' ', QString::SkipEmptyParts);
    if (list.length() < 5)
    {
        return 2;
    }
    while (1)
    {
        if (list[0] == "FE")
            list.removeFirst();
        else
            break;
    }

//    qDebug()<<"shuchu"<<(list[2]+ list[1]).toInt(nullptr, 16);
    if (list[0] == "68" and (list.length() >= ((list[2] + list[1]).toInt(nullptr, 16))))
    {
        qDebug() << "check granted";
        return 1;
    } else
    {
        if (list[0] == "68")
        {
//            qDebug() << "check denied but find 68 with start: " << list;
            return 2;
        } else
        {
            int temp = list.indexOf("68");
            if (temp == -1)
                return 2;
            qDebug() << "temp " << temp;
            qDebug() << "list" << list;
            while (temp)
            {
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

string DtoB(int d)
{
    if (d / 2)
        DtoB(d / 2);
    char x[] = {0};
    sprintf(x, "%d", d % 2);
    string a = x;
    return a;
}


string StringAddSpace(string &input)
{
    string output = "";
    for (int i = 0; i < input.length(); i += 2)
    {
        output = output + input[i] + input[i + 1] + ' ';
    }
    return output;
}

QString StringAddSpace(QString &input)
{
    QString output = "";
    for (int i = 0; i < input.length(); i += 2)
    {
        output = output + input[i] + input[i + 1] + ' ';
    }
    return output;
}

int Stringlist2Hex(QString &str, BYTE *pOut)
{
    QList<QString> str_list;
    str_list = StringAddSpace(str).split(' ');
    int len = str_list.length();
    for (int i = 0; i < len; i++)
    {
        int qwe = str_list[i].toInt(nullptr, 16);
        pOut[i] = (BYTE) qwe;
    }
    return 0;
}

int Stringlist2Hex_char(QString &str, char *pOut)
{
    QList<QString> str_list;
    str_list = StringAddSpace(str).split(' ');
    int len = str_list.length();
    for (int i = 0; i < len; i++)
    {
        int qwe = str_list[i].toInt(nullptr, 16);
        pOut[i] = qwe;
    }
    return 0;
}

VALUE_LEFT Data_deal(QList<QString> a)
{
    int qwe = (a.takeFirst()).toInt(nullptr, 16);
    VALUE_LEFT m;
    switch (qwe)
    {
        case DATA_ARRAY:
        {
            (a.takeFirst()).toInt(nullptr, 16);
            return Data_deal(a);
        }
        case DATA_STRUCT :
        {
            (a.takeFirst()).toInt(nullptr, 16);
            return Data_deal(a);
        }
        case DATA_OCT_STRING:
        {
            m.value = "";
            int b = (a.takeFirst()).toInt(nullptr, 16);
            for (int i = 0; i < b; i++)
            {
                m.value = m.value + a.takeFirst();
            }
            m.left = a;
            return m;
        }
        case DATA_UNSIGNED:
        {
            m.value = a.takeFirst();
            m.left = a;
            return m;
        }
        case DATA_LONG_UNSIGNED:
        {
            int nu = (a[0] + a[1]).toInt(nullptr, 16);
            m.value = QString::number(nu);
            a.removeFirst();
            a.removeFirst();
            m.left = a;
            return m;
        }
        case DATA_ENUM:
        {
            m.value = a.takeFirst();
            m.left = a;
            return m;
        }
        case DATA_OAD:
        {
            m.value = "";
            for (int i = 0; i < 4; i++)
            {
                m.value = m.value + a.takeFirst();
            }
            m.left = a;
            return m;
        }
        case DATA_TSA:
        {
            int len = (a.takeFirst()).toInt(nullptr, 16);
            QString tsa = "";
            a.removeFirst();
            for (int i = 1; i < len; i++)
            {
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

//
//QString return_current_time()
//{
//    time_t timep;
//    time(&timep);
//    char tmp[64];
//    strftime(tmp, sizeof(tmp), "%Y%m%d%H%M%S00", localtime(&timep));
//    QString x = tmp;
//
//}

QString re_rever_add()
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile("config.xml");
    tinyxml2::XMLElement *root = doc.RootElement();
    tinyxml2::XMLElement *first_child = root->FirstChildElement("revert_add");
    const char *content;
    content = first_child->GetText();
    QString add = QString::fromLocal8Bit(content);
    return add;
}
