#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
using namespace std;


int main(void)
{
    vector<int> numbers{1,2,3,4,5,6} ;

    //ostream_iterator内部要重载相应的运算符，模拟
    //出一个迭代器功能来==>适配器模式
    ostream_iterator<int> osi(cout," ");
    copy(numbers.begin(),numbers.end(),osi);
    cout<<endl;
    
    copy(numbers.begin(),numbers.end(),ostream_iterator<int>(cout," "));
    cout<<endl;

    return 0;
}

