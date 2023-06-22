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

void Reader::maincycle()
{
    //debug
    while(1)
    {
        cout << "TEST PRINT!!!" <<endl;
    }
}
