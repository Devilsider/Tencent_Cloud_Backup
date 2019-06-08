#pragma once

namespace wd{

class Nocopyable
{
protected:
    Nocopyable() {}
    ~Nocopyable() {}
    
    Nocopyable(const Nocopyable &)=delete ;
    Nocopyable &operator=(const Nocopyable &)=delete ;

};

}
