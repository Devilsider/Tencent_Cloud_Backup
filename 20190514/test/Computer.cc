#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Computer
{
    public:
        void setBrand(const char * brand){
            strcpy(_brand,brand);
        }
        void setPrice(float price ){
            _price =price;
        }
        void print(){
            cout <<"brand: "<<_brand<<endl
                 <<"price: "<<_price<<endl;
        }
    private:
        char _brand[20];
        float _price;
};

int main(void){
    Computer pc;
    pc.setBrand("Lenovo");
    pc.setPrice(5555);
    pc.print();
    return 0;

}
