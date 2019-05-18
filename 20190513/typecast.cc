#include <iostream>
using std::cout;
using std::endl;

void test1(){
    double number1=1.11;
    int number2=static_cast<int>(number1);
    cout<<"number1 ="<<number1<<endl;
    cout<<"number2 ="<<number2<<endl;

    int *pint=static_cast<int *>(malloc(sizeof(int)));
    *pint =10;
    free(pint);
}
int main(){
    test1();
    return 0;
}
