#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Computer{
public:
    Computer(const char *brand,float price);
#if 0 
    Computer(const Computer &rhs)
    :_brand(rhs._brand),
    _price(rhs.price)
    {
        cout<<"Computer(const Computer &)"<<endl;
    }
#endif
    Computer (const Computer &rhs)
    :_brand(new char[strlen(rhs._brand)+1]()),
    _price(rhs._price)
    {
        cout<<"Computer(const Computer &)"<<endl;
        strcpy(_brand,rhs._brand);
    }
#if 0
    Computer & operator=(const Computer &rhs){
        _brand = rhs._brand;
        _price = rhs._price;
        return *this;
    }
#endif 
    Computer & operator=(const Computer &rhs){
        cout<<"Computer & operator =(const Computer &)"<<endl;
        if(this!=&rhs){
            delete[] this->_brand;
            _brand=new char[strlen(rhs._brand)+1]();
            strcpy(_brand,rhs._brand);
            _price=rhs._price;
        }
        return *this;
    }


    void print();
    ~Computer(){
        delete []_brand;
        cout<<"~Computer()"<<endl;
    }
    
private:
    char * _brand;
    float _price;
};

Computer::Computer(const char *brand,float price )
    :_brand(new char[strlen(brand)+1]()),
    _price(price)
{
    cout<<"Computer(const char *,float)"<<endl;
    strcpy(_brand,brand);
}
void Computer::print(){
    printf(">> _brand : %p\n",_brand);
    cout<<">> brand: "<<_brand<<endl
        <<">> price :"<<_price<<endl;

}
int test0(){
    Computer pc1("xiaomi",7500);
    cout <<"pc1:->>"<<endl;
    pc1.print();
    Computer pc2=pc1;
    cout <<"pc2:->>"<<endl;
    pc2.print();
    return 0;
}

void test1(){
    Computer pc1("xiaomi",7777);
    cout<<"pc1-> "<<endl;
    pc1.print();

    Computer pc2("Thinkpad",8888);
    cout<<"pc2-> "<<endl;
    pc2.print();

    pc2=pc1;
    cout<<endl<<"执行pc2 = pc1之后:"<<endl;
    cout<<"pc2:-->"<<endl;
    pc2.print();

    pc2=pc2;
    
}
int main(void)
{
   // test0(); 
   test1();
    return 0;
}

