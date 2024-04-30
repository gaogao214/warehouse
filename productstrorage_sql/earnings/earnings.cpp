#include "earnings.h"
#include <QFile>

earnings::earnings() {
    //垂直布局
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setSpacing(10);
    vlayout->setContentsMargins(0,0,0,0);

    //水平布局
    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->setContentsMargins(0,0,0,0);
    hlayout->setSpacing(10);

    QLabel* label = new QLabel();
    label->setText("收益明细");
    hlayout->addWidget(label);

    hlayout->addSpacing(700);//添加与下个部件的间距
    // vlayout->addLayout(hlayout);

    QLabel* label_name = new QLabel();
    label_name->setText("筛选时间");
    hlayout->addWidget(label_name);

    m_pname_lineedit = new QLineEdit();
    hlayout->addWidget(m_pname_lineedit);

    vlayout->addLayout(hlayout);

    QHBoxLayout* search_hlayout = new QHBoxLayout();
    search_hlayout->setContentsMargins(0,0,0,0);
    search_hlayout->addSpacing(750);

    m_psearch_pushbutton = new QPushButton();
    m_psearch_pushbutton->setFixedHeight(30);
    m_psearch_pushbutton->setText("搜索");

    search_hlayout->addWidget(m_psearch_pushbutton);
    vlayout->addLayout(search_hlayout);

    connect(m_psearch_pushbutton,&QPushButton::clicked,this,[this](){
        // searchTableWidget();
    });


    // m_ptable_strorage = new QTableWidget();
    // m_ptable_strorage->resize(900,500);
    // // m_ptable_strorage->setRowCount(6);//行数
    // m_ptable_strorage->setColumnCount(6);//列数
    // m_ptable_strorage->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    // m_ptable_strorage->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改

    // m_ptable_strorage->setHorizontalHeaderLabels(QStringList()<<"收益日期"<<"总售价"<<"收益总价");
    m_ptable_strorage = new QTableView();
    m_ptable_strorage->resize(900,500);
    m_ptable_strorage->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    m_ptable_strorage->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改

    QHeaderView *hearview = new QHeaderView(Qt::Horizontal);
    m_pTableViewModel = new QStandardItemModel(this);
    m_pTableViewModel->setHorizontalHeaderLabels(QStringList()<<"收益日期"<<"总售价");
    hearview->setModel(m_pTableViewModel);
    hearview->setSectionResizeMode(QHeaderView::Stretch);    //先自适应宽度
    // hearview->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    m_ptable_strorage->setHorizontalHeader(hearview);

    vlayout->addWidget(m_ptable_strorage);

    // tableWidgetEarnings();
}

//时间相同，计算sale相同时间的售价相加;在数组中找相同时间的iter;
void earnings::tableWidgetEarnings()
{
    int total_price = 0;
    QString keystr ;
    for(auto iter:m_psaleVector)
    {
        auto it = std::find_if(m_psaleVector.begin(), m_psaleVector.end(), [&](const inventory_property& item){
            return item.time == iter.time;
        });
        if(it != m_psaleVector.end())
        {
            qDebug()<<"time :"<<iter.time<<"iter.price:"<<iter.price<<"\n";
            m_ptableWidgetMap[iter.time].push_back(iter.price);
        }
    }

    if(!m_ptableWidgetMap.empty())
    {
        for(auto& iter : m_ptableWidgetMap.keys())
        {
            keystr = iter;
            qDebug()<<"iter key:"<<iter<<":";
            for(auto it: m_ptableWidgetMap[iter])
            {
                qDebug()<<"value:"<<it<<"\n";
                total_price += it;
            }
            QList<QStandardItem *> newRowItems;
            newRowItems.append(new QStandardItem(keystr));
            newRowItems.append(new QStandardItem(QString::number(total_price)));
            if(m_ptable_strorage->model() == nullptr)
            {
                m_pTableViewModel->insertRow(0, newRowItems);
            }
            else
            {
                int RowCont=m_ptable_strorage->model()->rowCount();
                m_pTableViewModel->insertRow(RowCont, newRowItems);
            }

            m_ptable_strorage->setModel(m_pTableViewModel);// 将模型设置到QTableView中
            m_ptable_strorage->update();
        }
    }


    // for(auto iter : m_psaleVector)
    // {
    //     auto property = std::find_if(m_ptableWidgetVector.begin(), m_ptableWidgetVector.end(), [&](auto file) {return file.time == iter.time; });

    //     if (property == m_ptableWidgetVector.end())
    //     {
    //         RowCont=m_ptable_strorage->rowCount();
    //         m_ptable_strorage->insertRow(RowCont);
    //         m_ptable_strorage->setItem(RowCont,1,new QTableWidgetItem(iter.time));
    //         m_ptableWidgeInventory.name = iter.name;
    //         m_ptableWidgeInventory.time = iter.time;
    //         m_ptableWidgeInventory.price = iter.price;
    //         m_ptableWidgeInventory.row = RowCont;

    //         m_ptableWidgetVector.push_back(m_ptableWidgeInventory);
    //     }
    //     else
    //     {
    //         sale_price_count = property->price.toInt() + iter.price.toInt();                //日期一样 将收益累加
    //         // m_ptable_strorage->setItem(property->row,0,new QTableWidgetItem(iter.name));
    //         m_ptable_strorage->setItem(property->row,0,new QTableWidgetItem(iter.time));
    //          // m_ptable_strorage->setItem(property->row,2,new QTableWidgetItem(QString::number(price_count)));
    //         m_ptable_strorage->setItem(property->row,2,new QTableWidgetItem(QString::number(sale_price_count)));
    //     }
    // }

}

void earnings::StrorageTableWidgetEarnings(QSqlTableModel* tablewidget_data)
{
    m_pstrorageVector.clear();
    int rowCount = tablewidget_data->rowCount();
    for(int row = 0;row < rowCount; row++)
    {
        QModelIndex index = tablewidget_data->index(row,1);//入库时间
        QVariant data = tablewidget_data->data(index);
        m_pstrorageInventory.time = data.toString();
        index = tablewidget_data->index(row,2);//入库价格
        data = tablewidget_data->data(index);
        m_pstrorageInventory.price = data.toInt();
        m_pstrorageVector.push_back(m_pstrorageInventory);
    }
    tableWidgetEarnings();
}

void earnings::SaleTableWidgetEarnings(QSqlTableModel* tablewidget_data)
{
    m_psaleVector.clear();
    int rowCount = tablewidget_data->rowCount();
    for(int row = 0;row < rowCount; row++)
    {
        QModelIndex index = tablewidget_data->index(row,1);//出售时间
        QVariant data = tablewidget_data->data(index);
        m_psaleInventory.time = data.toString();
        index = tablewidget_data->index(row,2);//售价
        data = tablewidget_data->data(index);
        m_psaleInventory.price = data.toFloat();
        m_psaleVector.push_back(m_psaleInventory);
    }
    tableWidgetEarnings();
}


