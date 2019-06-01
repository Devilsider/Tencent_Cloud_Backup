#include <functional>
#include <iostream>
using namespace std;

void display(){
    cout<<"display()"<<endl;
}

void (*f)()=display;

typedef void(*Function)();

int test0(){
    f();
    Function f1=display;
    f1();
    return 0;
}

void add(int x,int y){
    cout<<" x + y = "<<x + y<<endl;
}

struct exemple{
    void add(int x,int y){
        cout<<"exemple::add()"<<endl;
        cout<<"x + y = "<<x+y<<endl;
    }

    int _x=10;
};

void test1(){
    auto f=display;
    f();
    auto f1=bind(&add,1,2);
    f1();
    exemple em;

    auto f2 = bind(&exemple::add,&em,3,4);
    f2();

    auto f3 = bind(&exemple::add,em,5,6);
    f3();
    
    using namespace placeholders;
    auto f4= bind(&exemple::add,&em,_1,_2);
    f4(11,12);

    auto f5= bind(&exemple::_x,&em);
    cout<< f5()<<endl;
}

void print(int x1,int x2,int &x3,int x4){
    cout<<"("<<x1
        <<","<<x2
        <<","<<x3
        <<","<<x4
        <<")"<<endl;
}

void test2(){
    using namespace std::placeholders;
    int a=100;
    
    //占位符本身所占的位置就是形参的位置
    //占位符本身的数字代表的是实参的位置
    auto f = bind(print ,_1,_2,ref(a),a);
    a = 101;
    f(11,22,1111,2222,3333);

}

void test3(){
    using namespace std::placeholders;
    int a = 100;
    
    //std::function称为函数的容器，只能保存一个函数
    function<void(int,int)> f = bind(print,_1,_2,ref(a),a);
    a=101;
    f(11,22);

    function<void(int)> f1 = bind(print,_1,100,ref(a),a);
    f1(111);
    
    function<void()> f2 = display;
    f2();

    f2=bind(&exemple::add,exemple(),1,2);
    f2();
}
int main()
{
    /* test0() ; */
    /* test1() ; */
    /* test2() ; */
    test3() ;
    return 0;
}

