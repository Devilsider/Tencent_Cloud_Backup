#include "singleton_template.h"
#include <stdlib.h>
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
class Point{
public:
    Point()
    :_x(0),_y(0)
    {}

    Point(int x,int y)
    :_x(x),_y(y) 
    {}
    
    void print(){
        cout<<" _x "<<_x<<" _y "<<_y<<endl;
    }
private:
    int _x;
    int _y;
};

class Computer{
public:
    Computer()
    :_brand(""),
    _price(0)
    {}
    Computer(string str,int price)
    :_brand(str),
    _price(price)
    {}
    void print(){
        cout<<" Computer _brand is "<<_brand<<" _price is "<<_price<<endl;
    }

private:
    string _brand;
    double _price;
};
int main()
{
    
    int * s1 =Singleton<int>::getInstance(10);
    cout<<" s1 = "<<s1<<" *s1 = "<<*s1<<endl;
     
    int * s2 =Singleton<int>::getInstance(20);
    cout<<" s2 = "<<s2<<" *s2 = "<<*s2<<endl;

    Point * p1=Singleton<Point>::getInstance(1,2);
    cout<<" p1 " <<p1<<endl;
    p1->print();
    Point * p2=Singleton<Point>::getInstance(3,4);
    cout<<" p2 " <<p2<<endl;
    p2->print();

    Computer *c1=Singleton<Computer>::getInstance("xiaomi",6666);
    cout<<" c1 "<<c1<<endl;
    c1->print();
    Computer *c2=Singleton<Computer>::getInstance("xiaomi",6666);
    cout<<" c2 "<<c2<<endl;
    c2->print();
    
    Computer *c3=Singleton<Computer>::getInstance("huawei",8888);
    cout<<" c3 "<<c3<<endl;
    c3->print();
    return 0;
}

