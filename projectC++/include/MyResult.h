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
};


}
