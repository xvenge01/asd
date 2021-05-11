#include "actionlistener.h"

actionlistener::actionlistener(const std::string& name,QObject *parent) : name_(name),QObject(parent)
{

}

void actionlistener::on_failure(const mqtt::token &tok)
{
    std::cout << name_ << " failure";
           if (tok.get_message_id() != 0)
               std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
           std::cout << std::endl;
}

void actionlistener::on_success(const mqtt::token &tok)
{
    std::cout << name_ << " success";
           if (tok.get_message_id() != 0)
               std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
           auto top = tok.get_topics();
           if (top && !top->empty())
               std::cout << "\ttoken topic: '" << (*top)[0] << "', ..." << std::endl;
           std::cout << std::endl;
}
