/**
 * @brief The Settings class contain data from .conf file
 */
#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <iostream>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <filesystem>

// make singlton

class Param{
    class ModuleSender{
        class Recipient{
            std::string _name_channel;
            std::string _ip;
            uint32_t _port;
        public:
            Recipient(const std::string& name_channel,std::string& ip, uint32_t port)
                :_name_channel(name_channel)
                ,_ip(ip)
                ,_port(port)
            {}
        };
        std::vector<Recipient> recipients;
    public:
        ModuleSender()
        {}
    };
    ModuleSender sender;

    class ModuleReader{
    public:
        ModuleReader()
        {}
    };
    ModuleReader reader;

public:
    Param()
    {}
};

class Settings
{
    Param param;
    std::string find_config_file(const std::string& pathDirConfig);
    void read_config(const std::string& configName);

public:
    Settings(const std::string& pathDirConfig );
    const Param& getParam();
};

#endif // SETTINGS_H
