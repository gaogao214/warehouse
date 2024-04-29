#ifndef SQLTABLEWIDGETSALE_H
#define SQLTABLEWIDGETSALE_H

#include <QSqlQuery>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QObject>
#include <QWidget>
#include <QMetaObject>
#include <QFuture>
#include <QtConcurrent>

#include "profile.h"
#pragma execution_character_set("utf-8");

using namespace sql_struct;

class sqlTableWidgetSale:public QWidget
{
    Q_OBJECT
public:
    sqlTableWidgetSale();

public:
    void addSQLTablewidget(QString name,QString time,int price ,int num,int price_count);

    void SaleSQLTablewidgetShow();
    bool connectSaleSQL();
    void updateTableWidget(int row,QString name,QString time,int price ,int num,int price_count);
    void deleteTableWidget(int rowcur);

    void setSaletableWidgetData(QSqlTableModel* model);
    QSqlTableModel*  getSaleTableWidgetData();

    void searchTableView(QString name);

    void searchSQL(int search_flag);


private:


    QSqlDatabase strorageDb;
    QSqlDatabase saleDb;
    QSqlTableModel *model;
    sql_struct::tableWidget_data data;
    QVector<sql_struct::tableWidget_data> data_vec;
    // QSqlTableModel* data_tablewidget;
    QSqlTableModel* sale_data_tablewidget = nullptr;
};

#endif // SQLTABLEWIDGET_SALE_H
