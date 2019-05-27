#ifndef __WARCRAFT__HEADQUARTERS_H__
#define __WARCRAFT__HEADQUARTERS_H__
#include <vector>
#include <unordered_map>
#include "Types.h"
using namespace std;

namespace warcraft{
class Weapon;
class WeaponView;
class Warrior;
class WarriorView;

class Headquarters
{
public:
    Headquarters(Color color,size_t elements) 
    :_color(color)
     ,_elements(elements)
     ,_nextWarriorIndex(0)
    {}

    virtual ~Headquarters() {LogDebug("~Headquarters()");} 
    virtual WarriorPtr create();
    template<typename Iterator>
        void setWarriorCreatingOrder(Iterator beg,Iterator end){
            for(;beg!=end;++beg){
                _warrirorCreatingOrder.push_back(*beg);
            }
        }

    Color getColor()const {
        return _color;
    }

    WarriorViewPtr getWarriorView(WarriorPtr warrior){return _warriorViews[warrior];}
    WeaponViewPtr getWeaponView(WeaponPtr weapon){return _weaponViews[weapon];}
    size_t getWarriorAmount(WarriorType type){return  _warriorTypeAmounts[type];}
    size_t getWarriorTotalAmount()const{return _warriors.size();}
private:
    void nextWarriorType();
protected:
    Color _color;
    size_t _elements;
    size_t _nextWarriorIndex;
    vector<WarriorType> _warrirorCreatingOrder;

    vector<WarriorPtr> _warriors;

    unordered_map<WeaponPtr,WeaponViewPtr> _weaponViews;
    unordered_map<WarriorPtr,WarriorViewPtr> _warriorViews;
    unordered_map<WarriorType,size_t> _warriorTypeAmounts;
};



}
#endif
