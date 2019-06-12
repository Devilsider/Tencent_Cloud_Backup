#pragma once
namespace wd
{

class Noncopyable
{
public:
    Noncopyable() {}
    ~Noncopyable() {}
    Noncopyable(const Noncopyable &)=delete ;
    Noncopyable &operator=(const Noncopyable &)=delete ;
};

}
