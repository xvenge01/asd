#ifndef TOPICCONTAINER_H
#define TOPICCONTAINER_H
#include "topicmessage.h"

#include <QObject>
#include <QHash>
#include <QList>
class topicContainer : public QObject
{
    Q_OBJECT
public:
    typedef QHash<QString, QList<TopicMessage*>> hashSystem;
    typedef QHash<QString,int> hashnumSystem;

    explicit topicContainer(QObject *parent = nullptr);

    hashnumSystem hnumsys() const;
    hashSystem hssys() const;
    TopicMessage* createmsg(QString topic, QByteArray payload);


    void addnumbertotopic(QString topic, int numberofmsgs);
    int getnumberfortopic(QString topic);

    bool deletemsg(QString topic);
    bool deletetopic(QString topic);

    TopicMessage* getmsg(QString topic);
    QList<TopicMessage*> getmsgs(QString topic);


signals:
    void msgtAdded(TopicMessage *tmsg);
    void msgRemoved(QString topic);
    void topicRemoved(QString topic);
    void  topic_gotten(QString topic);
    void msgs_for_topic_gotten(QString topic);
    void num_set(QString topic, int num);
    void num_gotten(QString topic);

public slots:

private:
//    TopicMessages m_tmsglist;
    hashSystem m_hashsys;
    hashnumSystem m_hashnumsys;
    std::mutex mutex;
};

#endif // TOPICCONTAINER_H
