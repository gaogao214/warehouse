#include "widget.h"

#include <QApplication>
#include "src/easylogging++.h"

INITIALIZE_EASYLOGGINGPP
int main(int argc, char *argv[])
{
    el::Configurations conf("my_log.conf");
    el::Loggers::reconfigureAllLoggers(conf);
    // LOG(INFO) << "========================软件启动========================";
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
