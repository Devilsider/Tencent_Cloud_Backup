#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
int arr[10];

void printCapacity(vector<int> &vec){
    cout<<"vec's size "<<vec.size()<<endl;
    cout<<"vec's capacity "<<vec.capacity()<<endl;
}

int main()
{
    vector<int> numbers;
    numbers.reserve(30);
    printCapacity(numbers);
    cout<<"sizeof(numbers)="<<sizeof(numbers)<<endl;

    numbers.push_back(1);
    printCapacity(numbers);
    
    numbers.push_back(1);
    printCapacity(numbers);
    
    numbers.push_back(1);
    printCapacity(numbers);
   
    numbers.push_back(1);
    printCapacity(numbers);
    
    numbers.push_back(1);
    printCapacity(numbers);
   
    for(int idx=0;idx!=10;++idx){
        numbers.push_back(idx);
    }

    for(size_t idx=0;idx!=numbers.size();++idx){
        cout<<numbers[idx]<<" ";

    }
    cout<<endl;

    for(auto &i:numbers){
        cout<<i<<" ";
    }
    cout<<endl;

    for(auto i=numbers.begin();i!=numbers.end();++i){
        cout<<*i<<" ";
    }
    cout<<endl;
   
    cout<<"sizeof(numbers)="<<sizeof(numbers)<<endl;
    return 0;
}

