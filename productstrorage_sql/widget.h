#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QButtonGroup>
#include <QtSql/QSqlDatabase>
#include <QDebug>

#include "product_strorage/product_strorage.h"
#include "product_sale/saleProduct.h"
#include "inventory.h"
#include "earnings.h"
#include "sql_tableview/sqltablewidget.h"

#pragma execution_character_set("utf-8")

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    void initNav();
    void initMain();


private slots:
    void buttonclicked();

    void saveProfile();

private:
    QWidget* navWidget;

    QWidget* mainWidget;
    QStackedWidget* stackedWidget;
    QButtonGroup* btnGroup;

    productStrorage* m_pstrorageProduct = nullptr;
    saleproduct* m_psaleProduct = nullptr;
    earnings* m_pearing = nullptr;
    inventory* m_pinventory = nullptr;


};
#endif // WIDGET_H
