/********************************************************************************
** Form generated from reading UI file 'CollectionMonitoringClassObject.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLLECTIONMONITORINGCLASSOBJECT_H
#define UI_COLLECTIONMONITORINGCLASSOBJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class COLLECTIONMONITORINGCLASSOBJECTUi_Form
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(647, 465);
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(Form);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton);

        pushButton_3 = new QPushButton(Form);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(Form);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);

        treeWidget = new QTreeWidget(Form);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));

        verticalLayout->addWidget(treeWidget);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "\351\207\207\351\233\206\347\233\221\346\216\247\347\261\273", nullptr));
        pushButton->setText(QCoreApplication::translate("Form", "6012\345\210\206\346\236\220", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Form", "6014\345\210\206\346\236\220", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Form", "601C\345\210\206\346\236\220", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(15, QCoreApplication::translate("Form", "\350\277\220\350\241\214\346\227\266\346\256\265", nullptr));
        ___qtreewidgetitem->setText(14, QCoreApplication::translate("Form", "\344\273\273\345\212\241\350\277\220\350\241\214\347\261\273\345\236\213", nullptr));
        ___qtreewidgetitem->setText(13, QCoreApplication::translate("Form", "\347\212\266\346\200\201", nullptr));
        ___qtreewidgetitem->setText(12, QCoreApplication::translate("Form", "\346\211\247\350\241\214\344\274\230\345\205\210\347\272\247", nullptr));
        ___qtreewidgetitem->setText(11, QCoreApplication::translate("Form", "\345\273\266\346\227\266", nullptr));
        ___qtreewidgetitem->setText(10, QCoreApplication::translate("Form", "\347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
        ___qtreewidgetitem->setText(9, QCoreApplication::translate("Form", "\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        ___qtreewidgetitem->setText(8, QCoreApplication::translate("Form", "\345\255\230\345\202\250\346\227\266\346\240\207", nullptr));
        ___qtreewidgetitem->setText(7, QCoreApplication::translate("Form", "\347\224\265\350\203\275\350\241\250\351\233\206\345\220\210", nullptr));
        ___qtreewidgetitem->setText(6, QCoreApplication::translate("Form", "\344\270\212\346\212\245\347\261\273\345\236\213(601C)", nullptr));
        ___qtreewidgetitem->setText(5, QCoreApplication::translate("Form", "CSD(6014)", nullptr));
        ___qtreewidgetitem->setText(4, QCoreApplication::translate("Form", "\351\207\207\351\233\206\347\261\273\345\236\213(6014)", nullptr));
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("Form", "\346\226\271\346\241\210\347\274\226\345\217\267", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("Form", "\346\226\271\346\241\210\347\261\273\345\236\213", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("Form", "\346\211\247\350\241\214\351\242\221\347\216\207", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("Form", "\344\273\273\345\212\241ID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormCOLLECTIONMONITORINGCLASSOBJECT: public COLLECTIONMONITORINGCLASSOBJECTUi_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLLECTIONMONITORINGCLASSOBJECT_H
