/********************************************************************************
** Form generated from reading UI file '_4_Parametric_variable.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI__4_PARAMETRIC_VARIABLE_H
#define UI__4_PARAMETRIC_VARIABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class _4_Parametric_variableForm2
{
public:
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_4;
    QSplitter *splitter;
    QTreeWidget *treeWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QFrame *line;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QSpacerItem *horizontalSpacer;
    QTreeWidget *treeWidget_2;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter_2;
    QTreeWidget *treeWidget_3;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_2;
    QTreeWidget *treeWidget_4;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(620, 446);
        horizontalLayout = new QHBoxLayout(Form);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(Form);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_4 = new QHBoxLayout(tab);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        splitter = new QSplitter(tab);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        treeWidget = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy);
        treeWidget->setMaximumSize(QSize(275, 16777215));
        treeWidget->setSizeIncrement(QSize(0, 0));
        treeWidget->setBaseSize(QSize(0, 0));
        treeWidget->setProperty("showDropIndicator", QVariant(false));
        splitter->addWidget(treeWidget);
        treeWidget->header()->setMinimumSectionSize(15);
        treeWidget->header()->setDefaultSectionSize(25);
        treeWidget->header()->setHighlightSections(false);
        treeWidget->header()->setProperty("showSortIndicator", QVariant(false));
        treeWidget->header()->setStretchLastSection(false);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2->setContentsMargins(0, -1, 0, -1);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setMaximumSize(QSize(40, 16777215));
        pushButton->setIconSize(QSize(11, 16));
        pushButton->setAutoDefault(false);
        pushButton->setFlat(true);

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setMaximumSize(QSize(40, 16777215));
        pushButton_2->setFlat(true);

        horizontalLayout_2->addWidget(pushButton_2);

        line = new QFrame(layoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        sizePolicy1.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy1);
        pushButton_4->setMaximumSize(QSize(57, 16777215));
        pushButton_4->setFlat(true);

        horizontalLayout_2->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(layoutWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        sizePolicy1.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy1);
        pushButton_5->setMaximumSize(QSize(57, 16777215));
        pushButton_5->setFlat(true);

        horizontalLayout_2->addWidget(pushButton_5);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        treeWidget_2 = new QTreeWidget(layoutWidget);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QString::fromUtf8("1"));
        treeWidget_2->setHeaderItem(__qtreewidgetitem1);
        treeWidget_2->setObjectName(QString::fromUtf8("treeWidget_2"));
        treeWidget_2->setAlternatingRowColors(true);
        treeWidget_2->setTextElideMode(Qt::ElideMiddle);
        treeWidget_2->setAllColumnsShowFocus(true);

        verticalLayout->addWidget(treeWidget_2);

        splitter->addWidget(layoutWidget);

        horizontalLayout_4->addWidget(splitter);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        splitter_2 = new QSplitter(tab_2);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        treeWidget_3 = new QTreeWidget(splitter_2);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem();
        __qtreewidgetitem2->setText(0, QString::fromUtf8("1"));
        treeWidget_3->setHeaderItem(__qtreewidgetitem2);
        treeWidget_3->setObjectName(QString::fromUtf8("treeWidget_3"));
        sizePolicy.setHeightForWidth(treeWidget_3->sizePolicy().hasHeightForWidth());
        treeWidget_3->setSizePolicy(sizePolicy);
        treeWidget_3->setMaximumSize(QSize(275, 16777215));
        treeWidget_3->setSizeIncrement(QSize(0, 0));
        treeWidget_3->setBaseSize(QSize(0, 0));
        treeWidget_3->setProperty("showDropIndicator", QVariant(false));
        splitter_2->addWidget(treeWidget_3);
        treeWidget_3->header()->setMinimumSectionSize(15);
        treeWidget_3->header()->setDefaultSectionSize(25);
        treeWidget_3->header()->setHighlightSections(false);
        treeWidget_3->header()->setProperty("showSortIndicator", QVariant(false));
        treeWidget_3->header()->setStretchLastSection(false);
        layoutWidget1 = new QWidget(splitter_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_3->setContentsMargins(0, -1, 0, -1);
        pushButton_3 = new QPushButton(layoutWidget1);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);
        pushButton_3->setAutoDefault(false);
        pushButton_3->setFlat(true);

        horizontalLayout_3->addWidget(pushButton_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        treeWidget_4 = new QTreeWidget(layoutWidget1);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem();
        __qtreewidgetitem3->setText(0, QString::fromUtf8("1"));
        treeWidget_4->setHeaderItem(__qtreewidgetitem3);
        treeWidget_4->setObjectName(QString::fromUtf8("treeWidget_4"));

        verticalLayout_2->addWidget(treeWidget_4);

        splitter_2->addWidget(layoutWidget1);

        verticalLayout_3->addWidget(splitter_2);

        tabWidget->addTab(tab_2, QString());

        horizontalLayout->addWidget(tabWidget);


        retranslateUi(Form);

        tabWidget->setCurrentIndex(0);
        pushButton->setDefault(false);
        pushButton_3->setDefault(false);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("Form", "\350\257\273\345\217\226", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Form", "\350\256\276\347\275\256", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Form", "\345\217\226\346\266\210\345\213\276\351\200\211", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Form", "\346\270\205\347\251\272\345\213\276\351\200\211", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Form", "\345\261\236\346\200\247", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Form", "\346\223\215\344\275\234", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Form", "\346\226\271\346\263\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class _4_Parametric_variableForm: public _4_Parametric_variableForm2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI__4_PARAMETRIC_VARIABLE_H
