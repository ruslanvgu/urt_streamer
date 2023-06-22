#ifndef READER_H
#define READER_H
#include <iostream>
#include <thread>
#include <list>
//#include <exception>
#include "storage.h"
#include <string>
#include <../boost/asio.hpp>

using namespace std;

class Device
{
public: 
    Device(){}
    virtual void init() = 0;
    virtual void open() = 0;
    virtual void close() = 0;
};

class Fpga : public Device
{
    // Создаем io_service
     boost::asio::io_service io_service;

     // Создаем UART-порт
     boost::asio::serial_port port(io_service);
public:
    Fpga() {}
    void init() override
    {

         // Устанавливаем параметры порта
         //port.open("/dev/ttyS1");
         port.set_option(boost::asio::serial_port_base::baud_rate(115200));
         port.set_option::asio::serial_port_base::character_size(8));
         port.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
         port.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
         port.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));

    }
    void write(const string& message)
    {
        // Отправляем данные через UART-порт
        boost::asio::write(port, boost::asio::buffer(message));
    }

    string read()
    {
        // Получаем данные из UART-порта
        char data[1024];
        size_t length = boost::asio::read(port, boost::asio::buffer(data));
        return string(data, length);
    }

    void open() override
    {
        port.open("/dev/ttyS1");
    }

    void close() override
    {
        port.close();
    }
};



class Reader
{
    list<Fpga> devices;

public:
    Reader();
    void maincycle();
};

#endif // READER_H
