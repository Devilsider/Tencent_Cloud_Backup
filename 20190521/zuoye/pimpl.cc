#include "pimpl.h"
#include <iostream>
using std::cout;
using std::endl;
class Pimpl::Impl{
public:
    Impl(){
        cout<<"Impl()"<<endl;
    }
    ~Impl(){
        cout<<"~Impl()"<<endl;
    }
private:
};

Pimpl::Pimpl()
:_pimpl(new Impl())
{
    cout<<"Pimpl()"<<endl;
}
Pimpl::~Pimpl(){
    if(_pimpl){
        delete _pimpl;
    }
    cout<<"~Pimpl()"<<endl;
}

