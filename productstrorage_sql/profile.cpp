#include "profile.h"

#include <QFileDialog>
#include <QDateTime>
#include <QTextStream>
#include <QDebug>
Profile::Profile()
{

}


void Profile::readProfile(QString filename , int strorageSale )
{
    // qDebug()<<"read profile :"<<filename<<"\n";
    QString filePath = filename;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;

    QTextStream stream(&file);
    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        QStringList row = line.split(',', Qt::SkipEmptyParts);
        // data.append(row);

        if(count > 0)
        {
            // qDebug()<<"row"<<row;
            if(strorageSale == 0){
                emit sig_readStrorageProfile(row);
            }else if(strorageSale == 1){
                sig_readSaleProfile(row);
            }
        }
        count = 1;
    }
    file.close();
    return ;
}

void Profile::writeProfile(QString filename,QString name,QString time,QString price,QString num,QString count)
{

    //1.选择导出的csv文件保存路径
    QString csvFile = filename;
    if(csvFile.isEmpty())
        return;

    //3.用QFile打开.csv文件 如果不存在则会自动新建一个新的文件
    QFile file(csvFile);
    if ( file.exists())
    {
        //如果文件存在执行的操作，此处为空，因为文件不可能存在
        file.open( QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);

        QTextStream out(&file);

        //其他数据可按照这种方式进行添加即可
        name = name + ",";
        time = time = tr("%1").arg(time);
        price = "," + price + ",";
        num = num + ",";
        count = count + ",";
        out<<name<<time<<price<<num<<count<<"\n";

        qDebug()<<"text stream :"<<name<<time<<price<<num<<count;

        //5.写完数据需要关闭文件
        file.close();
    }
    else
    {
        file.open( QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);
        // statusBar()->showMessage(tr("正在导出数据。。。。。。"));
        QTextStream out(&file);

        //4.获取数据 创建第一行
        out<<tr("商品名称,")<<tr("入库时间,")<<tr("入库价格,")<<tr("入库数量,")<<tr("入库总价,\n");//表头
        //其他数据可按照这种方式进行添加即可
        name = name + ",";
        time = tr("%1").arg(time) ;
        price = "," + price + ",";
        num = num + ",";
        count = count + ",";
        out<<name<<time<<price<<num<<count<<"\n";
        qDebug()<<"text stream :"<<name<<time<<price<<num<<count;

        //5.写完数据需要关闭文件
        file.close();
    }
}

void Profile::clearProfile(QString filename)
{
    QFile file(filename);
    file.close();
    file.remove();

    //1.选择导出的csv文件保存路径
    QString csvFile = filename;
    if(csvFile.isEmpty())
        return;

    //3.用QFile打开.csv文件 如果不存在则会自动新建一个新的文件
    QFile file_1(filename);
    if ( !file.exists())
    {
        file.open( QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);
        // statusBar()->showMessage(tr("正在导出数据。。。。。。"));
        QTextStream out(&file);

        //4.获取数据 创建第一行
        out<<tr("商品名称,")<<tr("入库时间,")<<tr("入库价格,")<<tr("入库数量,")<<tr("入库总价,\n");//表头
        //其他数据可按照这种方式进行添加即可
        //5.写完数据需要关闭文件
        file.close();
    }
}


