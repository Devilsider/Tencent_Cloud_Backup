#include "cowString_proxy.h"

CowString::CowString()
:_pstr(new char[5]()+4)
{
    cout<<"CowString()"<<endl;
}
CowString::CowString(const char * str)
:_pstr(new char[5+strlen(str)]()+4)
{
    cout<<"CowString(const char *)"<<endl;
    initRefCount();
    strcpy(_pstr,str);
}
CowString::CowString(const CowString &rhs)
:_pstr(rhs._pstr)
{
    increaseRefCount();
    cout<<"CowString(const CowString &)"<<endl;
}
CowString & CowString::operator=(const CowString &rhs){
    cout<<"CowString & CowString::operator=(const CowString &rhs)"<<endl;
    if(this!=&rhs){
        release();
        _pstr=rhs._pstr;
        increaseRefCount();
    }
    return  *this;
}
CowString::~CowString(){
    release();
}
CowString::CharProxy& CowString::CharProxy::operator=(const char &ch)
{
    cout<<"CharProxy::operator=(const char &)"<<endl;
    if(_idx>=0&&_idx<_cowString.size()){
        if(_cowString.refcount()>1){
            _cowString.decreaseRefCount();
            char* ptemp=new char[5+strlen(_cowString._pstr)]()+4;
            strcpy(ptemp,_cowString._pstr);
            ptemp[_idx]=ch;
            _cowString._pstr=ptemp;
            _cowString.initRefCount();
        }
    }
    else {
        cout<<"pointer crossing !"<<endl;
    }
    return *this;
}
std::ostream &operator<<(std::ostream &os,const CowString::CharProxy &rhs){
    os<<(rhs._cowString.c_str())[rhs._idx];
    return os;
}
std::ostream &operator<<(std::ostream &os,const CowString &rhs){
    os<<rhs.c_str();
    return os;
}

int main()
{
     CowString s0;
     cout << "s0 = " << s0 << endl;

     CowString s1("hello,world");
     CowString s2(s1);

     CowString s3("shenzhen");
     s3[0] = 'S';//refcount = 1

     s3 = s2;
     cout << "s1 = " << s1 << endl;
     cout << "s2 = " << s2 << endl;
     cout << "s3 = " << s3 << endl;
     printf("s1's address: %p\n", s1.c_str());
     printf("s2's address: %p\n", s2.c_str());
     printf("s3's address: %p\n", s3.c_str());
     cout << "s1's refcount() = " << s1.refcount() << endl;
     cout << "s2's refcount() = " << s2.refcount() << endl;
     cout << "s3's refcount() = " << s3.refcount() << endl;

     cout << endl << ">>> 执行s1[0] = 'x' 之后:" << endl;
     s1[0] = 'x';
     cout << "s1 = " << s1 << endl;
     cout << "s2 = " << s2 << endl;
     cout << "s3 = " << s3 << endl;
     printf("s1's address: %p\n", s1.c_str());
     printf("s2's address: %p\n", s2.c_str());
     printf("s3's address: %p\n", s3.c_str());
     cout << "s1's refcount() = " << s1.refcount() << endl;
     cout << "s2's refcount() = " << s2.refcount() << endl;
     cout << "s3's refcount() = " << s3.refcount() << endl;

     cout << endl << ">>> 执行 cout << s2[0] << endl 之后:" << endl;
     cout << "s2[0] = " << s2[0] << endl;// 在这里不应该进行深拷贝
     cout << "s1 = " << s1 << endl;
     cout << "s2 = " << s2 << endl;
     cout << "s3 = " << s3 << endl;
     printf("s1's address: %p\n", s1.c_str());
     printf("s2's address: %p\n", s2.c_str());
     printf("s3's address: %p\n", s3.c_str());
     cout << "s1's refcount() = " << s1.refcount() << endl;
     cout << "s2's refcount() = " << s2.refcount() << endl;
     cout << "s3's refcount() = " << s3.refcount() << endl;
 
    return 0;
}

