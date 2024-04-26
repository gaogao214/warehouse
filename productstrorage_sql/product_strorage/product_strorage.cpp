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
    vlayout->setSpacing(10);
    vlayout->setContentsMargins(0,0,0,0);

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

    m_pname_lineedit = new QLineEdit();
    add_hlayout->addWidget(m_pname_lineedit);

    QLabel* label_date = new QLabel();
    label_date->setText("添加日期");
    add_hlayout->addWidget(label_date);

    m_pdate_combobox = new QComboBox();
    add_hlayout->addWidget(m_pdate_combobox);

    QLabel* label_price = new QLabel();
    label_price->setText("入库价格");
    add_hlayout->addWidget(label_price);

    m_pprice_lineedit = new QLineEdit();
    add_hlayout->addWidget(m_pprice_lineedit);


    QLabel* label_num = new QLabel();
    label_num->setText("入库数量");
    add_hlayout->addWidget(label_num);

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


    sql_= new sqlTableWidget();//初始化数据库



    tableWidgetShow();
}


//添加按钮 添加数据到tableWidget
void productStrorage::addProductTableWidget()
{

    addproduct* product = new addproduct();

    connect(product,&addproduct::sig_saveAddProduct,this,[this](QString name,QString time,QString price,QString num){

#ifdef QSQLTABLE
        float count = price.toFloat() * num.toInt();
        sql_->addSQLTablewidget(name,time,price.toInt(),num.toInt(),count);
        tableWidgetShow();
#elif
        //     m_ptable_strorage->setItem(RowCont,0,new QTableWidgetItem(name));
        //     m_ptable_strorage->setItem(RowCont,1,new QTableWidgetItem(time));
        //     m_ptable_strorage->setItem(RowCont,2,new QTableWidgetItem(price));
        //     m_ptable_strorage->setItem(RowCont,3,new QTableWidgetItem(num));
        //     float count = price.toFloat() * num.toInt();
        //     m_ptable_strorage->setItem(RowCont,4,new QTableWidgetItem(QString::number(count)));

//     // m_pProfile->writeProfile(m_pstrorageProfileName,name,time,price,num,QString::number(count));
//     sql_->addSQLTablewidget(name,time,price.toInt(),num.toInt(),count);
//     emit sig_flushTableitem();//刷新库存和收益界面
#endif
    });

    product->show();



}

//修改按钮
void productStrorage::amendproductTableWidget()
{
#ifdef QSQLTABLE

    addproduct* product = nullptr;

    QItemSelectionModel *select = m_ptable_strorage->selectionModel();

    QModelIndexList list = select->selectedIndexes();
    // qDebug()<<"selectedIndexes"<<select->selectedIndexes();
    qDebug()<<"list.size:"<<list.size();
    product = new addproduct();
    QStringList strlist;
    //tableview 获取选中行的内容
    for(int i = 0; i < list.size();i++)
    {
        qDebug()<<"list["<<i<<"]: "<<list[i].model()->data(list[i]).value<QString>();
        qDebug()<<"list row ["<<i<<"]: "<<list[i].row();
        strlist.push_back(list[i].model()->data(list[i]).value<QString>());

    }
    product->setProductProperty(strlist[0],strlist[1],strlist[2],strlist[3]);


    connect(product,&addproduct::sig_saveAddProduct,this,[this](QString name,QString time,QString price,QString num){

        float count = price.toFloat() * num.toInt();
        // sql_->updateTableWidget(name,time,price.toInt(),num.toInt(),QString::number(count).toInt());
        tableWidgetShow();
        // sql_->updateTableWidget(name,time,price.toInt(),num.toInt(),QString::number(count).toInt());
        emit sig_flushTableitem();
    });

    product->show();
#elif

    addproduct* product = nullptr;

    QList<QTableWidgetItem*> items = m_ptable_strorage->selectedItems();
    int select_row = 0;
    if(!items.empty()){
        product = new addproduct();

        product->setProductProperty(items.at(0)->text(),items.at(1)->text(),items.at(2)->text(),items.at(3)->text());

        select_row =items.at(0)->row();
        qDebug()<<"select_row :"<<select_row;

        connect(product,&addproduct::sig_saveAddProduct,this,[this,select_row](QString name,QString time,QString price,QString num){

            // int RowCont;
            // RowCont=m_ptable_strorage->rowCount();
            // m_ptable_strorage->insertRow(RowCont);//增加一行
            m_ptable_strorage->setItem(select_row,0,new QTableWidgetItem(name));
            m_ptable_strorage->setItem(select_row,1,new QTableWidgetItem(time));
            m_ptable_strorage->setItem(select_row,2,new QTableWidgetItem(price));
            m_ptable_strorage->setItem(select_row,3,new QTableWidgetItem(num));
            float count = price.toFloat() * num.toInt();
            m_ptable_strorage->setItem(select_row,4,new QTableWidgetItem(QString::number(count)));

            QTextStream strList ;

            qDebug()<<"m_ptable_strorage->columnCount():"<<m_ptable_strorage->columnCount()<<"\n";
            qDebug()<<"m_ptable_strorage->rowCount():"<<m_ptable_strorage->rowCount()<<"\n";

            sql_->updateTableWidget(name,time,price.toInt(),num.toInt(),QString::number(count).toInt());
            emit sig_flushTableitem();
        });

        product->show();
    }
    else{

        QMessageBox::warning(this,"警告","请先选择一行再进行操作");
    }
#endif

}

void productStrorage::removeTableWidget()
{
    // QList<QTableWidgetItem*> items = m_ptable_strorage->selectedItems();

    // if(!items.empty()){

    //     auto message = QMessageBox::warning(this,"提示","是否删除本行数据");

    //     int delete_row = items.at(0)->row();
    //     //如确认删除
    //     if(message == QMessageBox::Ok)
    //     {
    //         m_ptable_strorage->removeRow(delete_row);  //删除掉了表格信息
    //         sql_->deleteTableWidget(delete_row);
    //     }
    //     emit sig_flushTableitem();
    // }
    // else{


    //     QMessageBox::warning(this,"警告","请先选择一行再进行操作");
    // }
}

void productStrorage::searchTableWidget()
{
    // QString input_name=m_pname_lineedit->text();
    // int row_num=m_ptable_strorage->rowCount();
    // if (input_name=="")//判断是否是空，如果是空就显示所有行
    // {
    //     for(int i=0;i<row_num;i++)
    //     {
    //         m_ptable_strorage->setRowHidden(i,false);//为false就是显示
    //     }
    // }
    // else
    // {
    //     //找到符合条件的索引 是通过你输入的和表格里面所有内容进行比对
    //     QList <QTableWidgetItem *> item = m_ptable_strorage->findItems(m_pname_lineedit->text(), Qt::MatchContains);
    //     //然后把所有行都隐藏
    //     for(int i=0;i<row_num;i++)
    //     {
    //         m_ptable_strorage->setRowHidden(i,true);//隐藏

    //     }
    //     //判断符合条件索引是不是空
    //     if(!item.empty())
    //     {
    //         //恢复对应的行
    //         for(int i=0;i<item.count();i++)
    //         {
    //             m_ptable_strorage->setRowHidden(item.at(i)->row(),false);//回复对应的行，也可以回复列

    //         }
    //     }
    // }
}

//打开软件，把配置文件的内容读取到tablewidget
void productStrorage::readProfileTableWidget(QStringList strlist)
{
    // int count = strlist.count();
    // int RowCont;
    // RowCont=m_ptable_strorage->rowCount();
    // m_ptable_strorage->insertRow(RowCont);//增加一行

    // // qDebug()<<"count:"<<count;
    // for(int i = 0; i < count ;i++)
    // {

    //     // qDebug()<<"strlist:"<<strlist[i];
    //     m_ptable_strorage->setItem(RowCont,i,new QTableWidgetItem(strlist[i]));

    // }
}

void productStrorage::onTableClicked()
{
    int row = m_ptable_strorage->currentIndex().row();//获得当前行索引
    qDebug()<<row;
    QModelIndex index1 =m_pTableViewModel->index(row,12);
    //model是你tableView里的模型，->index(行索引,列索引)
    //（索引从零开始,要看哪行哪列自己写（可以写循环遍历全部））
    QString id=m_pTableViewModel->data(index1).toString();//获取索引对应位置的数据转为字符串
    qDebug()<<id;
}

//软件启动读取数据库内容
void productStrorage::tableWidgetShow()
{
    tablewidget_data = sql_->getTableWidgetData();
    m_ptable_strorage->setModel(tablewidget_data);
}
