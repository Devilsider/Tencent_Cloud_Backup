#pragma once
#include "Headquarters.h"
//武士类视图
class WarriorView
{
public:
    WarriorView(WarriorPtr warrior)
    :_warrior(warrior) 
    {}
    void showBorn()const;//武士出生的时候
    void showMarch()const;//武士行军的时候
    void showEarnElements()const;//武士取走城市生命元的时候
    void showReachDestination()const;//武士到达敌方司令部的时候
    ~WarriorView() {}
protected:
    void showName()const;
    void showToCity()const;
    void showInCity()const;
    void showDeath()const;
    void showElementsAndForces()const;


protected: 
    WarriorPtr _warrior;
};

//dragon欢呼类视图
class DragonView
:public WarriorView
{
public:
    DragonView(WarriorPtr warrior)
    :WarriorView(warrior)
    {}

    //dragon在一次它主动进攻的战斗结束后，如果没有战死，就会欢呼
    void showYell()const;
};

//战斗类视图
class BattleView{
public:
    BattleView(WarriorPtr warrior1,WarriorPtr warrior2)
    :_warrior1(warrior1)
     ,_warrior2(warrior2)
    {}

    //武士主动攻击的时候
    void showBattle()const;
    //武士反击的时候
    void showDefense()const;
private:
    WarriorPtr _warrior1;
    WarriorPtr _warrior2;

};


//司令部类视图
class HeadquartersView{
public:
    HeadquartersView(Headquarters *heaquarters)
    :_headquarters(heaquarters)
    {}

    //司令部报告情况时
    void showLeftElements()const;

    //司令部被占领时
    void showBeTaken()const;

private:
    Headquarters * _headquarters;
};

//城市类视图
class CityView{
public:
    CityView(City *city)
    :_city(city)
    {}

    //城市更换旗子的时候
    void showFlag()const;

private:
    City * _city;
};








