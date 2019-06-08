#pragma once

namespace wd{

class Noncopyable
{
protected://抽象类
    Noncopyable(){}
    ~Noncopyable(){}

    Noncopyable(const Noncopyable&)=delete ;
    Noncopyable & operator=(const Noncopyable&)=delete ;

};

}
