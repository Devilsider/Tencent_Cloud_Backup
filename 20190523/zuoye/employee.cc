#include "employee.h"
#include <iostream>

int main()
{
    Employee e1("zsk",20,100,"ml"),e2("devilsider",25,50,"dl"),
             e3("win",21,200,"os"); 
    Person *pperson;
    pperson=&e1;
    pperson->display();
    pperson=&e2;
    pperson->display();
    pperson=&e3;
    pperson->display();
    
    cout<<"average salary is "<<(e1.getSalary()+e2.getSalary()+e3.getSalary())/3<<endl;
    return 0;
}

