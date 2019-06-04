#include <cmath>
#include <memory>
#include <iostream>
using namespace std;

//面向对象设计原则
//   >开闭原则:对修改关闭，对扩展开放

class Figure{
public:
    virtual void display()const =0;
    
    virtual double area()const =0;
   
    virtual ~Figure(){}

};

class Rectangle
:public Figure
{
public:
    Rectangle(double length,double width)
    :_length(length),_width(width)
    {}

    void display()const{
        cout<<"Rectangle";
    }

    double area()const{
        return _length*_width;
    }

    ~Rectangle(){
        cout<<"~Rectangle()"<<endl;
    }
private:
        double _length;
        double _width;
};

class Circle
:public Figure
{
public:
    Circle(size_t radius)
    :_radius(radius)
    {}

    void display()const{
        cout<<"Circle";
    }

    double area()const{
        return _radius*_radius*M_PI;
    }

    ~Circle(){
        cout<<"~Circle()"<<endl;
    }
private:
        double _radius;
};

class Triangle
:public Figure
{
public:
    Triangle(double a,double b,double c)
    :_a(a),_b(b),_c(c)
    {}

    void display()const{
        cout<<"Triangle";
    }

    double area()const{
        double p=(_a+_b+_c)/2;
        return sqrt(p*(p-_a)+p*(p-_b)+p*(p-_c));
    }

    ~Triangle(){
        cout<<"~Triangle()"<<endl;
    }
private:
    double _a;
    double _b;
    double _c;
};

void display(Figure * fig){
    fig->display();
    cout<<"'s area is "<<fig->area()<<endl;
}

//静态工厂创建
class Factory{
public:
    static Figure *createRectangle(){
        //load xml
        //...
        return new Rectangle(3,4);
    }
    
    static Figure *createCircle(){
        //load xml
        //...
        return new Circle(10);
    }

    static Figure *createTriangle(){
        //load xml
        //...
        return new Triangle(3,4,5);
    }

};


int main()
{
    unique_ptr<Figure> rectangle(Factory::createRectangle());
    unique_ptr<Figure> circle(Factory::createCircle());
    unique_ptr<Figure> triangle(Factory::createTriangle());

    display(rectangle.get());
    display(circle.get());
    display(triangle.get());

    return 0;
}

