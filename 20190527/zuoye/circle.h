#ifndef __CIRCLE_H__
#define __CIRCLE_H__

class Circle
{
public:
    Circle(); //半径置为0
    Circle(double r);//创建circle对象半径初始化为r。
    ~Circle(){}
    double getArea();//获取圆的面积
    double getPerimeter();//获取圆的周长
    virtual void show();//将圆的半径、周长、面积输出到屏幕
private:
double _radius;
};

#endif

