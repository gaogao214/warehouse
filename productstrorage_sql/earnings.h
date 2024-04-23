#ifndef EARNINGS_H
#define EARNINGS_H

#include <QWidget>
#include <QLabel>
#include <QObject>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QDebug>

#include "profile.h"
#pragma execution_character_set("utf-8")
//收益报表
class earnings:public QWidget
{
    Q_OBJECT
public:
    earnings();

    void tableWidgetEarnings();

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

    QString m_pstrorageProfileName = "C:/Users/gaohuan/Documents/data/strorage_data.csv";
    QString m_psaleProfileName = "C:/Users/gaohuan/Documents/data/sale_data.csv";

    struct inventory_property
    {
        QString name;
        QString price;
        QString num;
        QString time;
        int row;
    };
    inventory_property m_pstrorageInventory;
    inventory_property m_psaleInventory;
    inventory_property m_ptableWidgeInventory;

    QVector<inventory_property> m_pstrorageVector;
    QVector<inventory_property> m_psaleVector;
    QVector<inventory_property> m_ptableWidgetVector;
};

#endif // EARNINGS_H
