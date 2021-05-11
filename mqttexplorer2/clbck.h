#ifndef clbck_H
#define clbck_H

#include <QThread>
#include "mqtt/async_client.h"
#include "actionlistener.h"
//#include "mainwindow.h"

class MainWindow;
class clbck : public QThread, public virtual mqtt::callback, public virtual mqtt::iaction_listener
{
    Q_OBJECT
public:
    explicit clbck(mqtt::async_client& cli,
                      mqtt::connect_options& connOpts, MainWindow *window,
                      QObject *parent = nullptr
            );
    void delivery_complete(mqtt::delivery_token_ptr token) override;
    void connection_lost(const std::string& cause) override;
    void reconnect() ;
    void connected(const std::string& cause) override ;
    void on_failure(const mqtt::token& tok) override;
     void on_success(const mqtt::token& tok) override;
     void message_arrived(mqtt::const_message_ptr msg) override;

signals:

public slots:

private:
    // The MQTT client
    mqtt::async_client& cli_;
    // Options to use if we need to reconnect
    mqtt::connect_options& connOpts_;
    // An action listener to display the result of actions.
   actionlistener subListener_;
   int  nretry_=0;
   MainWindow *main_window;
};

#endif // clbck_H
