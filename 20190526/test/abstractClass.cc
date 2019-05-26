#include <iostream>
using std::cout;
using std::endl;

class Base{
public:
    void  print()const
    {
        cout<<"_base = "<<_base<<endl;
    }
protected:
    Base(double base)
    :_base(base)
    {
        cout<<"Base(double)"<<endl;
    }
private:
    double _base;
};

class Derived:public Base
{
public:
    Derived(double base)
    :Base(base)
    {
        cout<<"Derived(double base)"<<endl;
    }

};
int main()
{
    Base * pbase;
    Derived derived(11.11);
    derived.print();
    return 0;
}

