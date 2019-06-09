#pragma once
#include "data_type.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using std::priority_queue;
using std::unordered_map;
using std::vector;
namespace wd{

class Headquarters
{
public:
    Headquarters(Color color,size_t elements) 
    :_color(color)
     ,_elements(elements)
     ,_earnElements(0)
     ,_nextWarriorIndex(0)
    {}

    virtual  
    ~Headquarters() {}
    
    //创建武士
    WarriorPtr create();
   
    //添加胜利者
    void addWinner(WarriorPtr warrior);

    //奖励胜利者
    void reward();

    //统计从城市获得的生命元
    void increaseElements(size_t elements){
        _earnElements+=elements;
    }

    //设置所剩的生命元数量
    void setElements(size_t elements){
        _elements=elements;
    }

    template<typename Iterator>
        void setWarriorCreatingOrder(Iterator beg,Iterator end){
            //设置武士的生产顺序
            for(;beg!=end;++beg){
                _warriorCreatingOrder.push_back(*beg);
            }
        }

    size_t getId()const {
        return _id;
    }
    void setId(size_t id){
        _id=id;
    }
    Color getColor()const{
        return _color;
    }
    size_t getElements()const{
        return _elements;
    }
    vector<WarriorPtr> &getWarriors(){
        return _warriors;
    }
    
private:
//生产各种武士
    WarriorPtr createIceman(size_t id,size_t hp,size_t forces);
    WarriorPtr createLion(size_t id,size_t hp,size_t forces);
    WarriorPtr createWolf(size_t id,size_t hp,size_t forces);
    WarriorPtr createNinja(size_t id,size_t hp,size_t forces);
    WarriorPtr createDragon(size_t id,size_t hp,size_t forces);

    void nextWarriorType(){
        return _warriorCreatingOrder[_nextWarriorIndex];
    }
protected:
    Color _color;//红或者蓝
    size_t _id;//编号，0代表红色司令部，N+1代表蓝色司令部
    size_t _elements;//当前司令部所剩的生命元
    size_t _earnElements;//一次战斗结束后，所有武士获取的生命元
    size_t _nextWarriorIndex;//下次生产的武士的下标
    vector<WarriorType> _warriorCreatingOrder;//武士生产顺序

    //一段时间结束后，胜利的所有武士
    priority_queue<WarriorPtr,vector<WarriorPtr>,WarriorComparator,> _winners;
    vector<WarriorPtr> _warriors;//生产的武士

    //各种类型的武士的数量。
    unordered_map<WarriorType,size_t> _warriorTypeAmounts;
};

class RedHeadquarters
:public Headquarters
{
public:
    RedHeadquarters(size_t elements)
    :Headquarters(RED,elements)
    { }
};

class BlueHeadquarters
:public Headquarters
{
public:
    BlueHeadquarters(size_t elements)
    :Headquarters(BLUE,elements)
    {}
};

}

