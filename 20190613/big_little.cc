#include <stdio.h>
#include <iostream>
using namespace std;

bool isLittleEnd(){
    union example{
        int number;
        char ch;
    };
    example e;
    e.number=1;
    e.ch='a';
    return e.ch;
}
void test0(){
    int number=0x1234;
    char  *p=(char *)&number;
    printf("%x\n",*p);
}
int main()
{
    test0() ;
    return 0;
}

