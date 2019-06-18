#pragma once
#include <string>
using std::string;

namespace wd
{
struct MyResult
{
    string _word;//候选词
    int _iFeq;//词频
    int _iDist;//与查询词的最小编辑距离
    friend bool operator <(MyResult m1,MyResult m2)
    {
        if(m1._iDist<m2._iDist){
            return false;
        }
        else if(m1._iDist==m2._iDist)
        {
            if(m1._iFeq>m2._iFeq){
                return false;
            }
            return true;
        }
        return true;
    }
};


}
