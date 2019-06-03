#ifndef __HEAD_QUARTERS_H__
#define __HEAD_QUARTERS_H__
#include "warrior.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <map>
using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
using std::atexit;

class HeadQuarters
{
public:
    HeadQuarters()
    :_id(0),_color(-1),_M(-1),_time(0),_lion(0),_iceman(0)
     ,_dragon(0),_ninja(0),_wolf(0)
    {
        /* cout<<"HeadQuarters()"<<endl; */

        _mapWeapon.insert(pair<int,string>(0,"sword"));
        _mapWeapon.insert(pair<int,string>(1,"bomb"));
        _mapWeapon.insert(pair<int,string>(2,"arrow"));
    }
    HeadQuarters(int& id,int& color,int &m,int &time)
    :_id(id),_color(color),_M(m),_time(time),_lion(0),_iceman(0)
     ,_dragon(0),_ninja(0),_wolf(0)
    {
        /* cout<<"HeadQuarters(int& id,int& color,int &m,int &time)"<<endl; */
        _mapWeapon.insert(pair<int,string>(0,"sword"));
        _mapWeapon.insert(pair<int,string>(1,"bomb"));
        _mapWeapon.insert(pair<int,string>(2,"arrow"));
    }
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
    void CreateIceman(int &m,int &life,int &numId,int &color);
    void CreateDragon(int &m,int &life,int &numId,int &color);
    void CreateLion(int &m,int &life,int &numId,int &color);
    void CreateNinja(int &m,int &life,int &numId,int &color);
    void CreateWolf(int &m,int &life,int &numId,int &color);
    //virtual ~HeadQuarters() {}
    
    int getLion(){
        return _lion;
    }
    int getIceman(){
        return _iceman;
    }
    int getDragon(){
        return _dragon;
    }
    int getNinja(){
        return _ninja;
    }
    int getWolf(){
        return _wolf;
    }
    void setWolf(const int &wolf){
        _wolf=wolf;
    }
    void setIceman(const int  &iceman){
        _iceman=iceman;
    }
    void setLion(const int  &lion){
        _lion=lion;
    }
    void setNinja(const int  &ninja){
        _ninja=ninja;
    }
    void setDragon(const int &dragon){
        _dragon=dragon;
    }
    map<int ,string> getWeaponMap(){
        return _mapWeapon;
    }
    void setWeaponMap(const map<int,string> &mapWeapon){
        _mapWeapon=mapWeapon;
    }
private:
    int _id;
    int _color;//0，是红色，1是蓝色
    int _M;//生命元
    int _time;//用计数模拟时间，以后修改
    int _lion;
    int _iceman;
    int _dragon;
    int _ninja;
    int _wolf; 
    map<int,string>  _mapWeapon;
};

class RedHeadQuarter:public HeadQuarters{
public:
    RedHeadQuarter()
    :HeadQuarters(),_numId(0)
    {
    }
    RedHeadQuarter(int &id,int &color,int &M,int &time)
    :HeadQuarters(id,color,M,time),_numId(0)
    { }
    void CreateWarrior(vector<int> &warriorLife);//制造武士
    /* void print(); */
    int getNumId(){
        return _numId;
    }
    void setNumId(int numId){
        _numId=numId;
    }

private:
    int _numId;
};

class BlueHeadQuarter:public HeadQuarters{
public:
    BlueHeadQuarter()
    :HeadQuarters(),_numId(0)
    {}
    BlueHeadQuarter(int &id,int &color,int &M,int &time)
    :HeadQuarters(id,color,M,time),_numId(0)
    {}
    void CreateWarrior(vector<int>& warriorLife);//制造武士
    /* void print(); */
    int getNumId(){
        return _numId;
    }
    void setNumId(int numId){
        _numId=numId;
    }

private:
    int _numId;
};

class GameTime{
    public:
        static GameTime * getInstance(){
            pthread_once(&_once,init);
            return _pInstance;
        }
        static void destroy(){
            if(_pInstance){
                delete _pInstance;
            }
        }
        static void init(){
            _pInstance=new GameTime();
            atexit(destroy);
        }
        void showTime(){
            cout<<"_hour is "<<_hour<<endl;
        }
        int  getTime(){
            return _hour;
        }
        void Time(int init){
            _hour=init;
        }
        void updateTime(){
            ++_hour;
            _hour%=_hour;
        }

        
    private:
        GameTime(){};
        ~GameTime(){};
        int  _hour;//模拟时间
        static GameTime * _pInstance;
        static pthread_once_t _once;
};

#endif
