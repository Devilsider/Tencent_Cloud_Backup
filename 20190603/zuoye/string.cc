#include <string.h>
#include <vector>
#include <iostream>
using namespace std;

class String {
public:
    String(const char *pstr)
    :_pstr(new char[strlen(pstr)+1]())
    {
        cout<<"String(const char *)"<<endl;
        strcpy(_pstr,pstr);
    }

    //复制构造函数
    String(const String &rhs)
    :_pstr(new char[strlen(rhs._pstr)+1]())
    {
        strcpy(_pstr,rhs._pstr);
        cout<<"String(const String &)"<<endl;
    }
    
    //赋值运算符函数
    String &operator=(const String &rhs)
    {
        cout<<"String & operator = (const String &rhs)"<<endl;
        if(this != &rhs){
            delete  []_pstr;
            _pstr=new char[strlen(rhs._pstr)+1]();
            strcpy(_pstr,rhs._pstr);
        }
        return *this;
    }

    //移动构造函数和移动赋值运算符函数统称为具有移动语义的函数
    //复制构造函数和赋值运算符函数统称为具有复制控制语义的函数
    //具有移动语义的函数要优先于具有复制控制语义的函数
    
    //移动构造函数
    String(String && rhs)
    :_pstr(rhs._pstr)//浅拷贝
    {
        cout<<"String(String &&)"<<endl;
        rhs._pstr = NULL;
    }
    String &operator=(String && rhs){
        cout<<"String &operator=(String && rhs)"<<endl;
        if(this != &rhs){
            delete []_pstr;
            _pstr=rhs._pstr;
            rhs._pstr=NULL;
        }
        return *this;
    }

    ~String(){
        if(_pstr){
            delete []_pstr;
        }
        cout<<"~String()"<<endl;
    }
    friend std::ostream & operator<<(std::ostream &os,const String &rhs);

private:
    char *_pstr;
};
std::ostream & operator<<(std::ostream &os,const String &rhs){
    os<<rhs._pstr;
    return os;
}
int main()
{
    vector<String> strs;
    strs.push_back("hello,world");
    cout<<"......"<<endl;

    String str1="wangdao";
    cout<<"str1 = "<<str1<<endl;
    cout<<endl;
    //strs.push_heap(str1);//只要是放在容器中的元素，都是一个全新的副本(copy)
    
    strs.push_back(std::move(str1));
    
    String str2("shenzhen");
    str2 = "henggang";
    cout<<" str2= "<<str2<<endl;

    cout<< endl<<"test std::move"<<endl;
    //std::move显示的将一个左值转换为一个右值,本质上是一个强制转换
    
    str2 = std::move(str1);//该语句之后，就不再使用str1对象了
    cout<<"str2 = "<<str2<<endl;
    //cout<<"str1 = "<<str1<<endl;
    //
    str2 = std::move(str2);


    cout<<"......"<<endl;
    return 0;
}

