#pragma vtordisp(off)
#include <iostream>
using std::cout;
using std::endl;

class B{
public:
    B()
    :_ib(10) ,
    _cb('B')
    {}
    virtual void f(){
        cout<<"B::f()"<<endl;
    }
    virtual void Bf(){
        cout<<"B::f()"<<endl;
    }
private:
        int _ib;
        int _cb;
};
class B1:virtual public B
{
public:
    B1()
    :_ib1(100) ,
    _cb1('1')
    {}
    virtual void f(){
        cout <<"B1::f()"<<endl;
    }
#if 1
    virtual void f1(){
        cout<<"B1::f()"<<endl;
    }
    virtual void B1f(){
        cout<<"B1::f()"<<endl;
    }
#endif
private:
        int _ib1;
        int _cb1;
};

class B2:virtual public B
{
public:
    B2()
    :_ib2(1000),_cb2('2')
    {}
    virtual void f(){
        cout<<"B2::f()"<<endl;
    }
#if 1
    virtual void f2(){
        cout<<"B2::f2()"<<endl;
    }
    virtual void Bf2(){
        cout<<"B2::Bf2()"<<endl;
    }
#endif
private:
        int _ib2;
        char _cb2;
};

class D:public B1,public B2
{
public:
    D()
    :_id(10000),_cd('3')
    {}
    virtual void f(){
        cout<<"D::f()"<<endl;
    }
#if 1
    virtual void f1(){
        cout<<"D::f1()"<<endl;
    }
    virtual void f2(){
        cout<<"D::f2()"<<endl;
    }
    virtual void Df(){
        cout<<"D::Df()"<<endl;
    }
#endif
private:
    int _id;
    char _cd;
};

int main()
{
    D d;
    cout<<sizeof(d) <<endl;
    return 0;
}

