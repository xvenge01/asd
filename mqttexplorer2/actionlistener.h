#ifndef ACTIONLISTENER_H
#define ACTIONLISTENER_H

#include <QObject>
#include "mqtt/async_client.h"

class actionlistener : public QObject,public virtual mqtt::iaction_listener
{
    Q_OBJECT
public:
    explicit actionlistener(const std::string& name,QObject *parent = nullptr);

     void on_failure(const mqtt::token& tok) override ;
      void on_success(const mqtt::token& tok) override ;
signals:
private:
     std::string name_;
};

#endif // ACTIONLISTENER_H
