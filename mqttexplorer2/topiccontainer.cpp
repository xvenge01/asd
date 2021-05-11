#include "topiccontainer.h"

topicContainer::topicContainer(QObject *parent) : QObject(parent)
{
    std::cout<<"creating topiccontainer, creator0";
}

topicContainer::hashSystem topicContainer::hssys() const
{
    return m_hashsys;
}

//topicContainer::TopicMessages topicContainer::tmsglist() const
//{
//    return m_tmsglist;
//}

TopicMessage *topicContainer::createmsg(QString topic, QByteArray payload)
{
    std::lock_guard<std::mutex> lock(mutex);
    std::cout<<"creating message with name :" <<topic.toStdString();

    auto result = new TopicMessage();
    QList<TopicMessage*> tmpmesg;
    if(m_hashsys.isEmpty()){
        std::cout<<"hasmap is empty";
    }
    if(result != nullptr){
        result->setTopicname(topic);
        result->setPayloadmsg(payload);

        if(m_hashsys.contains(topic)){

                tmpmesg = m_hashsys.value(topic);
                   if(tmpmesg.count()>=m_hashnumsys.value(topic)){
                       tmpmesg.pop_front();
                   }
//            QList<TopicMessage*> tmpmesg((*m_hashsys)value(topic));
                tmpmesg.append(result);
                m_hashsys.insert(result->Topicname(),tmpmesg);
//            emit msgtAdded(result);
        }
        else{
            if(tmpmesg.count()>=m_hashnumsys.value(topic)){
                tmpmesg.pop_front();
            }
            tmpmesg.append(result);
            m_hashsys.insert(result->Topicname(),tmpmesg);

        }
    }
    emit msgtAdded(result);
    return result;
}

void topicContainer::addnumbertotopic(QString topic, int numberofmsgs)
{
    std::lock_guard<std::mutex> lock(mutex);
    m_hashnumsys.insert(topic,numberofmsgs);
    emit num_set(topic, numberofmsgs);
}

int topicContainer::getnumberfortopic(QString topic)
{
    std::lock_guard<std::mutex> lock(mutex);
    return m_hashnumsys.value(topic);
     emit num_gotten(topic);
}

bool topicContainer::deletemsg(QString topic)
{

    return false;
}

bool topicContainer::deletetopic(QString topic)
{
    return false;
}


QList<TopicMessage*> topicContainer::getmsgs(QString topic)
{
    std::lock_guard<std::mutex> lock(mutex);//maybeunnecesarry

    return m_hashsys.value(topic);
    emit msgs_for_topic_gotten(topic);

}


TopicMessage *topicContainer::getmsg(QString topic)
{
    std::lock_guard<std::mutex> lock(mutex);
    if(m_hashsys.contains(topic)){
        return m_hashsys.value(topic).last();
        emit topic_gotten(topic);
    }
    return nullptr;
}

