//
// Created by admin on 2020/3/12.
//

#include "SaveLog.h"
#include "ctime"

SaveLog::SaveLog() {
    char buffer[MAX_PATH];
    getcwd(buffer, MAX_PATH);
    std::string address = buffer;
    address.append("\\Log");
    if (0 != access(address.c_str(), 0)){
        mkdir(address.c_str());
        std::cout<<"Create a Log folder\n";
    } else
        std::cout<<"Already have Log\n";
    time_t now = time(0);
    char* dt = ctime(&now);
    write(QString(dt)+'\n');
}

void SaveLog::run() {

}

void SaveLog::write(QString text) {
    std::ofstream oFile;
    oFile.open(".\\Log\\ShowMessage.log",std::ios::app);
    text.append('\n');
    std::string a;
    a = text.toStdString();
    oFile<<a;
}
