#ifndef SENDER_H
#define SENDER_H

#include<boost/asio.hpp>
#include <string>
#include <iostream>
#include <list>
#include <memory>
#include <unordered_map>

using namespace std;
using boost::asio::ip::udp;
using boost::asio::ip::tcp;

class Connection
{
public:
    virtual void send(const string& message)=0;
    virtual void open()=0;
    virtual void close()=0;
    virtual ~Connection(){}
};

class ConnectionUdp : public Connection
{
    boost::asio::io_context io_context; // object for input/output
    udp::socket socket;
    udp::endpoint receiver_endpoint;

public:
    ConnectionUdp(const string& ip, uint32_t port)
        :socket(io_context)
    {
        //definition ip an port
        receiver_endpoint = udp::endpoint(boost::asio::ip::make_address(ip), port);
    }

    void send(const string& message) override
    {
        try
        {
            //send data from udp channel
            socket.send_to(boost::asio::buffer(message), receiver_endpoint);
        } catch(std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    void open()
    {
        //open udp socket
        socket.open(boost::asio::ip::udp::v4());
    }

    void close()
    {
        //close udp channel
        socket.close();
    }
};

class ConnectionTcp : public Connection
{
private:
    boost::asio::io_service io_service;
    tcp::socket socket;
    tcp::endpoint endpoint;

public:
    ConnectionTcp(const string& ip, uint32_t port)
        : socket(io_service)
        , endpoint(boost::asio::ip::address::from_string(ip), port)
    {
    }

    void send(const string& message) override
    {
        try {
            // send message
            boost::asio::write(socket, boost::asio::buffer(message));
        }  catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    void open()
    {
        //open connection
        try{
            socket.connect(endpoint);
        }catch(std::exception& e)
        {
            std::cerr << e.what() <<std::endl;
        }
    }
      /*  try
        {
            if (!connected.load())
            {
                // Ищем хост по имени и порту
                tcp::resolver::query query(host, port);
                tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
                tcp::resolver::iterator end;

                // Пробуем установить соединение с первым попавшимся адресом
                boost::system::error_code error = boost::asio::error::host_not_found;
                while (error && endpoint_iterator != end)
                {
                    socket.close();
                    socket.connect(*endpoint_iterator++, error);
                }
                if (error)
                {
                    throw boost::system::system_error(error);
                }
                connected.store(true);
            }

            connected.store(false);//??
        }
        catch (const std::exception& e)
        {
            std::cerr << "ConnectionTcp: Exception caught in open(): " << e.what() <<::endl;
        }
    }*/

    void close()
    {
        //close connection
        try{
            socket.close();
        }catch(std::exception& e)
        {
            std::cerr << e.what() <<std::endl;
        }
    }
};


enum class PROT{
    NONE = 0,
    UPD,
    TCP
};

class Sender
{
    unordered_map<string, unique_ptr<Connection>> connections;
    void createChannel(const string& name, const string& ip, uint32_t port, PROT prot);

public:
    Sender();
    Connection* getChannel(const string& name);

};

#endif // SENDER_H
