///参变量(4)

#include "_4_Parametric_variable.h"

_4_Parametric_variable::_4_Parametric_variable(QWidget *parent) : QDialog(parent),
                                                                  ui(new Ui::_4_Parametric_variableForm)
{
    ui->setupUi(this);
    model = new QStandardItemModel(nullptr);
    this->setWindowTitle("参变量");
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("Database.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    att();
    act();
    ui->treeWidget_2->setColumnCount(7);
    ui->treeWidget_2->setHeaderLabels(QStringList() << "数据名称" << "属性" << "数值" << "数据类型" << "小数" << "单位" << "备注");
    ui->treeWidget_2->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->treeWidget_4->setColumnCount(7);
    ui->treeWidget_4->setHeaderLabels(QStringList() << "数据名称" << "属性" << "数值" << "数据类型" << "小数" << "单位" << "备注");
    ui->treeWidget_4->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    Item_box = {};
}

void _4_Parametric_variable::att()
{
    ui->treeWidget->setColumnCount(4);
    ui->treeWidget->setHeaderLabels(QStringList() << "标识" << "名称" << "属性" << "读写");
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    QSqlQuery sql_query;
    QSqlQuery sql_querychild;
    sql_query.exec("select * from oi_des where OITypeID=5 ");
    if (!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    } else
    {
        while (sql_query.next())
        {
            QString oiid = sql_query.value(0).toString();
            QString detail = sql_query.value(2).toString();
            QTreeWidgetItem *OI = new QTreeWidgetItem(ui->treeWidget);
            OI->setText(0, detail);
            OI->setText(1, sql_query.value(3).toString());
            sql_querychild.exec("select * from oi_attribute where OIID=" + oiid + " ORDER BY AttrNo");
            while (sql_querychild.next())
            {
                QString name = sql_querychild.value(3).toString();
                QString AttNo = sql_querychild.value(2).toString();
                QString RW = sql_querychild.value(5).toString();
                QTreeWidgetItem *OIchild = new QTreeWidgetItem(OI);
                OIchild->setText(1, name);
                OIchild->setText(2, AttNo);
                OIchild->setText(3, RW);
                OIchild->setCheckState(0, Qt::Unchecked);
            }
        }
    }
    connect(ui->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem * , int)), this,
            SLOT(add_item(QTreeWidgetItem * , int)));

    connect(ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem * , QTreeWidgetItem * )),
            this, SLOT(add_item(QTreeWidgetItem * , QTreeWidgetItem * )));
}

void _4_Parametric_variable::act()
{
    ui->treeWidget_3->setColumnCount(3);
    ui->treeWidget_3->setHeaderLabels(QStringList() << "标识" << "名称" << "方法");
    ui->treeWidget_3->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    QSqlQuery sql_query;
    QSqlQuery sql_querychild;
    sql_query.exec("select * from oi_des where OITypeID=5 ");
    if (!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    } else
    {
        while (sql_query.next())
        {
            QString oiid = sql_query.value(0).toString();
            QString detail = sql_query.value(2).toString();
            QTreeWidgetItem *OI = new QTreeWidgetItem(ui->treeWidget_3);
            OI->setText(0, detail);
            OI->setText(1, sql_query.value(3).toString());
            sql_querychild.exec("select * from oi_action where OIID=" + oiid + " ORDER BY ActionNo");
            while (sql_querychild.next())
            {
                QString name = sql_querychild.value(3).toString();
                QString AttNo = sql_querychild.value(2).toString();
                QString RW = sql_querychild.value(5).toString();
                QTreeWidgetItem *OIchild = new QTreeWidgetItem(OI);
                OIchild->setText(1, name);
                OIchild->setText(2, AttNo);
                OIchild->setText(3, RW);
                OIchild->setCheckState(0, Qt::Unchecked);
            }
        }
    }
    connect(ui->treeWidget_3, SIGNAL(itemChanged(QTreeWidgetItem * , int)), this,
            SLOT(add_item(QTreeWidgetItem * , int)));

    connect(ui->treeWidget_3, SIGNAL(currentItemChanged(QTreeWidgetItem * , QTreeWidgetItem * )),
            this, SLOT(add_item(QTreeWidgetItem * , QTreeWidgetItem * )));
}

void _4_Parametric_variable::add_item(QTreeWidgetItem *item, int pos)
{
    deal_box_att(item);

}

void _4_Parametric_variable::deal_box_att(QTreeWidgetItem *item)
{
    PARAMETRIC *need_del = nullptr;
    int i = -1;
            foreach(auto x, Item_box)
        {
            i += 1;
            if (x.left == item)
            {
                flag = true;
                need_del = &x;
                break;
            }
        }
    if (!flag)
    {
        auto newitem = new QTreeWidgetItem(ui->treeWidget_2);
        newitem->setText(0, item->parent()->text(0) + " " + item->parent()->text(1));
        newitem->setText(1, item->text(2));
        newitem->setCheckState(0, Qt::Checked);
        PARAMETRIC new_m_itembox;
        new_m_itembox.left = item;
        new_m_itembox.right = newitem;
        Item_box.append(new_m_itembox);

    } else
    {
        delete need_del->right;
        delete need_del;
        Item_box.removeAt(i);
        flag = false;
    }
}


void _4_Parametric_variable::add_item(QTreeWidgetItem *item, QTreeWidgetItem *item2)
{
    if (item->parent())
    {
        if (item->checkState(0) == Qt::Checked)
            item->setCheckState(0, Qt::Unchecked);
        else
        {
            item->setCheckState(0, Qt::Checked);
        }
    }

}

