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
private:
    long _a=100;
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

class C:public A,public B{
public:
    virtual void a(){
        cout<<"C::a()"<<endl;
    }
    virtual void b(){
        cout<<"C::b()"<<endl;
    }
    virtual void c(){
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
    A a;
    long ** pvtable=(long **)&a;
    
    long address = pvtable[0][0];
    typedef  void (*Function)();
    Function f= (Function )address; f();

    f=(Function)pvtable[0][1];
    f();

    f=(Function)pvtable[0][2];
    f();
   
    pvtable[1]=(long *)1000;
    long value=(long)pvtable[1];
    cout<<"value= "<<value<<endl;

    C c;
    pvtable=(long**)&c;
    cout<<" sizeof(c)= "<<sizeof(c)<<endl; 
    f=(Function)pvtable[0][0];    
    f();

    f=(Function)pvtable[0][1];    
    f();
    
    f=(Function)pvtable[0][2];    
    f();
    
    f=(Function)pvtable[2][0];    
    f();
    
    f=(Function)pvtable[2][1];    
    f();
    
    f=(Function)pvtable[3][0];    
    f();
    
    f=(Function)pvtable[3][1];    
    f();
    
    f=(Function)pvtable[3][2];    
    f();
    return 0;
}

