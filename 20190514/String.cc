#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
class String {
public:
	String();
	String(const char *pstr);
	String(const String & rhs);
	String & operator=(const String & rhs);
	~String();

	void print();

private:
	char * _pstr;
};
String::String(){
    _pstr=new char[1]();
}
String::String(const char *pstr)
:_pstr(new char[strlen(pstr)+1]())
{
    strcpy(_pstr,pstr);
}
String::String(const String &rhs)
:_pstr(new char[strlen(rhs._pstr)+1]())
{
    strcpy(_pstr,rhs._pstr);
}
String & String::operator=(const String &rhs){
    if(this!=&rhs){
        delete [] _pstr;
        _pstr=new char[strlen(rhs._pstr)+1]();
        strcpy(_pstr,rhs._pstr);
    }
    return *this;
}
void String::print(){
    if(NULL!=this->_pstr) {
        cout<<"_pstr is "<<this->_pstr<<endl;
    }
}
String::~String(){
    cout<<"this ~String"<<endl;
    delete []this->_pstr;
}
int main(void)
{
	String str1;
	str1.print();

	String str2 = "Hello,world";
	String str3("wangdao");

	str2.print();
	str3.print();

	String str4 = str3;
    str4.print();

	str4 = str2;
	str4.print();

	return 0;
}

