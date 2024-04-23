#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#pragma execution_character_set("utf-8")

class addproduct:public QWidget
{
    Q_OBJECT
public:
    addproduct();

    void setProductProperty(QString name,QString time,QString price,QString num);

signals:
    void sig_saveAddProduct(QString name,QString time,QString price,QString num);


private:
    QPushButton* m_psaveButton = nullptr; //保存按钮
    QPushButton* m_pcannelButton = nullptr;//取消按钮

    QLineEdit* m_pname_lineedit = nullptr;//商品名称
    QLineEdit* m_ptime_lineedit = nullptr;//入库时间
    QLineEdit* m_pprice_lineedit =nullptr;//入库价格
    QLineEdit* m_pnum_lineedit =nullptr;//入库数量


};

#endif // ADDPRODUCT_H
