#include "string.h"
using namespace wd;

int main()
{
    String s1("hello");
    String s2("worlddddd");
    cout<<s1<<endl;
    cout<<s2<<endl;
    String s3;
    s3=s1;
    cout<<s3<<endl;

    std::cin>>s3;
    
    cout<<s3<<endl;
    
    s3=s1+s2;

    cout<<s3<<endl;


    String s4(s3);
    cout<<"s4= "<<s4<<endl;
   
    s4=s1;

    cout<<"s4= "<<s4<<endl;
    s4="nihao";
    cout<<"s4= "<<s4<<endl;

    s1+=s2;
    cout<<"s1= "<<s1<<endl;

    s4+="wobuhao";
    cout<<"s4= "<<s4<<endl;
   
    cout<<"s4[1]= "<<s4[1]<<endl;
    cout<<"s4[100]"<<s4[100]<<endl;
   
    cout<<"s4.size()= "<<s4.size()<<endl;
    cout<<"s4.cstr()= "<<s4.c_str()<<endl;
    
    s3=s4;
    cout<<"s3= " <<s3<<endl;
    cout<<"s4= " <<s4<<endl;
    cout<<" s4==s3?: "<<(s4==s3)<<endl;
    cout<<"s4!=s3?: " <<(s4!=s3)<<endl;
    cout<<"s4>s3?: "<<(s4>s3)<<endl;
    cout<<"s4<s3?: "<<(s4<s3)<<endl;
    cout<<"s4<=s3?: "<<(s4<=s3)<<endl;
    cout<<"s4>=s3?: "<<(s4>=s3)<<endl;
    return 0;
}

