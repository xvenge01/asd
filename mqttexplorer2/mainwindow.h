#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mqtt/async_client.h"
#include "clbck.h"
#include "topiccontainer.h"
#include <QTreeWidget>
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = nullptr);
    ~MainWindow();

    void addtoTree(QString topic);
    void addtoList(QString msg);

    QString getwantedTopic();
    QString getServerAdress();
    QString getClientID();
//    TopicMessage*addmsg(QString topic, QByteArray payload);

//    void setCli(mqtt::async_client *value);
    void getvalue(QString topic);

public slots:
        void gotoSubsribePublish(QString topic);
        void showDashboard();
        void showPublishSubscribe();
        void showTree();
        void getCurrentItemMessages(QString topic);

        void addnumber(QString topic, int number);
        int getwantednumber();
        void showList();
        void showTopicMenu();
        void addmsg(QString topic, QByteArray payload);
        void updateTreeItemValue(QString topic,QByteArray payload);
        void popupmsg(QString popupmsg);

private slots:
        void on_pushButton_clicked();
        void on_pushButton_2_clicked();
        void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
        void on_pushButton_4_clicked();
//        void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

        void on_pushButton_3_clicked();

        void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    topicContainer tpccnt;
//    systopiccontainer *systpc;
    void setupConnections();
    std::unique_ptr<mqtt::async_client> cli;
    std::unique_ptr<clbck> cb;
    mqtt::connect_options *connOpts = new mqtt::connect_options;
//    mqtt::async_client *cli;
//    clbck *callbck;
};
#endif // MAINWINDOW_H
