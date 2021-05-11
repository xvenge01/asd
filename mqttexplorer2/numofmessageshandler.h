#ifndef NUMOFMESSAGESHANDLER_H
#define NUMOFMESSAGESHANDLER_H

#include <QObject>

class numofmessageshandler : public QObject
{
    Q_OBJECT
public:
    typedef QHash<QString,int> hashnumSystem;
    explicit numofmessageshandler(QObject *parent = nullptr);




//    hashnumSystem hssys() const;
//    TopicMessage* addnumberTOpic(QString topic,int numberofmsgs);
//    bool deletemsg(QString topic);
//    bool deletetopic(QString topic);
//    TopicMessage* getmsg(QString topic);
//    QList<TopicMessage*> getmsgs(QString topic);


signals:
//    void msgtAdded(TopicMessage *tmsg);
//    void msgRemoved(QString topic);
//    void topicRemoved(QString topic);
//    void  topic_gotten(QString topic);
//    void msgs_for_topic_gotten(QString topic);
signals:

};

#endif // NUMOFMESSAGESHANDLER_H
