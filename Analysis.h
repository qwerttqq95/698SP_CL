//
// Created by admin on 2019/8/20.
//

#ifndef INC_698SP_CL_ANALYSIS_H
#define INC_698SP_CL_ANALYSIS_H

#include <QDialog>
#include <QDebug>
#include "ui_Analysis.h"

class Analysis : public QDialog
{
Q_OBJECT
public:
    explicit Analysis(const QString& message = "", QWidget *parent = nullptr);

    QString text;


private:
    Ui::AnalysisDialog *ui;

public slots:

    void removehead();
};


#endif //INC_698SP_CL_ANALYSIS_H
