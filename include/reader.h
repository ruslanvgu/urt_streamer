#ifndef READER_H
#define READER_H
#include <iostream>
#include <thread>
#include <list>
#include <string>
#include <boost/asio.hpp>
//#include <boost/asio/ip/network_v4.hpp>
//#include <boost/process.hpp>
#include <boost/filesystem.hpp>
#include "storage.h"
#include "settings.h"
#include <fcntl.h>

using namespace std;

class Device
{
public: 
    Device(){}
    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
    virtual void send_data(std::vector<unsigned char> data) = 0;
    virtual std::vector<unsigned char> receive_data(int size) = 0;
};

class UrtDevice : public Device
{
private:
  std::string device_;
  int frequency_;
  int fd_;

public:
    UrtDevice(std::string device/*, int frequency*/){
        device_ = device;
    }

    bool connect() {
        fd_ = open(device_.c_str(), O_RDWR);
        return fd_ != -1;
    }

    void send_data(std::vector<unsigned char> data){}
    std::vector<unsigned char> receive_data(int size){}
    bool disconnect(){}

};
/*
class Fpga : public Device
{
    // Создаем io_service
     boost::asio::io_service io_service;

     // Создаем UART-порт
     boost::asio::serial_port port;
public:
    Fpga(): port(io_service) {}
    void init() override
    {

         // Устанавливаем параметры порта
         //port.open("/dev/ttyS1");
         port.set_option(boost::asio::serial_port_base::baud_rate(115200));
         port.set_option(boost::asio::serial_port_base::character_size(8u));
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
*/
/*void printMacAddress1(const std::string& ip_address)
{
        boost::asio::io_context io_context;
      boost::asio::ip::tcp::socket socket(io_context, boost::asio::ip::tcp::v4());

      boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::from_string("8.8.8.8"), 80);
      socket.connect(endpoint);

      boost::asio::ip::tcp::socket::native_handle_type socket_handle = socket.native_handle();

      struct ifreq ifr;
      memset(&ifr, 0, sizeof(ifr));
      strcpy(ifr.ifr_name, "eth0");

      if (ioctl(socket_handle, SIOCGIFHWADDR, &ifr) == -1)
      {
        std::cerr << "Failed to get MAC address for eth0" << std::endl;
        return ;
      }

      unsigned char* mac_address = reinterpret_cast<unsigned char*>(ifr.ifr_hwaddr.sa_data);

      std::printf("MAC address for eth0: %02x:%02x:%02x:%02x:%02x:%02x\n",
                  mac_address[0], mac_address[1], mac_address[2],
                  mac_address[3], mac_address[4], mac_address[5]);


}*/

class Reader
{
    list<UrtDevice> devices;

    string read_file(const boost::filesystem::path& path);
    void  find_urt_device(const std::string& dirDevicePath); // /dev
public:
    Reader();
    void cycle_read_device();
};

#endif // READER_H
