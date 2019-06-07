#ifndef __WARRIOR_H__
#define __WARRIOR_H__
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

class Warrior
{
public:
    Warrior() 
    :_id(0),
    _hp(0),
    _color(-1)
     ,_city_num(0)
    {}
    Warrior(int &id,int &hp,int &color)
    :_id(id),_hp(hp),_color(color)
    {}
    ~Warrior() {}
    int getId(){
        return _id;
    }
    double getHp(){
        return _hp;
    }
    int getColor(){
        return _color;
    }
    int getCityNum(){
        return _city_num;
    }
    void setId(int &id){
        _id=id;
    }
    void setHp(double &hp){
        _hp=hp;
    }
    void setColor(int &color){
        _color=color;
    }
    void setCityNum(int CityNum){
        _city_num=CityNum;
    }
    virtual void print(){
        cout<<"Warrior "<<endl
            <<"-------id = "<<_id<<endl
            <<"-------hp = "<<_hp<<endl
            <<"-------color = "<<_color<<endl;
    }
    virtual void attcak(){
        
    }
private:
    int _id;//编号
    double _hp;//生命值
    int _color;//用数字代替字符，0为红，1为蓝
    int _city_num;//city num，所处的city的编号
};

class Dragon:public Warrior{
public:
    Dragon()
    :Warrior(),_weapon(-1),_morale(-1)
    {}
    Dragon(int &id,int &hp,int &color,int &weapon,double &morale)
    :Warrior(id,hp,color),_weapon(weapon),_morale(morale)
    {
    }
    int getWeapon(){
        return _weapon;
    }
    int getMorale(){
        return _morale;
    }
    void setWeapon(int &weapon){
        _weapon=weapon;
    }
    void setMorale(int &morale){
        _morale=morale;
    }
    void print(){
        Warrior::print();
        cout<<"Dragon "<<endl
            <<"-------weapon = "<<_weapon<<endl
            <<"-------morale = "<<_morale<<endl;
    }

private:
    int _weapon;//0,1,2
    double _morale;//士气
};

class Ninja:public Warrior
{
public:
    Ninja()
    :Warrior(),_weapon()
    { }
    Ninja(int &id,int &hp,int &color,vector<int> &weapon)
    :Warrior(id,hp,color),
    _weapon(weapon)
    {}
    vector<int> getWeapon(){
        return _weapon;
    }
    void setWeapon(vector<int> &weapon){
        _weapon=weapon;
    }
    void print(){
        Warrior::print();
        cout<<"Ninja "<<endl
            <<"-------weapon1 = "<<_weapon[0]<<endl
            <<"-------weapon2 = "<<_weapon[1]<<endl;
    }
private:
    vector<int> _weapon;
};

class Iceman:public Warrior{
public:
    Iceman()
    :Warrior(),_weapon()
    { }
    
    Iceman(int &id,int &hp,int &color,int  &weapon)
    :Warrior(id,hp,color),
    _weapon(weapon)
    {}

    int getWeapon(){
        return _weapon;
    }
    void setWeapon(int &weapon){
        _weapon=weapon;
    }
    void print(){
        Warrior::print();
        cout<<"Iceman "<<endl
            <<"-------weapon = "<<_weapon<<endl;
    }
private:
    int _weapon;
};

class Lion:public Warrior{
public:
    Lion()
    :Warrior(),_loyalty()
    { }
    Lion(int &id,int &hp,int &color,int  &loyalty)
    :Warrior(id,hp,color),
    _loyalty(loyalty)
    {}
    int getloyalty(){
        return _loyalty;
    }
    void setloyalty(int &loyalty){
        _loyalty=loyalty;
    }
    void print(){
        Warrior::print();
        cout<<"Lion "<<endl
            <<"-------loyalty = "<<_loyalty<<endl;
    }
private:
    int _loyalty;
};
class Wolf:public Warrior{
public:
    Wolf()
    :Warrior()
    { }
    Wolf(int &id,int &hp,int &color)
    :Warrior(id,hp,color)
    {}
    void print(){
        Warrior::print();
        cout<<"Wolf "<<endl;
    }
private:
};
#endif
