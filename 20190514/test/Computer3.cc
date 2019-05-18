#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Computer{
public:
    Computer(const char *brand,float price);
    void print();
    void release(){
        delete []_brand;
    }
    ~Computer(){
        release();
        cout<<"~Computer()"<<endl;
    }
private:
    char * _brand;
    float _price;//注意字节对齐

};
Computer::Computer(const char *brand,float price)
:_brand(new char[strlen(brand)+1]())
    ,_price(price)
{
    cout <<"Computer(const char *,float )"<<endl;
    strcpy(_brand,brand);
}
void Computer::print(){
    cout<<"brand: "<<_brand<<endl
        <<"price: "<<_price<<endl;

}
Computer pc3("Dell",7777);
int test0(){
    Computer pc1("Lenovo",5555);
    pc1.print();
    //pc1.release();
    cout<<"sizeof(Computer)="<<sizeof(Computer)<<endl
        <<"sizeof(pc1)="<<sizeof(pc1)<<endl<<endl;
    
    Computer *pc2=new Computer("Thinkpad",8888);
    pc2->print();

    delete pc2;
    cout<<endl;

    pc3.print();

    cout<<endl;
    static Computer pc4("xiaomi",7500);
    pc4.print();

    return 0;

}
int main()
{
    test0();
    cout<<"......"<<endl;
    return 0;
}

