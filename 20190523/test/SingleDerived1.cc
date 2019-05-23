#include <iostream>
using std::cout;
using std::endl;

class Base{
public:
    Base(){
        cout<<"Base()"<<endl;
    }
};

class Derived
:public Base
{
public:
    Derived(double derived)
    :Base(),
    _derived(derived)
    {
        cout<<"Derived()"<<endl;
    }
    void display(){
        cout<<"Derived : _derived = "<<_derived<<endl;
    }
private:
    double _derived;
};

int main()
{
    Derived d(11.1);
    d.display();
    return 0;
}

