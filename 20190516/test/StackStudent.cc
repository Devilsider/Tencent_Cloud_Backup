#include <string.h>
#include <stdlib.h>

#include <iostream>
using std::cout;
using std::endl;
class Student{
public:
    Student(const char *name,int id)
    :_name(new char[strlen(name)+1]())
     ,_id(id)
    {
        cout<<"Student(const char *,int)"<<endl;
        strcpy(_name)
    }
private:
    char *_name;
    int _id;
}
int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

