#ifndef __CYLINDER_H__
#define __CYLINDER_H__
#include "circle.h"
class Cylinder:public Circle
{
public:
    Cylinder(double r,double h);//创建circle对象并将半径初始化r，并且将高度初始化为h
    ~Cylinder() {}
    double getVolume();//获取圆柱体体积
    void showVolume();//将圆柱体体积输出到频幕

private:
    double _height;
};

#endif
