#pragma once
namespace  wd
{
struct MyNode{
    int _docid;
    double _cos; 
    friend bool operator <(const MyNode &m1,const MyNode &m2)
    {
        if(m1._cos<m2._cos){
            return true;
        }
        return false;
    }
};
}
