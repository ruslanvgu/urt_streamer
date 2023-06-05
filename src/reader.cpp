#include "reader.h"

Reader::Reader()
{

    /*
     * 1. find fpga device
     * 2. init fpga device
     * 3. read fpga device
     *
     *
    */


    if(!init())
        throw "Inititalization failed!";
}

bool Reader::init()
{
    string pathDev =  "/dev/";

}

void Reader::read()
{
    //debug
    while(1)
    {
        cout << "TEST PRINT!!!" <<endl;
    }
}
