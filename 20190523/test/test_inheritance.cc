#include <iostream>
using std::cout;
using std::endl;

class CA{
public:
int _x;
protected:
int _y;
private:
int _z;
};
class CB:private CA{
public:
    void func(){
        _z=7;
        _y=6;
        _x=5;
        cout<<"_z = "<<_z<<endl;
    }
};

int main(){
    CB b;
    b._z=10;
    b._y=3;
    b._x=2;
    return 0;
};
