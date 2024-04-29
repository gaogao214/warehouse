#ifndef INVENTORY_H
#define INVENTORY_H
#include <QWidget>
#include <QLabel>
#include <QObject>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QVector>

#include "profile.h"
#pragma execution_character_set("utf-8")
//库存
class inventory:public QWidget
{
    Q_OBJECT
public:
    inventory();

public slots:
    void tableWidgetShow();

    void tableWidgetFlush(QString name,int num);

private:
    QPushButton* m_pbutton_amend = nullptr;//修改
    QPushButton* m_pbutton_flush = nullptr;//删除
    QPushButton* m_psearch_pushbutton = nullptr;//搜索

    QLineEdit* m_palarm_lineedit = nullptr;//商品名称

    QComboBox* m_pdate_combobox = nullptr;//添加日期

    QTableWidget* m_ptable_strorage = nullptr;//入库表格


    Profile* m_pProfile = nullptr;

    QString m_pstrorageProfileName = "C:/Users/gaohuan/Documents/data/strorage_data.csv";
    QString m_psaleProfileName = "C:/Users/gaohuan/Documents/data/sale_data.csv";

    QString m_pstrorage_name;
    QString m_pstrorage_num;
    QString m_psale_name;
    QString m_psale_num;

    struct inventory_property
    {
        QString name;
        QString num;
        int row;
    };
    inventory_property m_pstrorageInventory;
    inventory_property m_psaleInventory;
    inventory_property m_pflushInventory;

    QVector<inventory_property> m_pstrorageVector;
    QVector<inventory_property> m_psaleVector;
    QVector<inventory_property> m_pflushVector;
};

#endif // INVENTORY_H
