#include "clbck.h"
#include "mainwindow.h"

clbck::clbck(mqtt::async_client& cli, mqtt::connect_options& connOpts, MainWindow *ui
                    ,QObject *parent) :  QThread(parent),
    cli_(cli), connOpts_(connOpts),
    subListener_("Subscription"), main_window(ui)
{
    std::cout<<"Created clbck"<<cli.get_server_uri()<<"    "<< currentThread();
}

void clbck::message_arrived(mqtt::const_message_ptr msg)
{
    std::cout << "Message arrived" << std::endl;
    std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
    std::cout << "\tpayload: '" << msg->to_string() << "'\n" << std::endl;
    std::cout<<"PRIDAVAM TOPIC, msg";
//    main_window->addtoList(QString::fromStdString(msg->get_topic()));

    QByteArray data(msg->to_string().c_str(),msg->to_string().size());

//    emit messagerecieved(QString::fromStdString(msg->get_topic()),data);
    main_window->addmsg(QString::fromStdString(msg->get_topic()),data);
    main_window->updateTreeItemValue(QString::fromStdString(msg->get_topic()),data);
//    main_window->addtoTree(QString::fromStdString(msg->get_topic()));//wrong wokr with threads
}

void clbck::delivery_complete(mqtt::delivery_token_ptr token)
{
    std::cout<<"delivery complete";
}

void clbck::connection_lost(const std::string &cause)
{
    std::cout << "\nConnection lost" << std::endl;
    if (!cause.empty())
       std::cout << "\tcause: " << cause << std::endl;

    std::cout << "Reconnecting..." << std::endl;
    reconnect();
}

void clbck::reconnect()
{
   std::cout<<"reconnecting";
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
            try {
                cli_.connect(connOpts_, nullptr, *this);
            }
            catch (const mqtt::exception& exc) {
                std::cerr << "Error: " << exc.what() << std::endl;
                exit(1);
    }
}

void clbck::connected(const std::string &cause)
{
    std::cout << "\nConnection success" << std::endl;
}

void clbck::on_failure(const mqtt::token &tok)
{
//    std::cout << "Connection attempt failed" << std::endl;
    std::cout << "Connection attempt failed" << std::endl;
            if (++nretry_ > 5)
                exit(1);
            reconnect();
}

void clbck::on_success(const mqtt::token &tok)
{
    std::cout << "SUCCESS connection";
}
