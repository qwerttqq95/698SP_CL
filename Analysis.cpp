#include "Analysis.h"

Analysis::Analysis(QString message, QWidget *parent) : QDialog(parent), ui(new Ui::AnalysisDialog)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 3);
    if (message != "")
    {
        ui->textEdit->setText(message);
    }
}

