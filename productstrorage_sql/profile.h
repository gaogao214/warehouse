#ifndef PROFILE_H
#define PROFILE_H
#include <QObject>
#include <ActiveQt/QAxObject>
#include <QWidget>


namespace sql_struct {
struct tableWidget_data
{
    QString name;
    QString time;
    int price;
    int num;
    int price_count;
};
}

class Profile:public QWidget
{
    Q_OBJECT
public:
    Profile();

public:
    void readProfile(QString filename,int strorageSale = 0);//strorage = 0,入库; =1出库
    void writeProfile(QString filename,QString name,QString time,QString price,QString num,QString count);
    void clearProfile(QString filename);

signals:
    void sig_readStrorageProfile(QStringList str);
    void sig_readSaleProfile(QStringList str);

public:
    QString m_pstrorageProfileName = "C:/Users/gaohuan/Documents/data/strorage_data.csv";
    QString m_psaleProfileName = "C:/Users/gaohuan/Documents/data/sale_data.csv";

    QString strData;
    QString str;

    int count = 0 ;

};

#endif // PROFILE_H
