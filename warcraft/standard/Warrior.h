#ifndef __WARRIOR_H__
#define __WARRIOR_H__
#include "data_type.h"
#include "Headquarters.h"
#include <memory>

namespace warcraft{

class Warrior
:public std::enable_shared_from_this<Warrior>
{
public:
    Warrior(Color color,
            const string &name,
            size_t id,
            size_t hp,
            size_t forces,
            WarriorType type) 
        :_color(color),
        _name(name),
        _id(id),
        _hp(hp),
        _forces(forces),
        _type(type)
    {}
    virtual ~Warrior() {}

    virtual void march();//行军
    virtual void attack(WarriorPtr warrior);//攻击另一个武士
    virtual void defense(WarriorPtr warrior);//反击另一个武士

    void beWinner();//成为胜利者
    void beRewarded();//被奖励
    void sentElementsToHeadquarters(size_t elements);//为司令部获取生命元

    void setHp(size_t hp){
        _hp=hp;
    }
    void setCity(size_t id){
        _cityId=id;
    }
    void setHeadquarters(Headquarters *headquarters){
        _headquarters=headquarters;
    }

    Color getColor()const{
        return _color;
    }
    string getName()const{
        return _name;
    }
    size_t getId()const{
        return _id;
    }
    size_t getHp()const{
        return _hp;
    }
    size_t getCityId()const{
        return _cityId;
    }
    size_t getElements()const{
        return _hp;
    }
    size_t getEarnElements()const{
        return _earnElements;
    }
    size_t getForces()const{
        return _forces;
    }
    WarriorType getType()const{
        return _type;
    }

protected:
    Color _color;
    string _name;
    size_t _id;//编号
    size_t _hp;//生命值
    size_t _forces;//攻击力
    size_t _cityId;//位于某个城市
    size_t _earnElements;//从某个城市中获取的生命元
    WarriorType _type;
    Headquarters *_headquarters;

};


class Dragon
:public Warrior
{
public:
    Dragon(Color color,size_t id,size_t hp,size_t forces,float morale)
    :Warrior(color,"dragon",id,hp,forces,DRAGON_TYPE),
    _morale(morale)
    {}

    virtual float getMorale()const {
        return _morale;
    }


private:
    float _morale;
};

class Ninja
:public Warrior
{
public:
    Ninja(Color color,size_t id,size_t hp,size_t forces)
    :Warrior(color,"ninja",id,hp,forces,NINJA_TYPE)
    {}

    virtual void defense(WarriorPtr warrior)override;
};

class Iceman
:public Warrior
{
public:
    Iceman(Color color,size_t id,size_t hp,size_t forces)
    :Warrior(color,"iceman",id,hp,forces,ICEMAN_TYPE)
     ,_steps(0)
    {}
    //iceman每前进两步，在第二步完成的时候，生命值会减少9，攻击力会增加20
    //但是若生命值减9后会小于等于0，则生命值不减9，而是变为1，即iceman不会因为
    //走多了而死
    //需要覆盖
    virtual void march()override;
private:
    size_t _steps;
};

class Lion
:public Warrior
{
public:
    Lion(Color color,size_t id,size_t hp,size_t forces,size_t loyalty)
    :Warrior(color,"lion",id,hp,forces,LION_TYPE)
     ,_loyalty(loyalty)
    {

    }
    
    virtual size_t getLoyalty()const override{
        return _loyalty;
    }
private:
    size_t _loyalty;
};

class Wolf 
:public Warrior
{
public:
    Wolf(Color color,size_t id,size_t hp,size_t forces)
    :Warrior(color,"wolf",id,hp,forces,WOLF_TYPE)
    {}

    //在一个wolf通过主动攻击杀死敌人的次数达到偶数的时刻（次数从1开始算），在战斗完成后，
    //该wolf生命值和攻击力都增加一倍.如果其杀死的敌人是lion，则攻击和生命值先加倍，然后才
    //吸取lion的生命值。 获取 总部的生命元奖励，发生加倍之后。只有在主动攻击杀死敌人之时才
    //能有加倍的事情，反击杀死敌人则不会发生加倍。
    //须覆盖
    
    virtual void attack(WarriorPtr warrior)override;

private:
    int _killTimes;//击杀次数
};

}
#endif
