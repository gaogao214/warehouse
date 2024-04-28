#ifndef SQLTABLEWIDGET_H
#define SQLTABLEWIDGET_H

#include <QSqlQuery>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QObject>
#include <QWidget>
#include <QMetaObject>
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
    void SQLTablewidgetShow();
    bool connectSQL();
    void updateTableWidget(int row,QString name,QString time,int price ,int num,int price_count);
    void deleteTableWidget(int rowcur);

    void settableWidgetData(QSqlTableModel* model);
    void setSQLTable(QString name,QString time,int price ,int num,int price_count);
    QSqlTableModel*  getTableWidgetData();

    void searchTableView(QString name);


private:

    QSqlQuery sql_query;
    // QSqlQuery query;
    QSqlDatabase db;

    QStringList names ;


    QStringList clases;
    QSqlQuery query;
    QSqlTableModel *model;



    sql_struct::tableWidget_data data;
    QVector<sql_struct::tableWidget_data> data_vec;

    QSqlTableModel* data_tablewidget;


};

#endif // SQLTABLEWIDGET_H
