#ifndef __HEAD_QUARTERS_H__
#define __HEAD_QUARTERS_H__
#include "warrior.h"
#include <iostream>
using std::cout;
using std::endl;

class HeadQuarters
{
public:
    HeadQuarters()
    :_id(0),_color(-1),_M(-1),_time(0)
    {}
    HeadQuarters(int& id,int& color,int &m,int &time)
    :_id(id),_color(color),_M(m),_time(time)
    {}
    int getId(){
        return _id;
    }
    int getColor(){
        return _color;
    }
    int getM(){
        return _M;
    }
    int getTime(){
        return _time;
    }
    void setId(int &id){
        _id=id;
    }
    void setColor(int &color){
        _color=color;
    }
    void setM(int &m){
        _M=m;
    }
    void setTime(int& t){
        _time=t;
    }
    virtual void print(){
        cout<<"HeadQuarters "<<endl
            <<"-------------id = "<<_id<<endl
            <<"-------------color = "<<_color<<endl
            <<"-------------M = "<<_M<<endl
            <<"-------------time = "<<_time<<endl;
    }
    ~HeadQuarters() {}
private:
    int _id;
    int _color;//0，是红色，1是蓝色
    int _M;//生命元
    int _time;//用计数模拟时间，以后修改
};

class RedHeadQuarter:public HeadQuarters{
public:
    RedHeadQuarter()
    :HeadQuarters()
    {}
    RedHeadQuarter(int &id,int &color,int &M,int &time)
    :HeadQuarters(id,color,M,time)
    { }
    void CreateWarrior(vector<int> &warriorLife);//制造武士
    void print();

private:
};
class BlueHeadQuarter:public HeadQuarters{
public:
    BlueHeadQuarter()
    :HeadQuarters()
    {}
    BlueHeadQuarter(int &id,int &color,int &M,int &time)
    :HeadQuarters(id,color,M,time)
    { }
    void CreateWarrior(vector<int>& warriorLife);//制造武士
    void print();
private:
};
#endif
