#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
using namespace std;


int main(void)
{
    vector<int> numbers ;
    istream_iterator<int> isi(cin);
    //beign()、end()是用来读取容器元素的
    //不能用来做添加元素的操作
    //若要添加元素，须使用inserter插入迭代器等
    //例如使用back_inserter,返回的是一个插入迭代器std::back_insert_iterator
    //在赋值时调用相应的容器vector的push_back方法
    copy(isi,istream_iterator<int>(),back_inserter(numbers));

    copy(numbers.begin(),numbers.end(),ostream_iterator<int>(cout,","));
    cout<<endl; 


    return 0;
}

