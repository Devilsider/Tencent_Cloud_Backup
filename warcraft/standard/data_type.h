#ifndef __DATA_TYPE_H__
#define __DATA_TYPE_H__
#include <string>
using std::string;

enum Color{
    RED,
    BLUE,
    NOTEST
};

enum WarriorType{
    DRAGON_TYPE,
    NINJA_TYPE,
    ICEMAN_TYPE,
    LION_TYPE,
    WOLF_TYPE
};

//为了通过某种颜色或者武士类型，得到字符串，所以实现了了以下的line函数
inline string toString(Color color){
    return (color == RED)?string("red"):string("blue");
}

inline string toString(WarriorType type){
    switch(type){
        case DRAGON_TYPE:return "dragon";
        case NINJA_TYPE:return "ninja";
        case ICEMAN_TYPE:return "iceman";
        case LION_TYPE:return "lion";
        case WOLF_TYPE:return "wolf";
        default:
             return string();
    }
}
#endif
