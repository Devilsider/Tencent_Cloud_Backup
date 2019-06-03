#include <stdio.h>
#include <memory>
#include <iostream>
using namespace std;

struct FileCloser{
    void operator()(FILE *fp){
        if(fp){
            fclose(fp);
            cout<<"fclose()"<<endl;
        }
    }
};

void test0(){
    unique_ptr<FILE,FileCloser> up(fopen("test.txt","a+"));
    string msg("hello,world\n");
    fwrite(msg.c_str(),1,msg.size(),up.get());
}

void test1(){
    shared_ptr<FILE> sp(fopen("test.txt","a+"),FileCloser());
    string msg("hello,world\n");
    fwrite(msg.c_str(),1,msg.size(),sp.get());
}

int main()
{
    test0() ;
    test1() ;
    return 0;
}

