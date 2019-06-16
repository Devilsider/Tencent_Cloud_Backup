#pragma once

#include <vector>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::vector;


namespace wd
{

class MinEditDistance
{
public:
    MinEditDistance() {}
    ~MinEditDistance() {}
    int editDistance(const string &s1,const string &s2)
    {
        //初始化二维数组，用于存储动态规划中的中间数值
        int len1=(int)s1.size();
        int len2=(int)s2.size();
        vector<vector<int>> martix(len1+1,vector<int>(len2+1,0));
        for(int j=0;j<len2+1;++j)
        {
            martix[0][j]=j;
        }
        for(int i=0;i<len1+1;++i)
        {
            martix[i][0]=i;
        }
        for(int i=1;i<len1+1;++i)
        {
            for(int j=1;j<len2+1;++j)
            {
                    int f;
                    f = (s1[i]==s2[j])?0:1;
                    martix[i][j]=minOfThree(martix[i-1][j]+1,martix[i][j-1]+1,martix[i-1][j-1]+f);
            }
        }
        return martix[len1][len2];
    }

    int minOfThree(int t1,int t2,int t3)
    {
        int min;
        min = t1>t2?t2:t1;
        min = min>t3?t3:min;
        return min;
    }
private:

};

}
