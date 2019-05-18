#include <string.h>
#include <iostream>

class Object{
public:
    Object(char name[],int id)
    :_name(new char[strlen(name)+1]()),
    _id(id)
    {
        strcpy(_name,name);
    }
    void * operator new (size_t sz){
        void *ret=malloc(sz);
        return  ret;
    }
    void operator delete(void *ret){
        free(ret);
    }
private:
    ~Object(){
        delete[]_name;
    }
    char *_name;
    int _id;
};
int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

