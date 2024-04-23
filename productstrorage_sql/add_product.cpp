#include "add_product.h"
#include <QDateTime>
#include <QDebug>

//添加按钮弹窗
addproduct::addproduct()
{

    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->setContentsMargins(0,0,0,0);
    vlayout->setSpacing(10);
    this->setLayout(vlayout);

    QLabel* titleLabel = new QLabel();
    titleLabel->setFixedSize(280,20);
    titleLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    titleLabel->setText("添加产品");
    vlayout->addWidget(titleLabel);
    //========================👇商品名称===============
    QHBoxLayout* hlayouut = new QHBoxLayout();
    hlayouut->setContentsMargins(0,0,0,0);
    hlayouut->setSpacing(10);

    QLabel* label = new QLabel();
    label->setText("商品名称");
    m_pname_lineedit = new QLineEdit();

    hlayouut->addWidget(label);
    hlayouut->addWidget(m_pname_lineedit);
    //========================👆商品名称===============

    //========================👇入库时间===============
    QHBoxLayout* hlayouut_time = new QHBoxLayout();
    hlayouut_time->setContentsMargins(0,0,0,0);
    hlayouut_time->setSpacing(10);

    QDateTime curDateTime = QDateTime :: currentDateTime();

    QLabel* label_time = new QLabel();
    label_time->setText("入库时间");
    m_ptime_lineedit = new QLineEdit();
    m_ptime_lineedit->setText(curDateTime.toString("yyyy/MM/dd"));

    hlayouut_time->addWidget(label_time);
    hlayouut_time->addWidget(m_ptime_lineedit);
    //========================👆入库时间===============

    //========================👇入库价格===============
    QHBoxLayout* hlayouut_price = new QHBoxLayout();
    hlayouut_price->setContentsMargins(0,0,0,0);
    hlayouut_price->setSpacing(10);

    QLabel* label_price = new QLabel();
    label_price->setText("入库价格");

    m_pprice_lineedit = new QLineEdit();

    hlayouut_price->addWidget(label_price);
    hlayouut_price->addWidget(m_pprice_lineedit);
    //========================👆入库价格===============

    //========================👇入库数量===============
    QHBoxLayout* hlayouut_num = new QHBoxLayout();
    hlayouut_num->setContentsMargins(0,0,0,0);
    hlayouut_num->setSpacing(10);

    QLabel* label_num = new QLabel();
    label_num->setText("入库数量");

    m_pnum_lineedit = new QLineEdit();

    hlayouut_num->addWidget(label_num);
    hlayouut_num->addWidget(m_pnum_lineedit);
    //========================👆入库数量===============

    //========================👇是否保存按钮===============
    QHBoxLayout* hlayouut_button = new QHBoxLayout();
    hlayouut_button->setContentsMargins(0,0,0,0);
    hlayouut_button->setSpacing(10);

    m_psaveButton = new QPushButton();
    m_psaveButton->setText("保存");

    connect(m_psaveButton,&QPushButton::clicked,this,[this]{
        QString name = m_pname_lineedit->text();
        QString time = m_ptime_lineedit->text();
        QString price = m_pprice_lineedit->text();
        QString num = m_pnum_lineedit->text();


        qDebug()<<"name:"<<name<<"time"<<time<<"price:"<<price<<"num:"<<num<<"\n";
        emit sig_saveAddProduct(name,time,price,num);

        this->close();
    });

    m_pcannelButton = new QPushButton();
    m_pcannelButton->setText("取消");

    connect(m_pcannelButton,&QPushButton::clicked,this,[this]{
        this->close();
    });

    hlayouut_button->addWidget(m_psaveButton);
    hlayouut_button->addWidget(m_pcannelButton);
    //========================👆取消保存按钮===============
    vlayout->addLayout(hlayouut);
    vlayout->addLayout(hlayouut_time);
    vlayout->addLayout(hlayouut_price);
    vlayout->addLayout(hlayouut_num);
    vlayout->addLayout(hlayouut_button);

}

void addproduct::setProductProperty(QString name,QString time,QString price,QString num)
{
    m_pname_lineedit->setText(name);
    m_ptime_lineedit->setText(time);
    m_pprice_lineedit->setText(price);
    m_pnum_lineedit->setText(num);
}


