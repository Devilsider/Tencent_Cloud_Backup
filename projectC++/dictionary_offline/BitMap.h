#pragma once
#include <vector>
using std::vector;

class BitMap
{
    enum{
        SHIFT=5,
        MASK=0x1F,
        BIT_PER_INT=32
    };
public:
    BitMap(unsigned int range)
    :_data(1+range/BIT_PER_INT)
    {}
    void set(unsigned int number)
    {
        _data[number>>SHIFT]|=(1<<(number&MASK));
    }
    void reset(unsigned int number)
    {
        _data[number>>SHIFT]&=(~(1<<(number&MASK)));
    }
    bool test(unsigned int number)
    {
        return _data[number>>SHIFT]&(1<<(number&MASK));
    }
private:
    vector<unsigned int > _data;
};

