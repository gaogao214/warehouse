#ifndef SALEPRODUCT_H
#define SALEPRODUCT_H
#include <QWidget>
#include <QLabel>
#include <QObject>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include "sql_tableview/sqltablewidget_sale.h"
#include "add_product.h"
#pragma execution_character_set("utf-8");

class saleproduct:public QWidget
{
    Q_OBJECT
public:
    saleproduct();

    void addProductTableWidget();
    void amendproductTableWidget();
    void removeTableWidget();
    void searchTableWidget();
    void tableWidgetShow();
    void setInventoryData();

signals:
    void sig_flushTableitem(QSqlTableModel* tablewidget_data);
    void sig_searchSQL(int flag);
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

    QStandardItemModel* m_pTableViewModel = nullptr;

    QSqlTableModel* tablewidget_data = nullptr; // 数据库model

    sqlTableWidgetSale* sql_sale = nullptr;

    int select_row = 0;
};

#endif // SALEPRODUCT_H
