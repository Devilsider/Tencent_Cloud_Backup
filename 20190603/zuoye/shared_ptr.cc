#include <memory>
#include <vector>
#include <iostream>
using namespace std;

class Point{
public:
    Point(int ix,int iy)
    :_ix(ix),_iy(iy)
    {
        cout<<"Point(int,int)"<<endl;
    }

    void print(){
        cout<<"("<<_ix
            <<","<<_iy
            <<")"<<endl;
    }

    ~Point(){
        cout<<"~Point(int ,int)"<<endl;
    }
private:
    int _ix;
    int _iy;
};

shared_ptr<Point> getPoint(){
    shared_ptr<Point> point(new Point(3,4));
    return point;
}


int main()
{
    Point *pt=new Point(1,2);
    shared_ptr<Point> ap(pt);
    cout<<"ap's get = "<<ap.get()<<endl;
    cout<<"pt = "<<pt<<endl;

    ap->print();
    (*ap).print();
    
    shared_ptr<Point> ap2(ap);//进行复制或赋值，将引用计数增加
    {
        shared_ptr<Point> ap3=ap;
        cout<<"ap3's get = "<<ap3.get()<<endl;
        cout<<"ap3's use_count = "<<ap3.use_count()<<endl;
        cout<<"ap2's get = "<<ap2.get()<<endl;
        cout<<"ap2's use_count = "<<ap2.use_count()<<endl;
    }//当一个共享数据销毁的时候，将引用计数减去1；知道引用计数为0的时候
    //才真正回收堆空间的数据
    cout<<"退出语句块:"<< endl;
    cout<<"ap2's get = "<<ap2.get()<<endl;
    cout<<"ap2's use_count = "<<ap2.use_count()<<endl;
    //shared_ptr具有移动语义
    shared_ptr<Point> up = getPoint();
    cout<<"......"<<endl;
    up=ap;
    cout<<"up's get = "<<up.get()<<endl;
    cout<<"up's use_count = "<<up.use_count()<<endl;

    vector<shared_ptr<Point>> points;
    points.push_back(shared_ptr<Point>(new Point(3,4)));
    points.push_back(shared_ptr<Point>(new Point(3,4)));
    points.push_back(shared_ptr<Point>(new Point(3,4)));


    points.push_back(ap);
    points.push_back(up);
    return 0;
}

