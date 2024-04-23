#include "widget.h"

#include <QDebug>
#include <QSqlQuery>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    //1.整体采用水平布局
    QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setSpacing(10);
    horizontalLayout->setContentsMargins(0,0,0,0);

    //2.导航窗口 在左侧
    navWidget = new QWidget(this);
    QVBoxLayout* leftlayout = new QVBoxLayout(navWidget);
    leftlayout->setSpacing(0);
    leftlayout->setContentsMargins(0,0,0,0);

    horizontalLayout->addWidget(navWidget);

    //3.主窗体添加 在右侧
    mainWidget = new QWidget(this);
    mainWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    mainWidget->setMinimumWidth(800);
    mainWidget->setMinimumHeight(500);
    QVBoxLayout* rightLayout = new QVBoxLayout(mainWidget);
    rightLayout->setSpacing(10);
    rightLayout->setContentsMargins(0,0,0,0);
    stackedWidget =new QStackedWidget(mainWidget);
    rightLayout->addWidget(stackedWidget);
    horizontalLayout->addWidget(mainWidget);

    initNav();
    initMain();

}

Widget::~Widget() {}

//初始化菜单框
void Widget::initNav()
{
    QStringList names;
    names << u8"入库登记"
          << u8"出库登记"
          << u8"库存管理"
          << u8"收益明细";

    btnGroup = new QButtonGroup(this);

    //自动生成按钮
    for ( int i = 0; i < names.count(); i++ ) {
        QPushButton* btn = new QPushButton;

        //设置按钮固定高度
        btn->setMinimumHeight(60);

        //设置按钮的文字
        btn->setText(QString("%1. %2").arg(i + 1, 2, 10, QChar('0')).arg(names.at(i)));

        //设置按钮可选中按下类似复选框的功能
        btn->setCheckable(true);

        // 设置按钮的样式
        navWidget->setStyleSheet(R"(
            QPushButton {
                    font: 25px;
                    text-align : left;
            }
        )");

        // 将按钮添加到 btnGroup
        btnGroup->addButton(btn, i);

        //将按钮加入到布局
        navWidget->layout()->addWidget(btn);

        connect(btn,SIGNAL(clicked(bool)),this,SLOT(buttonclicked()));
    }

    btnGroup->button(0)->click();
}

//初始化mainwindows右侧
void Widget::initMain()
{
    m_psaleProduct= new saleproduct();
    m_pinventory = new inventory();
    m_pstrorageProduct = new productStrorage();
    stackedWidget->addWidget(m_pstrorageProduct);
    stackedWidget->addWidget(m_psaleProduct);
    stackedWidget->addWidget(m_pinventory);
    stackedWidget->addWidget(new earnings());


    connect(m_psaleProduct,&saleproduct::sig_flushTableitem,m_pinventory,&inventory::tableWidgetFlush);
    connect(m_pstrorageProduct,&productStrorage::sig_flushTableitem,m_pinventory,&inventory::tableWidgetFlush);
}

//哪个左侧按钮被按下，右侧就显示哪个界面
void Widget::buttonclicked()
{
    // qDebug()<<"buttonclicked";
    int index = btnGroup->checkedId();
    // qDebug()<<"index:"<<index;
    stackedWidget->setCurrentIndex(index);
}

void Widget::saveProfile()
{

}
