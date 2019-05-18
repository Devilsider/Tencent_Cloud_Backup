#include "Computer2.h"
#include <string.h>

#include <iostream>
using std::cout;
using std::endl;

void Computer::setBrand(const char *brand){
    strcpy(_brand,brand);
}
void Computer::setPrice(float price){
    _price=price;
}
void Computer::print(){
    cout<<"brand: "<<_brand<<endl
        <<"price: "<<_price<<endl; 
}


