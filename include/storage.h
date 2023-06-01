#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <queue>
#include <mutex>

using namespace std;

class Storage
{

    queue<string> data_;
    size_t sizeConteins_;
    //mutex mtx_;
public:
    Storage();

    void writeBack(const unsigned char * p, size_t size);
    string takeFront();
    size_t getSizeConteins();
    size_t size();
};

#endif // STORAGE_H
