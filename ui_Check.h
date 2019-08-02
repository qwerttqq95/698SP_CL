/********************************************************************************
** Form generated from reading UI file 'Check.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECK_H
#define UI_CHECK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class CheckDialogUi_Form
{
public:
    QHBoxLayout *horizontalLayout;
    QTreeView *treeView;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_5;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QPushButton *pushButton_6;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(739, 449);
        horizontalLayout = new QHBoxLayout(Form);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        treeView = new QTreeView(Form);
        treeView->setObjectName(QStringLiteral("treeView"));

        horizontalLayout->addWidget(treeView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 250);
        pushButton_5 = new QPushButton(Form);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        verticalLayout->addWidget(pushButton_5);

        pushButton_2 = new QPushButton(Form);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_4 = new QPushButton(Form);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(Form);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        pushButton = new QPushButton(Form);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_6 = new QPushButton(Form);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        verticalLayout->addWidget(pushButton_6);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form",
                                                     "\350\207\252\345\256\232\344\271\211\346\265\213\350\257\225\346\226\271\346\241\210",
                                                     nullptr));
        pushButton_5->setText(QApplication::translate("Form", "\345\210\267\346\226\260", nullptr));
        pushButton_2->setText(
                QApplication::translate("Form", "\346\267\273\345\212\240\346\226\271\346\241\210", nullptr));
        pushButton_4->setText(QApplication::translate("Form",
                                                      "\346\237\245\347\234\213\351\200\211\344\270\255\346\226\271\346\241\210",
                                                      nullptr));
        pushButton_3->setText(QApplication::translate("Form",
                                                      "\345\210\240\351\231\244\351\200\211\344\270\255\346\226\271\346\241\210",
                                                      nullptr));
        pushButton->setText(QApplication::translate("Form",
                                                    "\344\270\213\345\217\221\351\200\211\344\270\255\346\226\271\346\241\210",
                                                    nullptr));
        pushButton_6->setText(
                QApplication::translate("Form", "\347\273\210\346\255\242\344\270\213\345\217\221", nullptr));
    } // retranslateUi

};

namespace Ui
{
    class CheckDialog : public CheckDialogUi_Form
    {
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECK_H
