#include <iostream>
using std::cout;
using std::endl;

class A{
public:
    virtual void a(){
        cout<<"A::a()"<<endl;
    }
    virtual void b(){
        cout<<"A::b()"<<endl;
    }
    virtual void c(){
        cout<<"A::c()"<<endl;
    }
};

class B{
public:
    virtual void a(){
        cout<<"B::a()"<<endl;
    }
    virtual void b(){
        cout<<"B::b()"<<endl;
    }
    void c(){
        cout<<"B::c()"<<endl;
    }
    void d(){
        cout<<"B::d()"<<endl;
    }
};

class C:public A,public B
{
public:
    virtual void a(){
        cout<<"C::a()"<<endl;
    }
    void b(){
        cout<<"C::b()"<<endl;
    }
    void c(){
        cout<<"C::c()"<<endl;
    }
};

class D:public C{
public:
    void c(){
        cout<<"D::c()"<<endl;
    }
};

int main()
{
    C c;
    c.a();
    c.c();
    c.d();
    cout<<endl;

    A * pa=&c;
    cout<<"pa = "<<pa<<endl;
    pa->a();
    pa->b();
    pa->c();

    cout<<endl;
    B *pb=&c;
    cout<<"pb = "<<pb<<endl;
    pb->a();
    pb->b();
    pb->c();
    pb->d();
    cout<<endl;

    C *pc=&c;
    cout<<"pc = "<<pc<<endl;
    pc->a();
    pc->c();
    pc->d();
    cout<<endl;
    
    D d;
    pc=&d;
    pc->c();

    return 0;
}

