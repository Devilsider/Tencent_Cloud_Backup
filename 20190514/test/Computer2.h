#ifndef __WD_COMPUTER2_H__
#define __WD_COMPUTER2_H__

class Computer{
public:
    void setBrand(const char *brand);
    void setPrice(float price);
    void print();
private:
    char _brand[20];
    float _price;
};
#endif
