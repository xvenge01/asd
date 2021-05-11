#include "topicmessage.h"

TopicMessage::TopicMessage(QObject *parent) :QObject(parent)
{

}

QString TopicMessage::Topicname() const
{
    return m_topicname;
}


void TopicMessage::setTopicname(const QString &value)
{
    if(m_topicname != value){
        std::cout<<"setting name in topicmessage";
        m_topicname = value;
        emit TopicnameChanged();
    }
}

QByteArray TopicMessage::Payloadmsg() const
{
    return m_payloadmsg;
}

void TopicMessage::setPayloadmsg(const QByteArray &value)
{
    std::cout<<"setting payload in topicmessage";
    if(m_payloadmsg != value){
        m_payloadmsg = value;
        emit PayloadmsgChanged();
    }
}





//std::stack<mqtt::const_message_ptr> TopicMessage::getMessageStack(const std::string &topic)
//{
//    std::lock_guard<std::mutex> lock(mutex);
//    std::cout<<"before accessing umap"<<std::endl;
//    std::stack<mqtt::const_message_ptr> stck(umap.at(topic));
//    std::cout<<"after accessing umap"<<std::endl;
//    return stck;
//}

//void TopicMessage::put(std::string topic, mqtt::const_message_ptr &msg)
//{
//    std::lock_guard<std::mutex> lock(mutex);
//    std::cout<<"PRIDAVAM (topic): "<<msg->get_topic()<<std::endl;
//    std::cout<<"Message (topic): "<<msg->to_string()<<std::endl;

//    if(umap.find(topic) != umap.end()) {
//      std::cout<<"Nachadza sa v pute, v hash tab";
//      std::stack<mqtt::const_message_ptr> stck(umap.at(topic));
//      stck.push(msg);
//      umap.insert({topic,stck});
//    }
//    else{
//      std::cout<<"CREATUJEM NOVY STACK";
//      std::stack<mqtt::const_message_ptr>* stck = new std::stack<mqtt::const_message_ptr>;
//      stck->push(msg);
//      umap.insert({topic,*stck});
//    }
//}


