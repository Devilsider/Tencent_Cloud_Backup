#ifndef __PERSON_h__
#define __PERSON_h__
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
class Person
{
public:
    Person()
    :_name(""),_age(0)
    {

    }
    Person(string name,int age)
    :_name(name),
    _age(age)
    {
    }
    ~Person(){
    }
    virtual void display(){
        cout<<"Person    "<<endl
            <<"_name     >>"<<_name<<endl
            <<"_age      >>"<<_age<<endl;
    }
    string getName();
    int getAge();
    string setName();
    int setAge();
private:
    string _name;
    int _age;
};

#endif
