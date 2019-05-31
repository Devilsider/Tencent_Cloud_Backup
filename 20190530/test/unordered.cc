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


int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

