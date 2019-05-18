#include <iostream>
using std::cout;
using std::endl;
//数组栈不是链栈
class Stack{
    public:
        Stack(){
            cout<<"Stack()"<<endl;
            _StackSize=100;
            _esp=0;
            _Stack=new int[_StackSize];
        }
        Stack(int size){
            cout<<"Stack(int size)"<<endl;
            _StackSize=size;
            _esp=0;
            _Stack=new int[_StackSize];
        }
        bool empty(){
            if(0==_esp){
                return true;
            }
            return false;
        }
        bool full(){
            if(_StackSize==_esp){
                return true;
            }
            return false;
        }
        void push(int elem){
            if(!full()){
               //栈不满
               _Stack[_esp]=elem;
               ++_esp;
            }
            else{
                cout<<"stack is full!"<<endl;
            }
        }
        int top(){
            return _Stack[_esp-1];
        }
        void pop(){
            if(!empty()){
                --_esp;
                _Stack[_esp]=0;
            }
            else {
                cout<<"stack is empty!"<<endl;
            }
        }
        int getStackSize(){
            return _StackSize;
        }
        void setStackSize(const int size){
           _StackSize=size; 
        }
        void print(){
            for(int idx=0;idx<_esp;++idx){
                cout<<"_Stack[idx]="<<_Stack[idx]<<endl;
            }
        }
        ~Stack(){
            cout<<"~Stack()"<<endl;
            delete []_Stack;
        }
    private:
        int _StackSize;
        int* _Stack;//栈数组头指针
        int _esp;//栈顶指针
};


int main()
{
    Stack s1;
    Stack s2(10);
    s1.pop();
    s2.pop();
    for(int idx=0;idx<12;++idx){
        s2.push(idx);
    }
    s2.print();
    int elem;
    elem=s2.top();
    cout<<"elem="<<elem<<endl;
    s2.pop();
    s2.print();
    return 0;
}

