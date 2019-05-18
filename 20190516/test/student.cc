#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
using std::cout;
using std::endl;

class Student{
    public:
        int ild;
        char szName[10];
    public:
        Student(){
            cout<<"Student 构造函数被调用"<<endl;
        }
        ~Student(){
            cout<<"Student 析构函数被调用"<<endl;
        }
    private:
        static void * operator new(std::size_t nSize)
        {
            cout<<"new 操作符被调用,nSize="<<nSize<<endl;
            void *pRet=malloc(nSize);
            return pRet;
        }
        static void operator delete (void *pVoid)
        {
            cout<<"delete 操作符被调用."<<endl;
            free(pVoid);
        }
        
};
int main()
{
    Student *pstu=new Student;
    pstu->ild=101;
    strcpy(pstu->szName,"Tony");
    cout<<endl;
    delete  pstu;
    return 0;

    return 0;
}

