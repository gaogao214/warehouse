#ifndef PRODUCTSTRORAGE_H
#define PRODUCTSTRORAGE_H

#include <QWidget>
#include <QLabel>
#include <QObject>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QFuture>

#include "add_product.h"
#include "profile.h"
#include "sql_tableview/sqltablewidget.h"

#pragma execution_character_set("utf-8")

using namespace sql_struct;

class productStrorage:public QWidget
{
    Q_OBJECT
public:
    productStrorage();

signals:
    void sig_flushStrorageTableitem(QSqlTableModel* tablewidget_data);
    void sig_searchSQL(int flag);
private:
    void amendproductTableWidget();//修改
    void removeTableWidget();//删除
    void searchTableWidget();//搜索
    void tableWidgetShow(); //数据库显示在tableview

public:
    void setInventoryData();

private slots:
    void addProductTableWidget();  //添加按钮

private:
    QPushButton* m_pbutton_add = nullptr;//添加产品
    QPushButton* m_pbutton_amend = nullptr;//修改
    QPushButton* m_pbutton_rm = nullptr;//删除
    QPushButton* m_psearch_pushbutton = nullptr;//搜索

    QLineEdit* m_pname_lineedit = nullptr;//商品名称
    QLineEdit* m_pprice_lineedit = nullptr; //入库价格
    QLineEdit* m_pnum_lineedit = nullptr; //入库数量

    QComboBox* m_pdate_combobox = nullptr;//添加日期

    QTableView* m_ptable_strorage = nullptr;//入库表格
    QStandardItemModel* m_pTableViewModel     = nullptr;//tableview 添加模型

    sqlTableWidget* sql_ = nullptr;
    QSqlTableModel* tablewidget_data = nullptr; // 数据库model
    int selete_row = 0;//tableview 选中的行数
    QFuture<void> m_future;
};

#endif // PRODUCTSTRORAGE_H
