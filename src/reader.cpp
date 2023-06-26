#include "reader.h"

string Reader::read_file(const boost::filesystem::path &path)
{
    namespace fs = boost::filesystem;

    fs::ifstream inFile(path, std::ios::in | std::ios::binary);
    std::vector<char> buffer;
    if (inFile.is_open())
    {
        inFile.seekg(0, std::ios::end);
        buffer.resize(inFile.tellg());
        inFile.seekg(0, std::ios::beg);
        inFile.read(&buffer[0], buffer.size());
        inFile.close();
    }
    else {
        std::cerr << "Unable to open file";
    }

    return string(buffer.begin(),buffer.end());
}

void Reader::find_urt_device(const string &dirDevicePath)
{
    namespace fs = boost::filesystem;
    list<fs::path> result;

    fs::path dirPath(dirDevicePath);
    if (!fs::exists(dirPath))
    {
        return ;
    }

    /*for (fs::directory_iterator dirIt(path); dirIt != fs::directory_iterator(); ++dirIt)
    {
        const fs::path devicePath = dirIt->path();
        const fs::path idVendorPath = devicePath / "idVendor";
        const fs::path idProductPath = devicePath / "idProduct";
        const fs::path bDeviceClassPath = devicePath / "bDeviceClass";
        cout << devicePath.string() << " " << idProductPath.string() << " " << bDeviceClassPath.string()<<endl;
        if (!fs::exists(idVendorPath) || !fs::exists(idProductPath) || !fs::exists(bDeviceClassPath))
        {
            continue;
        }

        const std::string idVendor = read_file(idVendorPath).c_str();
        const std::string idProduct = read_file(idProductPath).c_str();
        const std::string bDeviceClass = read_file(bDeviceClassPath).c_str();
        cout << devicePath <<" idVendor:" <<idVendor<<" idProduct:"<< idProduct << " bDeviceClass:"<< bDeviceClass<< endl;
    }*/
    for(fs::directory_iterator dirIt(dirPath); dirIt != fs::directory_iterator(); ++dirIt)
    {
        const fs::path devicePath = dirIt->path();
        const string fileName = devicePath.filename().string();

       size_t pos = fileName.find("urt_");
       if( pos != std::string::npos ){
            UrtDevice device(devicePath.string());
            if(device.connect()){
                devices.push_back(device);
            }
       }
    }

}

Reader::Reader()
{
    // Settings settings;
    find_urt_device("/dev"); //take from settings

    //cycle_read_device();

}

void Reader::cycle_read_device()
{
    //debug
    while(1)
    {
        cout << "TEST PRINT!!!" <<endl;
    }
}
