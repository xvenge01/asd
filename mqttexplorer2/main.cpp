#include "mainwindow.h"
#include "topiccontainer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


//    QString topic{"topic"};
//    topicContainer tpccnt;

//    QString topic2{"topic2"};
//    QByteArray data(2,'a');
//    tpccnt.createmsg(topic2,data);

//    TopicMessage *tpmsg = tpccnt.getmsg(topic2);

//    TopicMessage *tpmsg2 = tpccnt.getmsg(topic);

    w.show();
    return a.exec();
}
