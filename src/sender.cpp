#include "sender.h"

Sender::Sender()
{
    //here reading data by channel from .conf file
}

unique_ptr<Connection> Sender::getChannel()
{
    //select anyone channel
    return {};
}

void Sender::createChannel(const string& ip, uint32_t port, PROT prot)
{
    switch(prot)
    {
    case PROT::UPD:
            connections.push_back( make_unique<ConnectionUdp>(ip,port));
        break;

    case PROT::TCP:
            connections.push_back( make_unique<ConnectionTcp>(ip,port));
        break;

    default:
            std::cout << "Invalid solution" <<std::endl;
        break;
    }

}

