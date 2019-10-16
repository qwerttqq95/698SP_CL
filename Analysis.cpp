#include "Analysis.h"

Analysis::Analysis(const QString& message, QWidget *parent) : QDialog(parent), ui(new Ui::AnalysisDialog)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 3);
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(removehead()));
    if (message != "")
    {
        text = message;
        ui->textEdit->setText(message);
    }
}

void Analysis::removehead()
{
    auto a = text;
    if (a != "")
    {
        QStringList list = a.split(' ', QString::SkipEmptyParts);
        int message_len = (list[2] + list[1]).toInt(nullptr, 16);  //报文长度
        ui->textEdit_2->append("报文长度: " + QString::number(message_len));
//        int ctrl_zone = list[3].toInt(nullptr, 16); //控制域
//        int SA_len = list[4].toInt(nullptr, 16) & 0xF;
    }

}

