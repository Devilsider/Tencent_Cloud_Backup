#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include <functional>
using namespace std;

bool greaterThan(int number){
    return number>5;
}


int main()
{
    vector <int> numbers{1,2,3,4,5,6,7,8,9};
    std::less<int> lt;
    using namespace placeholders;
    replace_if(numbers.begin(),numbers.end(),bind2nd(lt,5),10);

    copy(numbers.begin(),numbers.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
    return 0;
}

