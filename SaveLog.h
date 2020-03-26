//
// Created by admin on 2020/3/12.
//

#ifndef INC_698SP_CL_SAVELOG_H
#define INC_698SP_CL_SAVELOG_H
#include "windows.h"
#include "string"
#include <direct.h>
#include "iostream"
#include "fstream"
#include "QThread"

class SaveLog : public QThread {
Q_OBJECT
public:
    SaveLog();
    void run() override;

    void write(QString);


};


#endif //INC_698SP_CL_SAVELOG_H
