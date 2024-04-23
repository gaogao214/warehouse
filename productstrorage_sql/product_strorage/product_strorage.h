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

#include "add_product.h"
#include "profile.h"
#include "sqltablewidget.h"

#pragma execution_character_set("utf-8")

using namespace sql_struct;

class productStrorage:public QWidget
{
    Q_OBJECT
public:
    productStrorage();

signals:
    void sig_flushTableitem();

private:
    void amendproductTableWidget();
    void removeTableWidget();
    void searchTableWidget();

    void tableWidgetShow();
private slots:
    void addProductTableWidget();  //添加按钮
    void readProfileTableWidget(QStringList strlist);//读取配置文件到tablewidget


private:
    QPushButton* m_pbutton_add = nullptr;//添加产品
    QPushButton* m_pbutton_amend = nullptr;//修改
    QPushButton* m_pbutton_rm = nullptr;//删除
    QPushButton* m_psearch_pushbutton = nullptr;//搜索

    QLineEdit* m_pname_lineedit = nullptr;//商品名称
    QLineEdit* m_pprice_lineedit = nullptr; //入库价格
    QLineEdit* m_pnum_lineedit = nullptr; //入库数量

    QComboBox* m_pdate_combobox = nullptr;//添加日期

    QTableWidget* m_ptable_strorage = nullptr;//入库表格


    Profile* m_pProfile = nullptr;

    // QString m_pstrorageProfileName = "C:/Users/gaohuan/Documents/data/strorage_data.csv";

    sqlTableWidget* sql_ = nullptr;

    QVector<sql_struct::tableWidget_data> tablewidget_data;

};

#endif // PRODUCTSTRORAGE_H
