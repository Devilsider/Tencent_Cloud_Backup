#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Computer{
public:
    Computer(const char *brand,float price);

    Computer(const Computer &rhs)
    :_brand(new char[strlen(rhs._brand)+1]()),
    _price(rhs._price)
    {
        cout<<"Computer(const Computer&)"<<endl;
        strcpy(_brand,rhs._brand);
    }
    
    void print();

    ~Computer(){
        delete  []_brand;
        cout<<"~Computer()"<<endl;
    }
private:
    char *_brand;
    float _price;
};

Computer::Computer(const char *brand,float price)
:_brand(new char[strlen(brand)+1]() ),
    _price(price)
{
    cout<<"Computer(const char*,float)"<<endl;
    strcpy(_brand,brand);
}
int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

