#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
using namespace std;

int test0(){
    vector<int> numbers{1,2,3,4,5,6,7,8,9};

    numbers[0]= numbers[3]=numbers[4]=66;
    copy(numbers.begin(),numbers.end(),ostream_iterator<int>(cout," "));
    cout<<endl;

    auto it = remove(numbers.begin(),numbers.end(),66);

    numbers.erase(remove(numbers.begin(),numbers.end(),66),numbers.end());
    copy(numbers.begin(),numbers.end(),ostream_iterator<int>(cout, " "));
    cout<<endl;
    return 0;
}

int main()
{
    test0() ;
    return 0;
}

