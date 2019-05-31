#include "Myvector.h"
#include <iostream>


template<typename Container>
void display(const Container &c){
    typename Container::const_iterator it = c.begin();
    for(auto &i:c) {
        cout<<" "<<i;
    }
    cout<<endl;


    cout<<" c size= "<<c.size()<<endl;
    cout<<"   capacity= "<<c.capacity()<<endl;
}

int main()
{
    Myvector<int>  numbers;
    display(numbers);


    for(int idx=0;idx<10;++idx){
        numbers.push_back(idx);
    }

    display(numbers);

    cout<<" numbers[5]= "<<numbers[5]<<endl;
    cout<<" numbers[0]= "<<numbers[0]<<endl;

    for(int idx=0;idx<10;++idx){
        numbers.pop_back();
    }

    display(numbers);

    return 0;
}

