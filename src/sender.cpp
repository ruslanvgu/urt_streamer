#include "sender.h"

Sender::Sender()
{
    //here reading data by channel from .conf file
    string name;
    string ip;
    uint32_t port;
    PROT prot;
    createChannel(name, ip, port, prot);

}

Connection* Sender::getChannel(const string& name)
{
    //select anyone channel by name
    auto found = connections.find(name);
    if(found != connections.end())
        return found->second.get();
    else
        return nullptr;
}


void Sender::createChannel(const string& name, const string& ip, uint32_t port, PROT prot)
{
    switch(prot)
    {
    case PROT::UPD:
    {
        //connections[name]= make_unique<ConnectionUdp>(ip,port);
        unique_ptr<Connection> conn = make_unique<ConnectionUdp>(ip, port);
        connections.insert(std::make_pair(name, std::move(conn)));
        break;
    }

    case PROT::TCP:
    {
        //connections[name]= make_unique<ConnectionTcp>(ip,port);
        unique_ptr<Connection> conn = make_unique<ConnectionTcp>(ip, port);
        connections.insert(std::make_pair(name, std::move(conn)));
        break;
    }

    default:
            std::cout << "Invalid solution" <<std::endl;
        break;
    }

}

