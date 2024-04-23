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

    m_ptable_strorage = new QTableWidget();
    m_ptable_strorage->resize(900,500);
    // m_ptable_strorage->setRowCount(6);//行数
    m_ptable_strorage->setColumnCount(3);//列数
    m_ptable_strorage->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    m_ptable_strorage->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    m_ptable_strorage->setHorizontalHeaderLabels(QStringList()<<"商品名称"<<"库存量"<<"报警阈值");
    vlayout->addWidget(m_ptable_strorage);

    tableWidgetShow();
}

void inventory::tableWidgetShow()
{
    qDebug()<<"tableWidgetShow\n";
    QString strorage_filename = m_pstrorageProfileName;
    QString sale_filename = m_psaleProfileName;

    int strorage_count = 0;
    int sale_count = 0;
    int RowCont;

    QFile strorageFile(strorage_filename);
    if (!strorageFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;

    QFile saleFile(sale_filename);
    if (!saleFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;

    QTextStream strorageStream(&strorageFile);
    QTextStream saleStream(&saleFile);

    while (!strorageStream.atEnd())
    {
        QString line = strorageStream.readLine();
        QStringList row = line.split(',', Qt::SkipEmptyParts);
        m_pstrorage_name =row[0];
        m_pstrorage_num =row[3];
        if(strorage_count > 0)
        {
            m_pstrorageInventory.name = m_pstrorage_name;
            m_pstrorageInventory.num = m_pstrorage_num;
            m_pstrorageVector.push_back(m_pstrorageInventory);
        }
         strorage_count = 1;
    }

    while (!saleStream.atEnd())
    {
        QString line = saleStream.readLine();
        QStringList row = line.split(',', Qt::SkipEmptyParts);
        m_psale_name =row[0];
        m_psale_num =row[3];

        if(sale_count > 0)
        {
            // qDebug()<<"m_psale_name:"<<m_psale_name<<"num:"<<m_psale_num<<"\n";
            // m_psaleMap.insert(m_psale_name,m_psale_num);
            m_psaleInventory.name = m_psale_name;
            m_psaleInventory.num = m_psale_num;
            m_psaleVector.push_back(m_psaleInventory);
        }
        sale_count = 1;
    }

    if(m_psaleVector.empty())
    {
        for(auto iter : m_pstrorageVector)
        {
            m_ptable_strorage->insertRow(RowCont);//增加一行
            m_ptable_strorage->setItem(RowCont,0,new QTableWidgetItem(iter.name));
            m_ptable_strorage->setItem(RowCont,1,new QTableWidgetItem(iter.num));

            m_pflushInventory.name = iter.name;
            m_pflushInventory.num = iter.num;
            m_pflushInventory.row = RowCont;

            m_pflushVector.push_back(m_pflushInventory);
        }
    }

    for(auto iter : m_pstrorageVector)
    {
        auto property = std::find_if(m_psaleVector.begin(), m_psaleVector.end(), [&](auto file) {return file.name == iter.name; });
        if (property == m_psaleVector.end())
        {
            qDebug()<<"没有找到key值"<<"iter.begin:"<<iter.name<<"iter.end:"<<iter.num<<"\n";
            RowCont=m_ptable_strorage->rowCount();
            m_ptable_strorage->insertRow(RowCont);//增加一行
            m_ptable_strorage->setItem(RowCont,0,new QTableWidgetItem(iter.name));
            m_ptable_strorage->setItem(RowCont,1,new QTableWidgetItem(iter.num));

            m_pflushInventory.name = iter.name;
            m_pflushInventory.num = iter.num;
            m_pflushInventory.row = RowCont;

            m_pflushVector.push_back(m_pflushInventory);
        }
        else
        {
            qDebug()<<"找到key值"<<"property.name:"<<property->name<<"iter.end:"<<property->num<<"\n";
            int inventory_num = iter.num.toInt() - property->num.toInt();
            RowCont=m_ptable_strorage->rowCount();
            m_ptable_strorage->insertRow(RowCont);//增加一行
            m_ptable_strorage->setItem(RowCont,0,new QTableWidgetItem(iter.name));
            m_ptable_strorage->setItem(RowCont,1,new QTableWidgetItem(QString::number(inventory_num)));

            m_pflushInventory.name = iter.name;
            m_pflushInventory.num = iter.num;
            m_pflushInventory.row = RowCont;

            m_pflushVector.push_back(m_pflushInventory);
        }
    }

    strorageFile.close();
    saleFile.close();
}

void inventory::tableWidgetFlush()
{
    qDebug()<<"tableWidgetFlush\n";

    m_psaleVector.clear();
    m_pstrorageVector.clear();

    QString strorage_filename = m_pstrorageProfileName;
    QString sale_filename = m_psaleProfileName;

    int strorage_count = 0;
    int sale_count = 0;
    int RowCont = 0;

    //将出库入库配置文件进行存储到数组中，用于下面计算
    QFile strorageFile(strorage_filename);
    if (!strorageFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;

    QFile saleFile(sale_filename);
    if (!saleFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;

    QTextStream strorageStream(&strorageFile);
    QTextStream saleStream(&saleFile);
    while (!strorageStream.atEnd())
    {
        QString line = strorageStream.readLine();
        QStringList row = line.split(',', Qt::SkipEmptyParts);
        m_pstrorage_name =row[0];
        m_pstrorage_num =row[3];
        if(strorage_count > 0)
        {
            m_pstrorageInventory.name = m_pstrorage_name;
            m_pstrorageInventory.num = m_pstrorage_num;
            m_pstrorageInventory.row = strorage_count;
            m_pstrorageVector.push_back(m_pstrorageInventory);
        }
        strorage_count ++;
    }
    while (!saleStream.atEnd())
    {
        QString line = saleStream.readLine();
        QStringList row = line.split(',', Qt::SkipEmptyParts);
        m_psale_name =row[0];
        m_psale_num =row[3];

        if(sale_count > 0)
        {
            m_psaleInventory.name = m_psale_name;
            m_psaleInventory.num = m_psale_num;
            m_psaleVector.push_back(m_psaleInventory);
        }
        sale_count = 1;
    }

    for(auto iter:m_pflushVector)
    {
        auto rm_profile = std::find_if(m_pstrorageVector.begin(),m_pstrorageVector.end(),[&](auto rm){return rm.name == iter.name;});

        if(rm_profile == m_pstrorageVector.end())
        {
            qDebug()<<"000000"<<iter.row;
            m_ptable_strorage->removeRow(iter.row);
            // m_pflushVector.erase(m_pflushVector.begin() + iter.row);
        }
    }

    for(auto iter : m_pstrorageVector)
    {
        //根据入库的产品计算出库产品的数量
        auto property = std::find_if(m_psaleVector.begin(), m_psaleVector.end(), [&](auto file) {return file.name == iter.name; });
        if (property != m_psaleVector.end())
        {
            //找到相同名称的行数，直接在所在行数进行修改库存数量
            auto it = std::find_if(m_pflushVector.begin(), m_pflushVector.end(), [&](auto file) {return file.name == property->name; });
            if (it != m_pflushVector.end())
            {
                int inventory_num = iter.num.toInt() - property->num.toInt();
                m_ptable_strorage->setItem(it->row,1,new QTableWidgetItem(QString::number(inventory_num)));
            }
        }
        else {
            //找到相同名称的行数，直接在所在行数进行修改库存数量
            auto it = std::find_if(m_pflushVector.begin(), m_pflushVector.end(), [&](auto file) {return file.name == iter.name; });
            if (it == m_pflushVector.end())
            {
                RowCont=m_ptable_strorage->rowCount();
                m_ptable_strorage->insertRow(RowCont);//增加一行
                m_ptable_strorage->setItem(RowCont,0,new QTableWidgetItem(iter.name));
                m_ptable_strorage->setItem(RowCont,1,new QTableWidgetItem(iter.num));

                m_pflushInventory.name = iter.name;
                m_pflushInventory.num = iter.num;
                m_pflushInventory.row = RowCont;

                m_pflushVector.push_back(m_pflushInventory);
            }

        }
    }
    strorageFile.close();
    saleFile.close();
}
