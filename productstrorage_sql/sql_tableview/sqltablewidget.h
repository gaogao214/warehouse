#ifndef SQLTABLEWIDGET_H
#define SQLTABLEWIDGET_H

#include <QSqlQuery>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QObject>
#include <QWidget>
#include <QMetaObject>
#include <QFuture>
#include <QtConcurrent>

#pragma execution_character_set("utf-8");

#include "profile.h"
using namespace sql_struct;

class sqlTableWidget:public QWidget
{
    Q_OBJECT
public:
    sqlTableWidget();

public:
    void addSQLTablewidget(QString name,QString time,int price ,int num,int price_count);
    void StrorageSQLTablewidgetShow();
    bool connectStrorageSQL();
    void updateTableWidget(int row,QString name,QString time,int price ,int num,int price_count);
    void deleteTableWidget(int rowcur);

    void settableWidgetData(QSqlTableModel* model);
    QSqlTableModel*  getTableWidgetData();

    void searchTableView(QString name);

    void searchSQL();


private:


    QSqlDatabase strorageDb;
    QSqlDatabase saleDb;
    QSqlTableModel *model;
    sql_struct::tableWidget_data data;
    QVector<sql_struct::tableWidget_data> data_vec;
    QSqlTableModel* data_tablewidget;
    // QSqlTableModel* sale_data_tablewidget;

    QFuture<void> m_future;


};

#endif // SQLTABLEWIDGET_H
