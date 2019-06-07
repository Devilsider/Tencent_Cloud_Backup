#ifndef __WARRIOR_H__
#define __WARRIOR_H__
#include "data_type.h"
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
    :Warrior(color,"dragon",id,hp,forces,DRAGON_TYPE)
    {

    }
private:
    float _morale;
};
}
#endif
