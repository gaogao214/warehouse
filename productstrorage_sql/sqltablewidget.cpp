#include "sqltablewidget.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QTableWidget>

#pragma execution_character_set("utf-8");

sqlTableWidget::sqlTableWidget()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
          db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
          // db = QSqlDatabase::addDatabase("QSQLITE");
        connectSQL();
    }
    searchSQLTablewidget();
}

void sqlTableWidget::addSQLTablewidget(QString name,QString time,int price ,int num,int price_count)
{
    //========================================👇清空数据库－》创建student表========================================================
    QSqlQuery query;
    QSqlQuery sql_query;
    // query.exec("DROP TABLE students");        //先清空一下表
    //创建一个students表,标题分别为id、name、score、class
    query.exec("CREATE TABLE students ("
               u8"商品名称 VARCHAR(40) NOT NULL, "
               u8"入库时间 VARCHAR(40) NOT NULL, "
               u8"入库价格 INTEGER NOT NULL, "
               u8"入库数量 INTEGER NOT NULL,"
               u8"入库总价 INTEGER NOT NULL)");
    //创建一个students表
    //========================================👆清空数据库－》创建student表========================================================
    //========================================👇插入表=======================================================================
    query.prepare(u8"INSERT INTO students (商品名称, 入库时间, 入库价格,入库数量,入库总价) "
                  "VALUES (:name, :time, :price, :num, :pricecount)");
    //为每一列标题添加绑定值
    query.bindValue(":name", name);                  //向绑定值里加入时间
    query.bindValue(":time", time);                  //向绑定值里加入时间
    query.bindValue(":price", price);                     //入库价格
    query.bindValue(":num", num );    //入库数量
    query.bindValue(":pricecount", price_count );                //入库总价
    query.exec();               //加入库中
}

void sqlTableWidget::searchSQLTablewidget()
{
    QSqlQuery sql_query;
    // qDebug()<<tr("database connection name:%1").arg(db.connectionName());
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db = QSqlDatabase::database("qt_sql_default_connection");
        qDebug()<<u8"存在";
        //查询
        sql_query.exec("select * from students;");

        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            while(sql_query.next())
            {
                data.name = sql_query.value(0).toInt();
                data.time = sql_query.value(1).toString();
                data.price = sql_query.value(2).toInt();
                data.num = sql_query.value(3).toInt();
                data.price_count = sql_query.value(4).toInt();

                data_vec.push_back(data);
                qDebug()<<" ; NAME = "<<data.name <<" ; time = "<<data.time<<" ; price = "<<data.price<<" ; num = "<<data.num<<" ; price_count = "<<data.price_count;
            }

            settableWidgetData(data_vec);
        }
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }
}

bool sqlTableWidget::connectSQL()
{
    //这条语句会打印:drivers ("QSQLITE", "QMYSQL", "QMYSQL3", "QODBC", "QODBC3", "QPSQL", "QPSQL7")本地的数据库
    qDebug() << "drivers" << QSqlDatabase::drivers();
    //======================================👇创建数据库==========================================================
    // 加载驱动：这里的驱动必须是上一句打印里面的完全一样，必须是大写，不然会报错：QSqlDatabase: QSQLITE driver not loaded
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery sql_query;

    db.setDatabaseName("./StudentDB.db"); // 建立链接（链接一个数据库文件）
    if(!db.open())
    {
        return false;
        qDebug()<<"Error: Failed to connect database." << db.lastError();
    }else
    {
        return true;
        qDebug() << "Succeed to connect database." ;
    }
}

//修改
void sqlTableWidget::updateTableWidget(QString name,QString time,int price ,int num,int price_count)
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
            db = QSqlDatabase::database("qt_sql_default_connection");

            QSqlQuery query(db);
            if(query.exec(QString("update students set 时间='%1' ,价格='%2',数量='%3',总价= '%4' where 商品名称=%5")
                               .arg(time).arg(price).arg(num).arg(price_count).arg(name)))
            {
                qDebug("update data success");
            }
            else
            {
                qDebug()<<"error"<<query.lastError();
            }
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }

}

//删除选中行
void sqlTableWidget::deleteTableWidget(int rowcur)
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db = QSqlDatabase::database("qt_sql_default_connection");

        QSqlQuery query(db);

        if(query.exec(QString("delete from students where  id='%1'")//删除所在行
                           .arg(rowcur+1)))
        {
            qDebug("delete data success!");
        }
        else
        {
            qDebug()<<"error"<<query.lastError();
        }
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }

}

void sqlTableWidget::settableWidgetData(QVector<tableWidget_data> data)
{
    data_tablewidget = data;
}

QVector<tableWidget_data> sqlTableWidget::getTableWidgetData()
{
    return data_tablewidget;
}



