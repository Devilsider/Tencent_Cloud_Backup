#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

void display(int &number){
    ++number;
    cout<<number<<" ";
}
int main(void)
{
    vector<int> numbers{1,2,3,4,5} ;
    for_each(numbers.begin(),numbers.end(),display);
    cout<<endl;
    
    cout<<"&numbers[0] = " <<&numbers[0]<<endl;
    //lambda表达式 =>匿名函数
    for_each(numbers.begin(),numbers.end(),[](int number){
             cout<< number<<" ";
             });
    cout<<endl;

    //[] 表示捕获上下文中的对象,
    //=  以值传递的方式进行捕获
    //&  以引用的方式进行捕获
    auto f1= [=](){
        cout<<"lambda expression "<<endl;
        cout<<"numbers[0] = "<<numbers[0]<<endl;
        cout<<"&numbers[0] = "<<&numbers[0]<<endl;
    };

    f1();
    return 0;
}

