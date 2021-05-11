#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow( QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addtoTree(QString topic)
{
    QStringList pieces = topic.split( "/" );//topic,/home,/jozo




    QTreeWidgetItem*root;
    QString spracovanytopic;



   //topic/
   for(int i=0;i<pieces.length();i++){

//       QString curtopfile = pieces.at(i);
//       if(curtopfile.contains("=")){
//           curtopfile = curtopfile.split("=").at(0);
//       }

        if(i==0){
            spracovanytopic = pieces.at(i);
            QList<QTreeWidgetItem*> items = ui->treeWidget->findItems(pieces.at(i),Qt::MatchContains, 0);
            if (items.count() == 0) {   // not found, create new entry
                root = new QTreeWidgetItem(ui->treeWidget);
                root->setText(0,pieces.at(0));
                ui->treeWidget->addTopLevelItem(root);
            }
            else {
                int k;
                for(k = 0; k<items.count();k++){
                    if((QString::compare(items.at(k)->data(0,Qt::UserRole).toString(),pieces.at(i)))==0){
                        root = items.at(k);
                        break;
                    }
                }
                if (k>=items.count()){
                    root = new QTreeWidgetItem(ui->treeWidget);
                    root->setText(0,pieces.at(0));
                    ui->treeWidget->addTopLevelItem(root);
                }

            }
        }
        else{
            spracovanytopic = spracovanytopic + QString::fromStdString("/") +pieces.at(i);
           int j=0;
           while(j < root->childCount() && (QString::compare((root->child(j))->data(0,Qt::UserRole).toString(),spracovanytopic)!=0)){
               j++;
           }
           if(j<root->childCount()){
               root= root->child(j);
           }
           else{
               QTreeWidgetItem *child = new QTreeWidgetItem();
               child->setText(0,pieces.at(i));
               root->addChild(child);
               root=child;
           }
        }
       QString notrecievedyet{"not recieved yet"};
       root->setData(0,Qt::UserRole, spracovanytopic);
       root->setData(0,Qt::UserRole+1, notrecievedyet);
   }
//       TopicMessage *tmsg = tpccnt.getmsg(topic);
//       QString payld = QString::fromStdString(tmsg->Payloadmsg().toStdString());
//       root->setText(0,payld);
}

void MainWindow::addtoList(QString msg)
{
    ui->listWidget->addItem(msg);
}

QString MainWindow::getwantedTopic()
{
    return ui->topic->text();
}


QString MainWindow::getServerAdress()
{
    return ui->serveradress->text();
}

QString MainWindow::getClientID()
{
    return ui->clientid->text();
}

void MainWindow::showList()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void MainWindow::showTree()
{
    ui->stackedWidget->setCurrentWidget(ui->msgtree);
}

void MainWindow::getCurrentItemMessages(QString topic)
{
    ui->listWidget->clear();
    QList<TopicMessage*> messages = tpccnt.getmsgs(topic);
    for(int i =0; i< messages.count();i++){
        QString mesg = QString(messages.at(i)->Payloadmsg());
        addtoList(mesg);
    }

}

int MainWindow::getwantednumber()
{
    return ui->numofmsg->text().toInt();
}

void MainWindow::showTopicMenu()
{

    ui->stackedWidget->setCurrentWidget(ui->subscribetopic);
}

void MainWindow::addmsg(QString topic, QByteArray payload)
{
    tpccnt.createmsg(topic,payload);
}

void MainWindow::updateTreeItemValue(QString topic, QByteArray payload)
{
//    getvalue(topic);


    QTreeWidgetItemIterator it(ui->treeWidget);
//    QString wanted;
   while (*it) {
       QString currtopic =  (*it)->data(0,Qt::UserRole).toString();
       if(QString::compare(topic,currtopic)==0){
           (*it)->setData(0, Qt::UserRole+1,payload);
           QString payld =  (*it)->data(0,Qt::UserRole+1).toString();
           QString nameofwitem = currtopic.split("/").last();
           (*it)->setText(0, nameofwitem+"="+payld);
           break;

       }
       ++it;
   }
    getCurrentItemMessages(topic);

}

void MainWindow::popupmsg(QString popupmsg)
{
    Dialog sDialog;
    sDialog.setLabel(popupmsg);
    sDialog.setModal(true);
    sDialog.exec();

}


void MainWindow::gotoSubsribePublish(QString topic)
{
    showPublishSubscribe();
    ui->currenttopic->setText(topic);
}


void MainWindow::showDashboard()
{
    ui->stackedWidget->setCurrentWidget(ui->dashboard);

}


void MainWindow::showPublishSubscribe()
{
    ui->stackedWidget->setCurrentWidget(ui->subscribepublish);
}

void MainWindow::setupConnections()
{
//    connect(ui->actionAdd,SIGNAL(triggered(bool)),this, SLOT(subcribe()));
    connect(ui->actionDashBoard,&QAction::triggered,this,&MainWindow::showDashboard);
    connect(ui->actionshowTopicMsg,&QAction::triggered,this,&MainWindow::showTree);
//    connect(ui->actionaddedtolist,&QAction::triggered,this,&MainWindow::showList);
    connect(ui->actionaddSubscribeTopic,&QAction::triggered,this,&MainWindow::showTopicMenu);
    connect(ui->actionSubscribe_publish_current,&QAction::triggered,this,&MainWindow::showPublishSubscribe);
}

//void MainWindow::setCli(mqtt::async_client *value)
//{
//    cli = value;
//}

void MainWindow::on_pushButton_clicked()
{

    if(cli.get()!=nullptr){
        addtoTree(getwantedTopic());
        addnumber(getwantedTopic(),getwantednumber());
        std::cout<<"Subsrcibing";
    if((*cli.get()).is_connected()){
        std::string topic = getwantedTopic().toStdString();
        mqtt::subscribe_options subOpts;
        subOpts.set_no_local(true);
        auto token = (*cli.get()).subscribe(topic, 1, subOpts);
        std::cout<<"TOPIC: "<<topic;
//        cli->subscribe(TOPIC, 1);
    }
}
    else{
        popupmsg("Client is not defined, needs address from which to get messages");
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->treeWidget->setHeaderLabel(getServerAdress());
    std::string serveradress = getServerAdress().toStdString();
    std::string clientid = getClientID().toStdString();

    mqtt::create_options createOpts;
    createOpts.set_mqtt_verison(5);
    cli = std::make_unique<mqtt::async_client>(serveradress,clientid, createOpts);
    cb = std::make_unique<clbck>(*cli.get(),*connOpts,this);
//    mqtt::async_client client(serveradress, clientid, createOpts);


    connOpts->set_mqtt_version(5);
    connOpts->set_automatic_reconnect(true);
    connOpts->set_clean_start(false);


    (*cli.get()).set_callback(*(cb.get()));
    try {
            std::cout << "Connecting to the MQTT server..." << std::flush;
            std::cout<<"url adresa: "<<(*cli.get()).get_server_uri();
            (*cli.get()).connect(*connOpts);

    }
    catch (const mqtt::exception& exc) {
        std::cerr << "\nERROR: Unable to connect to MQTT server: '"
                  << serveradress << "'" << exc << std::endl;
        exit(1);
    }

}

void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    gotoSubsribePublish(item->data(0,Qt::UserRole).toString());

}



void MainWindow::on_pushButton_3_clicked()
{
    std::cout<<"pushbutton3";
    QString topic = ui->currenttopic->text();
    QString subtopic = ui->lineEdit->text();
    if(topic.isEmpty()){
        topic = subtopic;
    }
    else{
             topic = topic+"/"+subtopic;
    }
    std::cout<<"GET THIS NOW"<<topic.toStdString();

    addtoTree(topic);


    if(cli.get()!=nullptr){
            addtoTree(getwantedTopic());
        std::cout<<"Subsrcibing";
        if((*cli.get()).is_connected()){
            std::string subtopic = (topic).toStdString();
            mqtt::subscribe_options subOpts;
            subOpts.set_no_local(true);
            auto token = (*cli.get()).subscribe(subtopic, 1, subOpts);
            std::cout<<"TOPIC: "<<subtopic;
    //        cli->subscribe(TOPIC, 1);
        }
    }
    else{
        popupmsg("Client is not defined, needs address from which to get messages");
    }

}

void MainWindow::addnumber(QString topic, int number)
{
    tpccnt.addnumbertotopic(topic, number);
}

void MainWindow::on_pushButton_4_clicked()
{
    if(cli.get()!=nullptr){
        std::cout<<"poublsishuing";
    }
    else{
        popupmsg("Client is not defined, needs address from which to get messages");
    }
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    getCurrentItemMessages(item->data(0,Qt::UserRole).toString());
    showList();
}
