#include "circle.h"

#include <math.h>
#include <string>
#include <iostream>
using std::cout;
using std::endl;

Circle::Circle()
:_radius(0)
{
}
Circle::Circle(double r)
:_radius(r)
{
}
double Circle::getArea()
{
    return (_radius*_radius*M_PI);
}
double Circle::getPerimeter(){
    return (_radius*2*M_PI);
}
void Circle::show(){
    cout<<"Circle   >>"<<endl
        <<"_radius  >>"<<_radius<<endl
        <<"area     >>"<<getArea()<<endl
        <<"perimeter>>"<<getPerimeter()<<endl;
}
/* int main() */
/* { */
/*     Circle cir(10) ; */
/*     cir.show(); */
/*     return 0; */
/* } */

