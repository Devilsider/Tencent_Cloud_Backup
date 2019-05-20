#ifndef __STRING_H__
#define __STRING_H__
#include <limits>
#include <stdio.h>
#include<string.h>
#include<string>
#include<iostream>
using std::cout;
using std::endl;
using std::string;
namespace wd{
class String
{
public:
	String()
    :_pstr(new char[1]())
    {
    }
    String(const char *str)
    :_pstr(new char[strlen(str)+1]())
    {
        strcpy(_pstr,str);
    }
    String(const String& str)
    :_pstr(new char[strlen(str._pstr)+1]())
    {
            strcpy(_pstr,str._pstr);
    }
    ~String(){
        if(_pstr){
            delete []_pstr;
        }
    }
    String &operator=(const String &str){
        if(this!=&str){
            delete []_pstr;
            _pstr=new char[strlen(str._pstr)+1]();
            strcpy(_pstr,str._pstr);
        }  
        return *this;
    }
    String &operator=(const char * str){
        if(0!=strcmp(this->_pstr,str)){
            delete[]_pstr;
            _pstr=new char[strlen(str)+1]();
            strcpy(_pstr,str);
        }
        return *this;
    }

    String &operator+=(const String &str){
        if(NULL!=_pstr){
            char *temp(new char[strlen(_pstr)+1]());
            strcpy(temp,_pstr);
            delete []_pstr;
            _pstr=new char[strlen(temp)+strlen(str._pstr)+1]();
            sprintf(_pstr,"%s%s",temp,str._pstr);
            /* strcpy(_pstr,temp); */
            delete []temp;
        }
        return *this;
    }
    String &operator+=(const char *str){
        if(NULL!=_pstr){
            char *temp(new char[strlen(_pstr)+1]());
            strcpy(temp,_pstr);
            delete []_pstr;
            _pstr=new char[strlen(temp)+strlen(str)+1]();
            sprintf(_pstr,"%s%s",temp,str);
            delete []temp;
        }
        return *this;
    }

    char &operator[](std::size_t index){
        if(index<strlen(_pstr)){
            return _pstr[index];
        }
        else{
            static char nptr='\0';
            cout<<"pointer crossing !error"<<endl;
            return nptr;
        }
    }
    const char &operator[](std::size_t index) const{
        if(index<strlen(_pstr)){
            return _pstr[index];
        }
        else{
            static char nptr='\0';
            cout<<"pointer crossing !error"<<endl;
            return nptr;
        }
    }

    std::size_t size() const{
        return strlen(_pstr);
    }
    const char* c_str() const{
        return _pstr;
    }

	friend bool operator==(const String &, const String &);
	friend bool operator!=(const String &, const String &);

	friend bool operator<(const String &, const String &);
	friend bool operator>(const String &, const String &);
	friend bool operator<=(const String &, const String &);
	friend bool operator>=(const String &, const String &);

	friend std::ostream &operator<<(std::ostream &os, const String &s);
	friend std::istream &operator>>(std::istream &is, String &s);
    friend void readString(std::istream &is,wd::String &s);
    friend String operator+(const wd::String &s1, const wd::String &s2);
    friend String operator+(const wd::String &s1, const char *s2);


private:
char *_pstr;
};


String operator+(const wd::String &s1, const wd::String &s2){
    char *temp(new char[s1.size()+s2.size()+1]());
    for(size_t idx=0;idx<s1.size();++idx){
        temp[idx]=s1.c_str()[idx];
    }
    /* cout<<"----"<<s1.size()<<"--"<<s2.size()<<endl; */
    for(size_t idx=s1.size();idx<(s1.size()+s2.size());++idx){
        temp[idx]=s2.c_str()[idx-s1.size()];
    }
    /* cout<<"-----"<<temp<<endl; */
    return String(temp);
}
String operator+(const wd::String &s1, const char *s2){
    char *temp(new char[s1.size()+strlen(s2)+1]());
    for(size_t idx=0;idx<s1.size();++idx){
        temp[idx]=s1.c_str()[idx];
    }
    for(size_t idx=s1.size();idx<(s1.size()+strlen(s2));++idx){
        temp[idx]=s2[idx-s1.size()];
    }
    return String(temp);
}
wd::String operator+(const char *s1, const wd::String &s2)
{
    char *temp(new char[strlen(s1)+s2.size()+1]());
    strcpy(temp,s1);
    for(size_t idx=strlen(s1);idx<(strlen(s1)+s2.size());++idx){
        temp[idx]=s2.c_str()[idx-strlen(s1)];
    }
    return temp;
}
bool operator==(const wd::String &s1, const wd::String &s2){
    if(0==strcmp(s1._pstr,s2._pstr)){
        return true;
    }
    return false;
}
bool operator!=(const wd::String &s1, const wd::String &s2){
    if(0!=strcmp(s1._pstr,s2._pstr)){
        return true;
    }
    return false;
}

bool operator<(const wd::String &s1, const wd::String &s2){
    if(-1==strcmp(s1._pstr,s2._pstr)){
        return true;
    }
    return false;
}
bool operator>(const wd::String &s1, const wd::String &s2){
    if(1==strcmp(s1._pstr,s2._pstr)){
        return true;
    }
    return false;
}
bool operator<=(const wd::String &s1, const wd::String &s2){
    if(1==strcmp(s1._pstr,s2._pstr)){
        return false;
    }
    return true;
}
bool operator>=(const wd::String &s1, const wd::String &s2)
{
    if(-1==strcmp(s1._pstr,s2._pstr)){
        return false;
    }
    return true;
}

std::ostream &operator<<(std::ostream &os, const wd::String &s){
    os<<s._pstr;
    return os;
}

void readString(std::istream &is,wd::String &s){
    string temp; 
    while(is>>temp&&is.get()!='\n'){
        if(is.bad()){
            cout<<"the istream is crashed"<<endl;
            return;
        }
        else if(is.fail()){
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            continue;
        }
    }
    if(s._pstr){
        delete []s._pstr;
    }
    s._pstr=new char[temp.size()+1]();
    strcpy(s._pstr,temp.c_str());
}

std::istream &operator>>(std::istream &is, wd::String &s){
    readString(is,s);
    return is;
}

}


#endif
