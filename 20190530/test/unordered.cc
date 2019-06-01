#include <cmath>
#include <iostream>
#include <unordered_set>
using std::cout;
using std::endl;
using std::unordered_set;

class Point{
public:
    Point(int ix=0,int iy=0)
    :_ix(ix),_iy(iy)
    {
        cout<<"Point(int , int )"<<endl;
    }

    float getDistance()const{
        return sqrt(_ix*_ix+_iy*_iy);
    }

    int getX()const{
        return _ix;
    }
    int getY()const{
        return _iy;
    }

    friend std::ostream & operator<<(std::ostream &os,const Point &rhs);

private:
    int _ix;
    int _iy;
};

std::ostream &operator<<(std::ostream &os,const Point &rhs){
    os<<"("<<rhs._ix
      <<","<<rhs._iy
      <<")";
    return os;
}


struct PointComparator{
    bool operator()(const Point &lhs,const Point &rhs){
        return lhs.getDistance()>rhs.getDistance();
    }
};

bool operator==(const Point &lhs,const Point &rhs){
        return (lhs.getX()==rhs.getX())&&
               (lhs.getY()==rhs.getY());
}

namespace  std{
template<>
    struct hash<Point>
    {
        size_t operator()(const Point & rhs)const{
            return ((rhs.getX()*rhs.getX())>>1)^
                (rhs.getY()*rhs.getY()>>1);
        }
    };
}

struct PointHasher{
    size_t operator()(const Point &rhs)const {
            return ((rhs.getX()*rhs.getX())>>1)^
                (rhs.getY()*rhs.getY()>>1);
    }
};

struct PointEqual{
    bool operator()(const Point &lhs,const Point &rhs)const{
        return (lhs.getX()==rhs.getX())&&(lhs.getY()==rhs.getY());
    }
};

void test0(){
    unordered_set<Point,PointHasher,PointEqual> points{
        Point(1,2),
        Point(1,2),
        Point(3,4),
        Point(5,6),
        Point(-1,2),
        Point(7,8)
    };
    auto it=points.begin();
    for(;it!=points.end();++it){
        cout<<*it<<" ";
    }
    cout<<endl;

    auto ret=points.insert(Point(-1,4));
    if(ret.second){
        cout<<"添加成功！"<<endl;
        cout<<*ret.first<<endl;
    }
    else{
        cout<<"添加失败!"<<endl;
        cout<<*ret.first<<endl;
    }
}


int main()
{
    test0() ;
    return 0;
}

