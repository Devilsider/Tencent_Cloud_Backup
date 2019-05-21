#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
using std::cout;
using std::endl;

class CowString{
public:
    CowString();
    CowString(const char *);
    CowString(const CowString &rhs);
    CowString &operator=(const CowString &rhs);
    ~CowString();

    const char *c_str(){
        return _pstr;
    }
    int size()const{
        return strlen(_pstr);
    }
    int refcount(){
        return *((int *)(_pstr-4));
    }

    char &operator[](int idx);
    friend std::ostream &operator<<(std::ostream &os,const CowString &rhs);
private:
    void initRefcount(){
        *((int *)(_pstr-4))=1;
    }
    void increaseRefcount(){
        ++*((int *)(_pstr-4));
    }
    void decreaseRefcount(){
        --*((int *)(_pstr-4));
    }
    void release(){
        decreaseRefcount();
        if(0==refcount()){
            delete [](_pstr-4);
            cout<<">>delete _pstr"<<endl;
        }
    }
private:
    char *_pstr;
};

CowString::CowString()
:_pstr(new char[5]()+4)
{
    cout<<"CowString()"<<endl;
    initRefcount();
}
CowString::CowString(const char * str)
:_pstr(new char[5+strlen(str)]()+4)
{
    initRefcount();
    cout<<"CowString(const char *)"<<endl;
    strcpy(_pstr,str);
}
CowString::CowString(const CowString &rhs)
:_pstr(new char[5+strlen(rhs._pstr)]()+4)
{
    initRefcount();
    cout<<"CowString(const CowString &)"<<endl;
    strcpy(_pstr,rhs._pstr);
}
CowString & CowString::operator=(const CowString &rhs){
    if(this!=&rhs){
        release();
        _pstr=rhs._pstr;
        increaseRefcount();
    }
    return *this;
}
CowString::~CowString(){
    release();
}
std::ostream &operator<<(std::ostream &os,const CowString &rhs){
    os<<rhs._pstr;
    return os;
}
char & CowString::operator[](int idx){
    cout<<"CowString::operator[]"<<endl;
    if(idx>=0&&idx<size()){
        if(refcount()>1){
            decreaseRefcount();
            char *ptemp=new char[5+strlen(_pstr)]()+4;
            strcpy(ptemp,_pstr);
            _pstr=ptemp;
            initRefcount();
        }
        return _pstr[idx];
    }
    else {
        static char nullchar='\0';
        cout<<"pointer crossing"<<endl;
        return nullchar;
    }
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

