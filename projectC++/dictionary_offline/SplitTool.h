#pragma once
#include <string>
#include <vector>
using std::vector;
using std::string;  

class SplitTool
{
public:
    SplitTool(){}
    virtual ~SplitTool() {}
    
    virtual vector<string> cut(const string &sentence)=0;
private:

};

