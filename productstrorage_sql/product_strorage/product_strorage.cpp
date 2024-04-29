#include "product_strorage.h"

#include <QDebug>
#include <QMessageBox>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QDateTime>
#include <QTimer>

#define QSQLTABLE
//产品入库
productStrorage::productStrorage()
{
    //垂直布局
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setSpacing(10);//部件间隔
    vlayout->setContentsMargins(0,0,0,0);//上下左右间隔

    //水平布局
    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->setContentsMargins(0,0,0,0);
    hlayout->setSpacing(10);

    QLabel* label = new QLabel();
    label->setText("入库信息");
    hlayout->addWidget(label);
    hlayout->addSpacing(700);//添加与下个部件的间距

    //添加产品按钮
    m_pbutton_add = new QPushButton();
    m_pbutton_add->setFixedHeight(30);
    m_pbutton_add->setText("添加");
    hlayout->addWidget(m_pbutton_add);


    //修改产品按钮
    m_pbutton_amend = new QPushButton();
    m_pbutton_amend->setFixedHeight(30);
    m_pbutton_amend->setText("修改");
    hlayout->addWidget(m_pbutton_amend);


    //删除按钮
    m_pbutton_rm = new QPushButton();
    m_pbutton_rm->setFixedHeight(30);
    m_pbutton_rm->setText("删除");
    hlayout->addWidget(m_pbutton_rm);

    vlayout->addLayout(hlayout);

    //水平布局
    QHBoxLayout* add_hlayout = new QHBoxLayout();
    add_hlayout->setContentsMargins(0,0,0,0);
    add_hlayout->setSpacing(10);

    QLabel* label_name = new QLabel();
    label_name->setText("商品名称");
    add_hlayout->addWidget(label_name);

    //填写商品名称lineedit
    m_pname_lineedit = new QLineEdit();
    add_hlayout->addWidget(m_pname_lineedit);

    QLabel* label_date = new QLabel();
    label_date->setText("添加日期");
    add_hlayout->addWidget(label_date);

    //填写添加日期lineedit
    m_pdate_combobox = new QComboBox();
    add_hlayout->addWidget(m_pdate_combobox);

    QLabel* label_price = new QLabel();
    label_price->setText("入库价格");
    add_hlayout->addWidget(label_price);

    //填写入库价格lineedit
    m_pprice_lineedit = new QLineEdit();
    add_hlayout->addWidget(m_pprice_lineedit);

    QLabel* label_num = new QLabel();
    label_num->setText("入库数量");
    add_hlayout->addWidget(label_num);

    //填写入库数量lineedit
    m_pnum_lineedit = new QLineEdit();
    add_hlayout->addWidget(m_pnum_lineedit);

    vlayout->addLayout(add_hlayout);

    QHBoxLayout* search_hlayout = new QHBoxLayout();
    search_hlayout->setContentsMargins(0,0,0,0);
    search_hlayout->addSpacing(750);

    m_psearch_pushbutton = new QPushButton();
    m_psearch_pushbutton->setFixedHeight(30);
    m_psearch_pushbutton->setText("搜索");

    search_hlayout->addWidget(m_psearch_pushbutton);
    vlayout->addLayout(search_hlayout);

    //=====================================👇创建tableview===================================================
    m_ptable_strorage = new QTableView();
    m_ptable_strorage->resize(900,500);
    m_ptable_strorage->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    m_ptable_strorage->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改

    QHeaderView *hearview = new QHeaderView(Qt::Horizontal);
    m_pTableViewModel = new QStandardItemModel(this);
    m_pTableViewModel->setHorizontalHeaderLabels(QStringList()<<"商品名称"<<"入库时间"<<"入库价格"<<"入库数量"<<"入库总价");
    hearview->setModel(m_pTableViewModel);
    hearview->setSectionResizeMode(QHeaderView::Stretch);    //先自适应宽度
    hearview->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    m_ptable_strorage->setHorizontalHeader(hearview);

    vlayout->addWidget(m_ptable_strorage);
    //=====================================👆创建tableview===================================================
    //按下添加产品按钮，tablewidget可添加产品等数据
    connect(m_pbutton_add,&QPushButton::clicked,this,[this]{
        addProductTableWidget();
    });

    //修改
    connect(m_pbutton_amend,&QPushButton::clicked,this,[this]{
        amendproductTableWidget();
    });

    //删除
    connect(m_pbutton_rm,&QPushButton::clicked,this,[this]{
        removeTableWidget();
    });

    //搜索
    connect(m_psearch_pushbutton,&QPushButton::clicked,this,[this](){
        searchTableWidget();
    });
    qDebug()<<"productStrorage thread id:"<<QThread::currentThreadId();

    sql_= new sqlTableWidget();//初始化数据库
    sql_->searchSQL(1);
    tableWidgetShow();
}

//===========================👇添加按钮===============================
void productStrorage::addProductTableWidget()
{
    addproduct* product = new addproduct();//添加属性页面

    connect(product,&addproduct::sig_saveAddProduct,this,[this](QString name,QString time,QString price,QString num){

        float count = price.toFloat() * num.toInt();
        sql_->addSQLTablewidget(name,time,price.toInt(),num.toInt(),count);
        tableWidgetShow();

        emit sig_flushTableitem(name,num.toInt());//刷新库存和收益界面

    });

    product->show();
}
//===========================👆添加按钮===============================
//===========================👇修改所选中行===============================
void productStrorage::amendproductTableWidget()
{
    addproduct* product = nullptr;//修改属性页面

    QItemSelectionModel *select = m_ptable_strorage->selectionModel();

    QModelIndexList list = select->selectedIndexes();
    if(!list.empty()){
        selete_row = select->selectedRows().first().row();
        qDebug()<<"selectedIndexes"<<select->selectedRows().first().row();
        qDebug()<<"list.size:"<<list.size();
        product = new addproduct();
        QStringList strlist;
        //tableview 获取选中行的内容
        for(int i = 0; i < list.size();i++)
        {
            qDebug()<<"list["<<i<<"]: "<<list[i].model()->data(list[i]).value<QString>();
            strlist.push_back(list[i].model()->data(list[i]).value<QString>());

        }
        product->setProductProperty(strlist[0],strlist[1],strlist[2],strlist[3]);//没修改之前在属性页面显示
        connect(product,&addproduct::sig_saveAddProduct,this,[this](QString name,QString time,QString price,QString num){

            float count = price.toFloat() * num.toInt();
            sql_->updateTableWidget(selete_row,name,time,price.toInt(),num.toInt(),QString::number(count).toInt());
            tableWidgetShow();
            // emit sig_flushTableitem();//刷新库存和收益界面
        });

        product->show();
    }else{

        QMessageBox::warning(this,"警告","请先选择一行再进行操作");
    }
}
//===========================👆修改所选中行===============================
//===========================👇删除所选中行===============================
void productStrorage::removeTableWidget()
{
    QItemSelectionModel *select = m_ptable_strorage->selectionModel();
    QModelIndexList list = select->selectedIndexes();
    if(!list.empty()){
        auto message = QMessageBox::warning(this,"提示","是否删除本行数据");
        if(message== QMessageBox::Ok)
        {
            selete_row = select->selectedRows().first().row();
            qDebug()<<"selectedIndexes"<<select->selectedRows().first().row();
            qDebug()<<"list.size:"<<list.size();
            sql_->deleteTableWidget(selete_row);
            tableWidgetShow();
        }
    }else{
        QMessageBox::warning(this,"警告","请先选择一行再进行操作");
    }
}
//===========================👆删除所选中行===============================
//===========================👇搜索商品名称===============================
void productStrorage::searchTableWidget()
{
    qDebug()<<"m_pname_lineedit->text()"<<m_pname_lineedit->text();
    sql_->searchTableView( m_pname_lineedit->text());
    tableWidgetShow();
}
//===========================👆搜索商品名称===============================

//============================👇软件启动读取数据库内容======================
void productStrorage::tableWidgetShow()
{
    tablewidget_data = sql_->getTableWidgetData();
    m_ptable_strorage->setModel(tablewidget_data);
}
//============================👆软件启动读取数据库内容======================
