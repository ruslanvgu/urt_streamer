#include "storage.h"

Storage::Storage()
    :sizeConteins_(0)
    ,data_{}
{

}

void Storage::writeBack(const unsigned char *p, size_t size)
{
    string s(reinterpret_cast<const char*>(p),size);
    data_.push(s);
    sizeConteins_+=s.size();
}

string Storage::takeFront()
{
    if(data_.empty())
    {
        return {};
    }
    string first = data_.front();
    data_.pop();

    return first;
}

size_t Storage::getSizeConteins()
{
    return sizeConteins_;
}

size_t Storage::size()
{
    return data_.size();
}
