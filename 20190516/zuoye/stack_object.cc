#include<stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
using std::cout;
using std::endl;

class Object{
public:
    Object(char *name,int id)
    :_name(new char[strlen(name)+1]())
     ,_id(id)
    {
        strcpy(_name,name);
        cout<<"I am Object(char *,int)"<<endl;
    }
    ~Object(){
        cout<<"I am ~Object"<<endl;
        if(_name){
            delete []_name;
        }
    }
    void print(){
        cout<<"name ="<<_name<<endl
            <<"id ="<<_id<<endl;
    }
    void destroy(){
        delete  this;
    }
private:
    void * operator new(size_t sz){
        cout<<"new malloc size"<<endl;
        void *ret=malloc(sz);
        return ret;
    }
    void operator delete(void *ret){
        cout<<"new delete size" <<endl;
        free(ret);
    }
    char *_name;
    int _id;
};

int main()
{
    //Object *obj=new Object("zsk",123456);
    Object obje("zsk",1234456);
    obje.print();
    //obje.destroy();
    return 0;
}

