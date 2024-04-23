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


    m_ptable_strorage = new QTableWidget();
    m_ptable_strorage->resize(900,500);
    // m_ptable_strorage->setRowCount(6);//行数
    m_ptable_strorage->setColumnCount(6);//列数
    m_ptable_strorage->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    m_ptable_strorage->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改

    m_ptable_strorage->setHorizontalHeaderLabels(QStringList()<<"收益日期"<<"售价"<<"收益总价");
    vlayout->addWidget(m_ptable_strorage);

    m_pProfile = new Profile();

    connect(m_pProfile,&Profile::sig_readStrorageProfile,this,[this](QStringList strlist){
        // readProfileTableWidget(strlist);
    });
    // m_pProfile->readProfile(m_pstrorageProfileName,0);
    tableWidgetEarnings();
}

void earnings::tableWidgetEarnings()
{
    int sale_count = 0;
    int RowCont = 0;
    int sale_price_count = 0;

    QFile saleFile(m_psaleProfileName);
    if (!saleFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;

    QTextStream saleStream(&saleFile);
    while (!saleStream.atEnd())
    {
        QString line = saleStream.readLine();
        QStringList row = line.split(',', Qt::SkipEmptyParts);
        if(sale_count > 0)
        {
            m_psaleInventory.name = row[0];
            m_psaleInventory.num = row[3];
            m_psaleInventory.time = row[1];
            m_psaleInventory.price = row[4];
            m_psaleVector.push_back(m_psaleInventory);
        }
        sale_count = 1;
    }

    for(auto iter : m_psaleVector)
    {
        auto property = std::find_if(m_ptableWidgetVector.begin(), m_ptableWidgetVector.end(), [&](auto file) {return file.time == iter.time; });

        if (property == m_ptableWidgetVector.end())
        {
            RowCont=m_ptable_strorage->rowCount();
            m_ptable_strorage->insertRow(RowCont);
            m_ptable_strorage->setItem(RowCont,1,new QTableWidgetItem(iter.time));
            m_ptableWidgeInventory.name = iter.name;
            m_ptableWidgeInventory.time = iter.time;
            m_ptableWidgeInventory.price = iter.price;
            m_ptableWidgeInventory.row = RowCont;

            m_ptableWidgetVector.push_back(m_ptableWidgeInventory);
        }
        else
        {
            sale_price_count = property->price.toInt() + iter.price.toInt();                //日期一样 将收益累加
            // m_ptable_strorage->setItem(property->row,0,new QTableWidgetItem(iter.name));
            m_ptable_strorage->setItem(property->row,0,new QTableWidgetItem(iter.time));
             // m_ptable_strorage->setItem(property->row,2,new QTableWidgetItem(QString::number(price_count)));
            m_ptable_strorage->setItem(property->row,2,new QTableWidgetItem(QString::number(sale_price_count)));
        }
    }
    saleFile.close();

}


