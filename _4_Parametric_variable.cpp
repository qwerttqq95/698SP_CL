///参变量(4)

#include "_4_Parametric_variable.h"


_4_Parametric_variable::_4_Parametric_variable(QWidget *parent) : QDialog(parent),
                                                                  ui(new Ui::_4_Parametric_variableForm)
{
    ui->setupUi(this);
    model = new QStandardItemModel(nullptr);
    this->setWindowTitle("参变量");
    ui->treeWidget->setColumnCount(4);
    ui->treeWidget->setHeaderLabels(QStringList() << "标识" << "名称" << "属性" << "只读");
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);


    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("Database.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
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
            qDebug() << QString("OI:%1 Name:%2").arg(detail).arg(sql_query.value(3).toString());
            QTreeWidgetItem *OI = new QTreeWidgetItem(ui->treeWidget);
            OI->setText(0, detail);
            OI->setText(1, sql_query.value(3).toString());
//            OI->setCheckState(0,Qt::Unchecked);
//            OI->setFlags(OI->flags()|Qt::NoItemFlags);
            sql_querychild.exec("select * from oi_attribute where OIID=" + oiid + " ORDER BY AttrNo");
            while (sql_querychild.next())
            {
                QString name = sql_querychild.value(3).toString();
                QString AttNo = sql_querychild.value(2).toString();
                QString RW = sql_querychild.value(5).toString();
                QTreeWidgetItem *OIchild = new QTreeWidgetItem(OI);
                OIchild->setText(1,name);
                OIchild->setText(2,AttNo);
                OIchild->setText(3,RW);
                OIchild->setCheckState(0,Qt::Unchecked);
            }


        }
    }
    database.close();


}

