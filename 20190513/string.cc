#include <stdio.h>

#include <iostream>
#include <string>
//using namespace std;
using std::cout;
using std::endl;
using std::string;
void test0(){
    char str[]="hello,world";
    printf("str =%s\n",str);
    const char *pstr="hello,world";
    printf("pstr =%s\n",pstr);
}

using std::cout;
using std::endl;
using std::string;
void test1(){
    int number(1);
    cout<<"number = "<<number<<endl;
    string s1="hello";
    string s2("world");
    cout<<"s1=%s\n"<<s1<<endl;
    cout<<"s2=%s\n"<<s2<<endl;
    const char *pstr=s1.c_str();
    const char *pstr2=s1.data();
    printf("pstr=%s\n",pstr);
    printf("pstr2=%s\n",pstr2);

    cout<<"s1.size="<<s1.size()<<endl;
    cout<<"s2.size="<<s2.size()<<endl;

    for(auto i:s1){
        cout<<"i="<<i<<endl;
    }
    string s3=s1+s2;
    cout<<"s3="<<s3<<endl;
    s3.append(",shenzhen");
    cout<<"s3="<<s3<<endl;
    s3.append(3,'z');
    cout<<"s3="<<s3<<endl;
    s3.append(s1);
    cout<<"s3="<<s3<<endl;

    string s4;
    size_t pos=s3.find_first_of('z',0);
    s4=s3.substr(pos,3);
    cout<<"s4="<<s4<<endl;

    string s5("-insert-");
    s3.insert(pos,s5);
    cout<<"s3="<<s3<<endl;
    
}

using std::cout;
using std::endl;
using std::string;
int main()
{
    test1();
    return 0;
}

