#ifndef SENDER_H
#define SENDER_H

#include<boost/asio.hpp>
#include <string>
#include <iostream>
#include <list>
#include <memory>

using namespace std;
using boost::asio::ip::udp;
using boost::asio::ip::tcp;

class Connection
{

public:
    virtual void send(const string& message)=0;
    virtual ~Connection(){}
};

class ConnectionUdp : public Connection
{
    boost::asio::io_context io_context;
    udp::socket socket;
    udp::endpoint receiver_endpoint;

public:
    ConnectionUdp()
        :socket(io_context, udp::endpoint(udp::v4(), 0))
    {
        receiver_endpoint = udp::endpoint(boost::asio::ip::make_address("127.0.0.1"), 12345);
    }
    void send(const string& message) override
    {
        socket.send_to(boost::asio::buffer(message), receiver_endpoint);
    }
};

class ConnectionTcp : public Connection
{
private:
    boost::asio::io_service io_service;
    tcp::resolver resolver;
    tcp::socket socket;
    std::string host; // хост получателя
    std::string port; // порт получателя
    std::atomic<bool> connected{ false };

public:
    ConnectionTcp(const std::string& host_, const std::string& port_)
        : resolver(io_service)
        , socket(io_service)
        , host(host_)
        , port(port_)
    {}

    void send(const string& message) override
    {
        // Посылаем сообщение
        boost::asio::write(socket, boost::asio::buffer(message));
    }

    void open()//??
    {
        try
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
    }

    void close()
    {
        socket.close();
    }
};

class Sender
{
    //boost::asio::io_service io_service;
    list<unique_ptr<Connection>> connections;
public:
    Sender();
    void createChannel();
};

#endif // SENDER_H
