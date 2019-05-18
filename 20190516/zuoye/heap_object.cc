#include<string.h>
#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;

class Object{
public:
    Object(char name[],int id)
    :_name(new char[strlen(name)+1]()),
    _id(id)
    {
        cout<<"I am ObjectZ(char *,int)"<<endl;

        strcpy(_name,name);

    }
    void * operator new(size_t sz){
        cout<<"I am operator new"<<endl;
        void *ret=malloc(sz);
        return  ret;
    }
    void  operator delete(void *ret){
        cout<<"I am operator delete"<<endl;
        free(ret);
    }
    void destroy(){
        cout<<"I am destroy()"<<endl;
        delete  this;
    }
    void print(){
        cout<<"name ="<<_name<<endl
            <<"id="<<_id<<endl;
    }
private:
    ~Object() {
        delete []_name;
    }
    char *_name;
    int _id;
};


int main()
{
    Object *obj=new Object("zsk",123456);
    obj->print();
    //Object obje("zsk",123456);
    obj->destroy();
    return 0;
}

