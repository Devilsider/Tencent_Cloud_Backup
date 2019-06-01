#include <cmath>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

void test0(){
    int array[10] = {5,7,1,3,2,6,4,0,9,8};

    //priority_queue<int > que(array,array + 10);
    //
    //默认情况下，使用于小于符号比较，得到的是一个降序排列(大顶堆)
    //
    //底层实现，堆排序，==>二叉堆，大顶堆小顶堆
    priority_queue<int> que;

    for(int idx=0;idx!=10;++idx){
        que.push(array[idx]);
        cout<<"此时优先级最高的元素是: "<<que.top()<<endl;
    }

    while(!que.empty()){
        cout<<que.top()<<" ";
        que.pop();
    }
    cout<<endl;
}
void test1(){
    int array[10] = {5,7,1,3,2,6,4,0,9,8};

    //priority_queue<int > que(array,array + 10);
    //
    //默认情况下，使用于小于符号比较，得到的是一个降序排列(大顶堆)
    //
    //底层实现，堆排序，==>二叉堆，大顶堆小顶堆
    priority_queue<int,vector<int>,std::greater<int>> que;

    for(int idx=0;idx!=10;++idx){
        que.push(array[idx]);
        cout<<"此时优先级最高的元素是: "<<que.top()<<endl;
    }

    while(!que.empty()){
        cout<<que.top()<<" ";
        que.pop();
    }
    cout<<endl;
}

class Point{
public:
    Point(int ix=0,int iy=0)
    :_ix(ix),_iy(iy)
    {
        cout<<" Point(int,int)"<<endl;
    }

    float getDistance()const{
        return sqrt((_ix*_ix)+(_iy*_iy));
    }

    friend std::ostream &operator<<(std::ostream &os,const Point &rhs);
    
private:
    int _ix;
    int _iy;
};
std::ostream &operator<<(std::ostream &os,const Point &rhs)
{
    os<<"("<<rhs._ix
      <<","<<rhs._iy
      <<")";
    return os;
}

bool operator<(const Point &lhs,const Point &rhs){
    return lhs.getDistance()<rhs.getDistance();
}

struct PointComparator{
    bool operator()(const Point &lhs,const Point &rhs)const {
        return lhs.getDistance()>rhs.getDistance();
    }
};

void test2(){
    priority_queue<Point ,vector<Point>,PointComparator> que;
    que.push(Point(1,2));
    que.push(Point(-1,2));
    que.push(Point(3,2));
    que.push(Point(4,2));
    que.push(Point(1,6));

    while(!que.empty()){
        cout<<que.top()<<" ";
        que.pop();
    }
    cout<<endl;
}
int main()
{
    /* test0() ; */
    /* test1() ; */
    test2();
    return 0;
}

