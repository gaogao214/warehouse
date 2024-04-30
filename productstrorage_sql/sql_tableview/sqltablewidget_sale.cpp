#include "sqltablewidget_sale.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlRecord>
// #include <QTableWidget>

#pragma execution_character_set("utf-8");

#define QSQLTABLEMODEL_FLAG

sqlTableWidgetSale::sqlTableWidgetSale()
{

}

void sqlTableWidgetSale::addSQLTablewidget(QString name,QString time,int price ,int num,int price_count)
{
    QSqlRecord record = model->record();
    record.setValue(0,name);//商品名称
    record.setValue(1,time);//添加日期
    record.setValue(2,price);//商品价格
    record.setValue(3,num);//商品数量
    record.setValue(4,price_count);//总价
    model->insertRecord(model->rowCount(), record);//添加至Model
    model->submitAll();//提交

}

void sqlTableWidgetSale::SaleSQLTablewidgetShow()
{
    qDebug()<<"sqlTableWidgetSale::SaleSQLTablewidgetShow()";
    //使用QSqlTableModel 方法
    model = new QSqlTableModel(this,saleDb);

    model->setTable("sale_products");


    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //不显示第二列
    //model->removeColumn(1);

    //查询整张表
    model->select();

    setSaletableWidgetData(model);
}

bool sqlTableWidgetSale::connectSaleSQL()
{
    //这条语句会打印:drivers ("QSQLITE", "QMYSQL", "QMYSQL3", "QODBC", "QODBC3", "QPSQL", "QPSQL7")本地的数据库
    qDebug() << "drivers" << QSqlDatabase::drivers();
    //======================================👇创建数据库==========================================================
    // 加载驱动：这里的驱动必须是上一句打印里面的完全一样，必须是大写，不然会报错：QSqlDatabase: QSQLITE driver not loaded
    saleDb = QSqlDatabase::addDatabase("QSQLITE","sqlite1");

    saleDb.setDatabaseName("./productSaleDB.db"); // 建立链接（链接一个数据库文件）
     qDebug()<<"sale_connectionName:"<<saleDb.connectionName();

    if(!saleDb.open())
    {
        return false;
        qDebug()<<"Error: Failed to connect database." << saleDb.lastError();
    }else
    {
        // sql_query.exec("DROP TABLE sale_products");        //先清空一下表
        QSqlQuery sql_query(saleDb);
        //创建一个students表,标题分别为id、name、score、class
        sql_query.exec("CREATE TABLE sale_products ("
                       u8"商品名称 VARCHAR(40) NOT NULL, "
                       u8"出库时间 VARCHAR(40) NOT NULL, "
                       u8"售价 INTEGER NOT NULL, "
                       u8"数量 INTEGER NOT NULL,"
                       u8"总价 INTEGER NOT NULL)");
        //创建一个students表
        //========================================👆清空数据库－》创建student表========================================================
        qDebug() << "Succeed to connect database sale_products." ;

        return true;
    }
}

//修改
void sqlTableWidgetSale::updateTableWidget(int row,QString name,QString time,int price ,int num,int price_count)
{
    // if(name.isEmpty() || tatal <= 0)
    // {
    //     QMessageBox::information(this,"提示","修改失败,数据为空");
    //     return;
    // }

    // int curRow = tableView->currentIndex().row();
    qDebug()<<"row:"<<row;
    QSqlRecord record = model->record(row);
    record.setValue(0,name);
    record.setValue(1,time);
    record.setValue(2,price);
    record.setValue(3,num);
    record.setValue(4,price_count);


    if(model->setRecord(row, record))
    {
        model->submitAll();
    }

}

//删除选中行
void sqlTableWidgetSale::deleteTableWidget(int rowcur)
{
    //使用QSqlTableModel 方法
    model->removeRow(rowcur);
    model->submitAll(); //否则提交，在数据库中删除改行
}

void sqlTableWidgetSale::setSaletableWidgetData(QSqlTableModel* model)
{
    sale_data_tablewidget = new QSqlTableModel(this);
    sale_data_tablewidget = model;
}

QSqlTableModel*  sqlTableWidgetSale::getSaleTableWidgetData()
{
    return sale_data_tablewidget;
}

//搜索
void sqlTableWidgetSale::searchTableView(QString name)
{
    QString product_name =  QString(u8"商品名称 = '%1'").arg(name);
    // QString date = QString("date = '%1'").arg(dateEdit->date().toString("yyyy-MM-dd"));
    QString strFilter = "";
    if(!name.isEmpty())
    {
        strFilter.append(product_name);
    }
    //如需要日期查询请取消注释
    //    if(!dateEdit->text().isEmpty())
    //    {
    //        if(!strFilter.isEmpty())
    //        {
    //            strFilter.append(" and ");
    //        }
    //        strFilter.append(date);
    //    }
    model->setFilter(strFilter);
    // ui->tableView->setModel(model);
    model->select();
    setSaletableWidgetData(model);
}

void sqlTableWidgetSale::searchSQL()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        connectSaleSQL();//连接不存在需要创建连接，添加数据库
    }
    else
    {
        connectSaleSQL();//连接不存在需要创建连接，添加数据库
    }
    SaleSQLTablewidgetShow();

}



