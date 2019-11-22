/********************************************************************************
** Form generated from reading UI file 'CollectionMonitoringClassObject.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
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

class Ui_FormCOLLECTIONMONITORINGCLASSOBJECT
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(647, 465);
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(Form);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        treeWidget = new QTreeWidget(Form);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        verticalLayout->addWidget(treeWidget);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "\351\207\207\351\233\206\347\233\221\346\216\247\347\261\273", nullptr));
        pushButton->setText(QApplication::translate("Form", "\347\273\274\345\220\210\345\210\206\346\236\220", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(10, QApplication::translate("Form", "\350\277\220\350\241\214\346\227\266\346\256\265", nullptr));
        ___qtreewidgetitem->setText(9, QApplication::translate("Form", "\344\273\273\345\212\241\350\277\220\350\241\214\347\261\273\345\236\213", nullptr));
        ___qtreewidgetitem->setText(8, QApplication::translate("Form", "\347\212\266\346\200\201", nullptr));
        ___qtreewidgetitem->setText(7, QApplication::translate("Form", "\346\211\247\350\241\214\344\274\230\345\205\210\347\272\247", nullptr));
        ___qtreewidgetitem->setText(6, QApplication::translate("Form", "\345\273\266\346\227\266", nullptr));
        ___qtreewidgetitem->setText(5, QApplication::translate("Form", "\347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
        ___qtreewidgetitem->setText(4, QApplication::translate("Form", "\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        ___qtreewidgetitem->setText(3, QApplication::translate("Form", "\346\226\271\346\241\210\347\274\226\345\217\267", nullptr));
        ___qtreewidgetitem->setText(2, QApplication::translate("Form", "\346\226\271\346\241\210\347\261\273\345\236\213", nullptr));
        ___qtreewidgetitem->setText(1, QApplication::translate("Form", "\346\211\247\350\241\214\351\242\221\347\216\207", nullptr));
        ___qtreewidgetitem->setText(0, QApplication::translate("Form", "\344\273\273\345\212\241ID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormCOLLECTIONMONITORINGCLASSOBJECT: public Ui_FormCOLLECTIONMONITORINGCLASSOBJECT {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLLECTIONMONITORINGCLASSOBJECT_H
