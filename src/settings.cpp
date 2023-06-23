#include "settings.h"

void Settings::read_config(const std::string& configName)
{
    using namespace boost::property_tree;
    ptree pt;
    try {
        read_json(configName, pt);

        auto sender = pt.get_child("sender");
        std::cout << "timeout: " << sender.get<int>("timeout") << std::endl;
        std::cout << "recipients: " << std::endl;
        for (auto& recipient : sender.get_child("recipients")) {
            std::cout << "name_channel: " << recipient.second.get<std::string>("name_channel") << std::endl;
            std::cout << "ip: " << recipient.second.get<std::string>("ip") << std::endl;
            std::cout << "port: " << recipient.second.get<int>("port") << std::endl;
        }
    } catch (const json_parser_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

std::string Settings::find_config_file(const std::string &pathDirConfig)
{
    namespace fs = std::filesystem;
    fs::path path_to_dir = fs::absolute(pathDirConfig);
    std::string path_config_file;
    for (const auto& entry : fs::directory_iterator(path_to_dir))
    {
        if (fs::is_regular_file(entry) && entry.path().filename()=="urt_streamer.conf")
        {
            path_config_file = entry.path().string();
            std::cout << entry.path()<<" "<<entry.file_size()  << std::endl;
            return path_config_file;
        }
    }
    return {};
}

Settings::Settings(const std::string& pathDirConfig)
{
    const std::string configName = find_config_file(pathDirConfig);
    read_config(configName);
}

const Param& Settings::getParam()
{
    return param;
}
