#include <iostream>
using std::cout;
using std::endl;
class Point{
public:
    Point(int ix=0,int iy=0)
    :_ix(ix),_iy(iy)
    {
        cout<<_ix<<","<<_iy<<endl;
        cout<<"Point(int,int)"<<endl;
    }
    void print(){
        cout<<"("<<this->_ix
            <<","<<this->_iy
            <<")";
    }
    ~Point(){
        cout<<"~Point()"<<endl;
    }
private:
    int _ix;
    int _iy;
};
class Line{
public:
    Line(int x1,int y1,int x2, int y2)
    :_pt1(x1,y1),_pt2(x2,y2)
    {
        cout<<"Line (int ,int ,int ,int )"<<endl;
    }
    void printLine(){
        _pt1.print();
        cout<<"-->"<<endl;
        _pt2.print();
        cout<<"-->"<<endl;
    }
private:
    Point _pt1;
    Point _pt2;
};
int main()
{
    Line line(1,2,3,4);
    line.printLine();
    //std::cout << "Hello world" << std::endl;
    return 0;
}

