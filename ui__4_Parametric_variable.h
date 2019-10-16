/********************************************************************************
** Form generated from reading UI file '_4_Parametric_variable.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
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
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class _4_Parametric_variableUi_Form
{
public:
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QTreeView *treeView;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QTreeView *treeView_2;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(653, 506);
        horizontalLayout = new QHBoxLayout(Form);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter = new QSplitter(Form);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setLineWidth(0);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(true);
        splitter->setHandleWidth(0);
        splitter->setChildrenCollapsible(true);
        frame = new QFrame(splitter);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        treeView = new QTreeView(frame);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setFrameShape(QFrame::StyledPanel);
        treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(treeView);

        splitter->addWidget(frame);
        frame_2 = new QFrame(splitter);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        treeView_2 = new QTreeView(frame_2);
        treeView_2->setObjectName(QStringLiteral("treeView_2"));
        treeView_2->setFrameShape(QFrame::StyledPanel);
        treeView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_2->addWidget(treeView_2);

        splitter->addWidget(frame_2);

        horizontalLayout->addWidget(splitter);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class _4_Parametric_variableForm: public _4_Parametric_variableUi_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI__4_PARAMETRIC_VARIABLE_H
