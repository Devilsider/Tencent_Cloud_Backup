#pragma once
#include "data_type.h"
#include <iostream>
#include <vector>

namespace warcraft{

class City
{
public:
    City(size_t id,size_t elements=0)
    :_flag(Color::NOTEST)
     ,_id(id)
     ,_elements(elements)
     ,_redWinCount(0)
     ,_blueWinCount(0)
    {}

    void produceElements();//城市生产生命元
    void attach(WarriorPtr);//某武士进入该城市
    void detach(WarriorPtr);//某武士离开该城市
    void startBattle();//开始战斗
    void takenBy(WarriorPtr warrior);//生命元被武士抽走

    size_t getId()const{
        return _id;
    }

    Color getFlag()const{
        return _flag;
    }

    size_t getWarriorAmount(){
        return _redWarrior.size()+_blueWarrior.size();
    }

    vector<WarriorPtr>& getRedWarriors(){
        return _redWarriors;
    }
    vector<WarriorPtr>& getBlueWarriors(){
        return _blueWarrior;
    }
private:
    void battle(WarriorPtr warrior1,WarriorPtr warrior2);//两名武士的战斗情况
    bool isChangingFlag(WarriorPtr warrior);

private:
    Color _flag;//城市的颜色
    size_t _id;//城市编号
    size_t _elements;//城市生命元
    size_t _redWinCount;//红方连续获胜次数
    size_t _blueWinCount;//蓝方连续获胜次数
    vector<WarriorPtr> _redWarrior;
    vector<WarriorPtr> _blueWarrior;
};

}

