#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;
int main()
{
    int number=1;
    int &ref=number;
    cout<<"ref="<<ref<<endl
        <<"number="<<number<<endl;
    ref=2;
    cout<<"ref="<<ref<<endl
        <<"number="<<number<<endl;
    number=3;
    cout<<"ref="<<ref<<endl
        <<"number="<<number<<endl;
    int number2=10;
    ref=number2;
    cout<<"ref="<<ref<<endl
        <<"number"<<number<<endl;
    cout<<"&ref="<<&ref<<endl
        <<"&number="<<&number<<endl
        <<"&number2="<<&number2<<endl;
    return 0;
}

