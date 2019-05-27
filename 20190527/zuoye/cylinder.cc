#include <math.h>
#include "cylinder.h"
#include <iostream>
using std::cout;
using std::endl;

Cylinder::Cylinder(double r,double h)
:Circle(r),
_height(h)
{
}
double Cylinder::getVolume(){
    return getArea()*_height;
}
void Cylinder::showVolume(){
    cout<<"Cylinder >>"<<endl
        <<"_height  >>"<<_height<<endl
        <<"volume   >>"<<getVolume()<<endl;
}

int main()
{
    Cylinder cylinder(1,5);
    cylinder.show();
    cylinder.showVolume();
    return 0;
}

