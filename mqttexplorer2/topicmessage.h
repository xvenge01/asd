#ifndef TOPICMESSAGE_H
#define TOPICMESSAGE_H

#include <QObject>
#include <QString>
#include <mutex>
#include "mqtt/async_client.h"
#include <unordered_map>

#include <stack>
#include <QByteArray>
#include <QString>

class TopicMessage : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString Topicname READ Topicname WRITE setTopicname NOTIFY TopicnameChanged)
    Q_PROPERTY(QByteArray Payloadmsg READ Payloadmsg WRITE setPayloadmsg NOTIFY PayloadmsgChanged)

public:
    explicit TopicMessage(QObject *parent = nullptr);

    QString Topicname() const;
    void setTopicname(const QString &value);

    QByteArray Payloadmsg() const;
    void setPayloadmsg(const QByteArray &value);

signals:
    void TopicnameChanged();
    void PayloadmsgChanged();



private:
    QString m_topicname;
    QByteArray m_payloadmsg;
};

#endif // TOPICMESSAGE_H
