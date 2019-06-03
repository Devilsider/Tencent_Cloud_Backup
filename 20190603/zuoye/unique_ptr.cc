#include <memory>
#include <vector>
#include <iostream>
using namespace std;

class Point{
public:
    Point(int ix=0,int iy=0)
    :_ix(ix),_iy(iy)
    {
        cout<<"Point(int, int )"<<endl;
    }
    
    void print(){
        cout<<"("<<_ix
            <<","<<_iy
            <<")"<<endl;
    }
    ~Point(){
        cout<<"~Point(int ,int )"<<endl;
    }
private:
    int _ix;
    int _iy;
};

unique_ptr<Point> getPoint(){
    unique_ptr<Point> point(new Point(3,4));
    return point;
}

int main()
{
    Point * pt =new Point(1,2) ;
    unique_ptr<Point> ap(pt);
    cout<<"ap's get = "<<ap.get()<<endl;
    cout<<"pt = "<<pt<<endl;

    ap->print();
    (*ap).print();

    //unique_ptr<Point> ap2(ap);//不能进行复制或赋值
    //unique_ptr<Point> ap2=ap;//左值
    
    //unique_ptr具有移动语义
    unique_ptr<Point> up = getPoint();//调用移动构造函数
    cout<<"......"<<endl;

    //unique_ptr可以作为容器的元素存在
    vector<unique_ptr<Point>> points;
    points.push_back(unique_ptr<Point>(new Point(3,4)));
    points.push_back(unique_ptr<Point>(new Point(5,6)));
    points.push_back(unique_ptr<Point>(new Point(2,1)));
    points.push_back(unique_ptr<Point>(new Point(7,8)));

    points.push_back(move(ap));//ap,up都是有名对象
    points.push_back(move(up));

    return 0;
}

