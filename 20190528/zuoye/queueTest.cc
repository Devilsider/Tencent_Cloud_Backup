#include "queue.h"
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::to_string;

void test0(){
    Queue<int,10> q1;
    q1.deQueue();
    for(int idx=0;idx<12;++idx){
        q1.enQueue(idx);
    }
    q1.print(); 

    cout<<" head = "<<q1.getHead()<<endl;
    q1.deQueue();
    q1.print();
    q1.enQueue(18);
    q1.print();
    q1.enQueue(19);
    q1.print();

    cout<<" head = "<<q1.getHead()<<endl;
    q1.print();

}

void test1(){
    Queue<char,10> q2;
    char ch='a';
    for(int idx=0;idx<13;++idx){
        q2.enQueue(ch+idx);
    }
    q2.print();

    cout<<" head = "<<q2.getHead()<<endl;
    cout<<" tail = "<<q2.getTail()<<endl;

    q2.deQueue();
    q2.print();

    q2.enQueue('z');
    q2.print();
    q2.enQueue('<');

}

void test2(){
    Queue<string,10> q3;
    string s("hello");
    for(int idx=0;idx<15;++idx){
        s.append(to_string(idx));
        q3.enQueue(s);
    }
    q3.print();
    cout<<"head= "<<q3.getHead()<<endl;
    cout<<"tail= "<<q3.getTail()<<endl;
}
int main()
{
    test0();
    test1();
    test2();
    return 0;
}

