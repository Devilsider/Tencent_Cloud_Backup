#include <iterator>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <iostream>
using namespace std;
/* using std::back_insert_iterator;//vector/list/deque 调用push_back */
/* using std::front_insert_iterator;//list/deque 调用push_front */
/* using std::insert_iterator;      //调用的是insert方法，适用的容器更多 */
int main(void)
{
    vector<int> numbers{1,2,3,4,5} ;
    list<int> numbers2{11,12,13};
    copy(numbers.begin(),numbers.end(),back_insert_iterator<list<int>>(numbers2));
    copy(numbers2.begin(),numbers2.end(),ostream_iterator<int>(cout,","));
    cout<<endl;

    copy(numbers.rbegin(),numbers.rend(),front_insert_iterator<list<int>>(numbers2));
    copy(numbers2.begin(),numbers2.end(),ostream_iterator<int>(cout,","));
    cout<<endl;

    set<int> numbers3{22,23,24,25};
    auto it= numbers3.begin();
    ++it;

    cout<<endl;
    copy(numbers.begin(),numbers.end(),insert_iterator<set<int>>(numbers3,it));
    copy(numbers3.begin(),numbers3.end(),ostream_iterator<int>(cout,","));
    cout<<endl;

    unordered_set<int> numbers4{22,23,24,25};
    auto it4 = numbers4.begin();
    ++it4;

    cout<<endl;
    copy(numbers.begin(),numbers.end(),insert_iterator<unordered_set<int>>(numbers4,it4));
    copy(numbers4.begin(),numbers4.end(),ostream_iterator<int>(cout,","));

    for(auto &i:numbers4){
        cout<<" "<<i;
    }
    cout<<endl;

    unordered_set<int> numbers5{22,23,24,25};
    for(auto i=numbers.begin();i!=numbers.end();++i) {
        numbers5.insert(numbers5.begin(),*i);
    }
    for(auto &i:numbers5){
        cout<<" "<<i;
    }
    cout<<endl;

    unordered_set<int> numbers6{22,23,24,25};
    for(auto i=numbers.begin();i!=numbers.end();++i) {
        numbers6.insert(numbers6.end(),*i);
    }
    for(auto &i:numbers5){
        cout<<" "<<i;
    }
    cout<<endl;
    
    return 0;
}

