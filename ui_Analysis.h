/********************************************************************************
** Form generated from reading UI file 'Analysis.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYSIS_H
#define UI_ANALYSIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class AnalysisUi_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(652, 494);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        splitter = new QSplitter(Dialog);
        splitter->setObjectName(QStringLiteral("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setFrameShape(QFrame::NoFrame);
        splitter->setFrameShadow(QFrame::Sunken);
        splitter->setLineWidth(1);
        splitter->setMidLineWidth(18);
        splitter->setOrientation(Qt::Vertical);
        splitter->setHandleWidth(5);
        textEdit = new QTextEdit(splitter);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy1);
        textEdit->setMinimumSize(QSize(0, 10));
        textEdit->setSizeIncrement(QSize(0, 10));
        textEdit->setBaseSize(QSize(0, 10));
        textEdit->setTabChangesFocus(true);
        textEdit->setHtml(QLatin1String(
                "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
                "p, li { white-space: pre-wrap; }\n"
                "</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
                "<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>"));
        textEdit->setAcceptRichText(false);
        splitter->addWidget(textEdit);
        textEdit_2 = new QTextEdit(splitter);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(2);
        sizePolicy2.setHeightForWidth(textEdit_2->sizePolicy().hasHeightForWidth());
        textEdit_2->setSizePolicy(sizePolicy2);
        textEdit_2->setMinimumSize(QSize(0, 140));
        textEdit_2->setSizeIncrement(QSize(0, 140));
        textEdit_2->setBaseSize(QSize(0, 140));
        textEdit_2->setReadOnly(true);
        splitter->addWidget(textEdit_2);

        verticalLayout->addWidget(splitter);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(
                QApplication::translate("Dialog", "\346\212\245\346\226\207\350\247\243\346\236\220", nullptr));
    } // retranslateUi

};

namespace Ui
{
    class AnalysisDialog : public AnalysisUi_Dialog
    {
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYSIS_H
