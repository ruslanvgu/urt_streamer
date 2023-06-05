#ifndef READER_H
#define READER_H
#include <iostream>
#include <thread>
#include <list>
//#include <exception>
#include "storage.h"

using namespace std;

class Fpga{

};



class Reader
{
    list<Fpga> devices;

public:
    Reader();

    bool init();
    void read();
    void close();
};

#endif // READER_H
