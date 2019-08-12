/********************************************************************************
** Form generated from reading UI file 'UI_MessageCompose.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_MESSAGECOMPOSE_H
#define UI_UI_MESSAGECOMPOSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class MESSAGECOMPOSEFormUi_Form
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_7;
    QPushButton *pushButton_6;
    QPushButton *pushButton;
    QPushButton *pushButton_5;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_8;
    QPushButton *pushButton_4;
    QTextEdit *textEdit;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(769, 592);
        horizontalLayout_2 = new QHBoxLayout(Form);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(Form);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(Form);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lineEdit);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_2 = new QLabel(Form);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBox = new QComboBox(Form);
        comboBox->addItem(QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        tableWidget = new QTableWidget(Form);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setRowCount(0);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(tableWidget);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, 207);
        pushButton_7 = new QPushButton(Form);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        verticalLayout->addWidget(pushButton_7);

        pushButton_6 = new QPushButton(Form);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        verticalLayout->addWidget(pushButton_6);

        pushButton = new QPushButton(Form);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_5 = new QPushButton(Form);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        verticalLayout->addWidget(pushButton_5);

        pushButton_2 = new QPushButton(Form);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(Form);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        pushButton_8 = new QPushButton(Form);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        verticalLayout->addWidget(pushButton_8);

        pushButton_4 = new QPushButton(Form);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);

        textEdit = new QTextEdit(Form);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(19);
        sizePolicy1.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy1);
        textEdit->setMinimumSize(QSize(0, 20));
        textEdit->setSizeIncrement(QSize(1, 23));
        textEdit->setBaseSize(QSize(0, 15));
        QFont font;
        font.setKerning(false);
        textEdit->setFont(font);
        textEdit->setMouseTracking(false);
        textEdit->setTabletTracking(false);
        textEdit->setFocusPolicy(Qt::NoFocus);
        textEdit->setContextMenuPolicy(Qt::NoContextMenu);
        textEdit->setAcceptDrops(false);
        textEdit->setAutoFillBackground(true);
        textEdit->setFrameShape(QFrame::NoFrame);
        textEdit->setFrameShadow(QFrame::Plain);
        textEdit->setReadOnly(true);
        textEdit->setAcceptRichText(false);
        textEdit->setCursorWidth(0);
        textEdit->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout->addWidget(textEdit);


        horizontalLayout_2->addLayout(verticalLayout);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(lineEdit);
        label_2->setBuddy(lineEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(
                QApplication::translate("Form", "\346\267\273\345\212\240\346\226\271\346\241\210", nullptr));
        label->setText(QApplication::translate("Form", "\346\226\271\346\241\210\345\220\215\347\247\260:", nullptr));
        label_2->setText(QApplication::translate("Form", "\344\277\235\345\255\230\344\275\215\347\275\256:", nullptr));
        comboBox->setItemText(0, QApplication::translate("Form", "\346\240\271\347\233\256\345\275\225", nullptr));

        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Form", "\350\257\264\346\230\216", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Form", "APDU", nullptr));
        pushButton_7->setText(QApplication::translate("Form",
                                                      "\346\267\273\345\212\240\345\217\202\346\225\260\345\210\235\345\247\213\345\214\226",
                                                      nullptr));
        pushButton_6->setText(QApplication::translate("Form",
                                                      "\346\267\273\345\212\240\346\225\260\346\215\256\345\210\235\345\247\213\345\214\226",
                                                      nullptr));
        pushButton->setText(
                QApplication::translate("Form", "\346\267\273\345\212\240\345\273\266\346\227\266", nullptr));
        pushButton_5->setText(
                QApplication::translate("Form", "\345\242\236\345\212\240\344\270\200\350\241\214", nullptr));
        pushButton_2->setText(
                QApplication::translate("Form", "\346\217\222\345\205\245\344\270\200\350\241\214", nullptr));
        pushButton_3->setText(
                QApplication::translate("Form", "\345\210\240\351\231\244\345\275\223\345\211\215\350\241\214",
                                        nullptr));
        pushButton_8->setText(
                QApplication::translate("Form", "\346\267\273\345\212\240\345\257\271\346\257\224", nullptr));
        pushButton_4->setText(QApplication::translate("Form", "\345\256\214\346\210\220", nullptr));
        textEdit->setHtml(QApplication::translate("Form",
                                                  "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                                                  "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
                                                  "p, li { white-space: pre-wrap; }\n"
                                                  "</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
                                                  "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                                    </p>\n"
                                                  "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">*\346\212\245\346\226\207\346\257\224\350\276\203:                                    </p>\n"
                                                  "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"> \345\234\250\350\257\264\346\230\216\351\207\214\345\241\253\345\206\231&quot;\346\257\224\350\276\203&quot;,APDU\345\206\205\346\224\276\347\275\256\350\246\201\345\257\271\346\257\224\344"
                                                  "\270\212\344\270\200\346\235\241\347\232\204\350\277\224\345\233\236\347\273\223\346\236\234                                    </p>\n"
                                                  "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                                    </p>\n"
                                                  "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">*\346\263\250\346\204\217:                                    </p>\n"
                                                  "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"> \350\257\264\346\230\216\344\270\215\345\217\257\345\214\205\345\220\253&quot;\345\273\266\346\227\266&quot;&quot;\346\257\224\350\276\203&quot;\347\255\211\345\255\227\346\240\267                                </p></body></html>",
                                                  nullptr));
    } // retranslateUi

};

namespace Ui
{
    class MESSAGECOMPOSEForm : public MESSAGECOMPOSEFormUi_Form
    {
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_MESSAGECOMPOSE_H
