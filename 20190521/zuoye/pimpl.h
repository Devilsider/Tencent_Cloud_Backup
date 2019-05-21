#ifndef __PIMPL_H__
#define __PIMPL_H__ 
class Pimpl
{
public:
    Pimpl();
    ~Pimpl();
    class Impl;
private:
    Impl *_pimpl;
};

#endif
