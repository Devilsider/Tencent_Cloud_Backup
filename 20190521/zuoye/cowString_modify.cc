#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;

class CowString
{
public:
	CowString();
	CowString(const char * pstr);
	CowString(const CowString & rhs);
	CowString & operator=(const CowString & rhs);

    ~CowString();

	const char * c_str() const {	return _pstr;	}
	int size() const {	return strlen(_pstr);	}
	int refcount() {	return *((int*)(_pstr - 4));	}
    const char & operator[](int idx)const;

    //采用代理类来区分[]的读写,设计模式之代理模式，[]只和代理类打交道
    class CharProxy{
    public:
        CharProxy(int idx,CowString &str)
        :_index(idx),
        _cowString(str)
        {
            cout<<"CharProxy(int,char*)"<<endl;
        }
        CharProxy &operator=(const char &ch);//执行写操作
        friend std::ostream& operator<<(std::ostream &os,const CharProxy &rhs);//执行读操作
    private:
        int  _index;
        CowString &_cowString;
    };

    CharProxy operator[](int idx){
        return CharProxy(idx,*this);
    }
private://inline
	void initRefcount() {	*((int*)(_pstr - 4)) = 1; }
	void increaseRefcount() {	++*((int*)(_pstr - 4));	}
	void decreaseRefcount() {	--*((int*)(_pstr - 4)); }
	void release() 
	{
		decreaseRefcount();
		if(refcount() == 0) {
			delete [] (_pstr - 4);
			cout << ">>> delete data!" << endl;
		}
	}

private:
	char * _pstr;//_pstr永远指向字符串的第一个元素
};

CowString::CowString()
: _pstr(new char[1 + 4]() + 4)
{
	cout << "CowString()" << endl;
	initRefcount();
}

CowString::CowString(const char * pstr)
: _pstr(new char[strlen(pstr) + 5]() + 4)
{
	initRefcount();
	strcpy(_pstr, pstr);
	cout << "CowString(const char * )" << endl;
}

CowString::CowString(const CowString & rhs)
: _pstr(rhs._pstr)
{
	cout << "CowString(const CowString &)" << endl;
	increaseRefcount();
}

CowString & CowString::operator=(const CowString & rhs)
{
	cout << "CowString & operator=(const CowString &)" << endl;
	if(this != & rhs) {
		release();

		_pstr = rhs._pstr;
		increaseRefcount();
	}
	return *this;
}

CowString::~CowString()
{
	release();
}

//下标访问运算符无法区分出接下来的操作是读操作还是写操作
//
//实现的只有写操作, 没有考虑读操作的问题
const char & CowString::operator[](int idx)const
{
	cout << "const char & operator[](int idx)const " << endl;
		return _pstr[idx];
}

std::ostream & operator<<(std::ostream & os, const CowString & rhs)
{
	os << rhs.c_str();
	return os;
}

CowString::CharProxy &CowString::CharProxy::operator=(const char &ch){
    //执行写操作
	cout << "char & operator[](int idx) " << endl;
	if(_index >= 0 && _index < _cowString.size()) {
		if(_cowString.refcount() > 1) {
		    //初始化开始，新开辟一个string	
            _cowString.decreaseRefcount();
			char * ptmp = new char[_cowString.size() + 5]() + 4;
			strcpy(ptmp, _cowString._pstr);
			_cowString._pstr = ptmp;
			_cowString.initRefcount();
            //初始化结束,修改_index处的值
            //修改
            _cowString[_index]=ch;
		}
	}else {
		cout << "下标越界!" << endl;
	}
    return *this;
}

std::ostream& operator<<(std::ostream &os,const CowString::CharProxy &rhs){
//执行读操作
    os<<rhs._cowString.c_str()[rhs._index];
    return os;
}


int main(void)
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
