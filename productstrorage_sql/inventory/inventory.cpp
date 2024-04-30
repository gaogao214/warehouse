#include "inventory.h"
#include <QDebug>
#include <QFile>

inventory::inventory()
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
    label->setText("库存信息");
    hlayout->addWidget(label);

    hlayout->addSpacing(700);//添加与下个部件的间距

    QLabel* alarm_label = new QLabel();
    alarm_label->setText("报警阈值");
    hlayout->addWidget(alarm_label);

    m_palarm_lineedit = new QLineEdit();

    hlayout->addWidget(m_palarm_lineedit);

    //修改产品按钮
    m_pbutton_amend = new QPushButton();
    m_pbutton_amend->setFixedHeight(30);
    m_pbutton_amend->setText("修改");
    hlayout->addWidget(m_pbutton_amend);
    connect(m_pbutton_amend,&QPushButton::clicked,this,[this]{
        // amendproductTableWidget();
    });

    //刷新按钮
    m_pbutton_flush = new QPushButton();
    m_pbutton_flush->setFixedHeight(30);
    m_pbutton_flush->setText("刷新");
    hlayout->addWidget(m_pbutton_flush);
    connect(m_pbutton_flush,&QPushButton::clicked,this,[this]{
        // removeTableWidget();
    });

    vlayout->addLayout(hlayout);

    //水平布局
    QHBoxLayout* add_hlayout = new QHBoxLayout();
    add_hlayout->setContentsMargins(0,0,0,0);
    add_hlayout->setSpacing(10);

    // m_ptable_strorage = new QTableWidget();
    // m_ptable_strorage->resize(900,500);
    // // m_ptable_strorage->setRowCount(6);//行数
    // m_ptable_strorage->setColumnCount(3);//列数
    // m_ptable_strorage->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    // m_ptable_strorage->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    // m_ptable_strorage->setHorizontalHeaderLabels(QStringList()<<"商品名称"<<"库存量"<<"报警阈值");

    m_ptable_strorage = new QTableView();
    m_ptable_strorage->resize(900,500);
    m_ptable_strorage->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    m_ptable_strorage->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改

    QHeaderView *hearview = new QHeaderView(Qt::Horizontal);
    m_pTableViewModel = new QStandardItemModel(this);
    m_pTableViewModel->setHorizontalHeaderLabels(QStringList()<<"商品名称"<<"库存量"<<"报警阈值");
    hearview->setModel(m_pTableViewModel);
    hearview->setSectionResizeMode(QHeaderView::Stretch);    //先自适应宽度
    hearview->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    m_ptable_strorage->setHorizontalHeader(hearview);

    vlayout->addWidget(m_ptable_strorage);

    tableWidgetShow();
}

void inventory::tableWidgetShow()
{
    if(m_ptable_strorage->model() != nullptr)
    {
        int rowCount = m_ptable_strorage->model()->rowCount();
        m_ptable_strorage->model()->removeRows(0,rowCount);
        m_ptable_strorage->update();
    }

    for(auto iter : m_pstrorageVector)
    {
        auto property = std::find_if(m_psaleVector.begin(), m_psaleVector.end(), [&](auto file) {return file.name == iter.name; });
        if (property == m_psaleVector.end())
        {
            // qDebug()<<"没有找到key值"<<"iter.begin:"<<iter.name<<"iter.end:"<<iter.num<<"\n";
            // 在指定行之前插入一行数据
            QList<QStandardItem *> newRowItems;
            newRowItems.append(new QStandardItem(iter.name));
            newRowItems.append(new QStandardItem(QString::number(iter.num)));
            if(m_ptable_strorage->model() == nullptr)
            {
                m_pTableViewModel->insertRow(0, newRowItems);
            }
            else
            {
                 int RowCont=m_ptable_strorage->model()->rowCount();
                 m_pTableViewModel->insertRow(RowCont, newRowItems);
            }

            // 将模型设置到QTableView中
            m_ptable_strorage->setModel(m_pTableViewModel);
        }
        else
        {
            // qDebug()<<"找到key值"<<"property.name:"<<property->name<<"iter.end:"<<property->num<<"\n";
            int inventory_num = iter.num - property->num;
            // 在指定行之前插入一行数据
            QList<QStandardItem *> newRowItems;
            newRowItems.append(new QStandardItem(iter.name));
            newRowItems.append(new QStandardItem(QString::number(inventory_num)));
            if(m_ptable_strorage->model() == nullptr)
            {
                m_pTableViewModel->insertRow(0, newRowItems);
            }
            else
            {
                int RowCont=m_ptable_strorage->model()->rowCount();
                m_pTableViewModel->insertRow(RowCont, newRowItems);
            }
            // 将模型设置到QTableView中
            m_ptable_strorage->setModel(m_pTableViewModel);
        }
    }
}

void inventory::StrorageTableWidgetFlush(QSqlTableModel* tablewidget_data)
{
    m_pstrorageVector.clear();
    int rowCount = tablewidget_data->rowCount();
    for(int row = 0;row < rowCount; row++)
    {
        QModelIndex index = tablewidget_data->index(row,0);
        QVariant data = tablewidget_data->data(index);
        m_pstrorageInventory.name = data.toString();
        index = tablewidget_data->index(row,3);
        data = tablewidget_data->data(index);
        m_pstrorageInventory.num = data.toInt();
        m_pstrorageVector.push_back(m_pstrorageInventory);
    }
    tableWidgetShow();
}

void inventory::SaleTableWidgetFlush(QSqlTableModel *tablewidget_data)
{
    m_psaleVector.clear();
    int rowCount = tablewidget_data->rowCount();
    for(int row = 0;row < rowCount; row++)
    {
        QModelIndex index = tablewidget_data->index(row,0);
        QVariant data = tablewidget_data->data(index);
        m_psaleInventory.name = data.toString();
        index = tablewidget_data->index(row,3);
        data = tablewidget_data->data(index);
        m_psaleInventory.num = data.toInt();
        m_psaleVector.push_back(m_psaleInventory);
    }
    tableWidgetShow();
}
