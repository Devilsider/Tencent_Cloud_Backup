#ifndef __EMPLOYEE_H__
#define __EMPLOYEE_H__
#include "person.h"
#include <iostream>
class Employee:public Person
{
public:
    Employee()
    :Person(),
    _salary(0),
    _department("")
    {

    }
    Employee(string name,int age,double salary,string department)
    :Person(name,age),
    _salary(salary),
    _department(department)
    {
    } 
    ~Employee() {}
    double getSalary(){
        return _salary;
    }
    string getDepartment();
    double setSalary();
    string setDepartment();
    void display(){
        Person::display();
        cout<<"Employee     "<<endl
            <<"_salary      >>"<<_salary<<endl
            <<"_department  >>"<<_department<<endl;
    }
private:
    double _salary;
    string _department;
};
#endif
