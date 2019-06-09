#include <vector>
#include <iostream>
#include <string>
#include <array>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if(s.size()==0||numRows==0||numRows==1){
            return s;
        }
        int mod=numRows*2-2;
        int len=s.length();
        int numColumns=((len/mod)+1)*2;

        vector<vector<char>>  martix(numRows,vector<char>(numColumns,0));//设定行号和列号
        
        int count=0;
        if(numRows==2){
            for(int j=0;j<numColumns;++j){
                for(int i=0;i<numRows;++i){
                        if(count==len)
                        {
                            break;
                        }
                    martix[i][j]=s[count];
                    ++count;
                }
            }
        }
        else{
            for(int j=0;j<numColumns;++j){
                for(int i=0;i<numRows;++i){
                    if(!isOdd(j)){
                        if(count==len)
                        {
                            break;
                        }
                        martix[i][j]=s[count];
                        ++count;
                    }
                    else{
                        if(i==numRows-2){
                            break;
                        }
                        if(count==len)
                        {
                            break;
                        }
                        martix[numRows-2-i][j]=s[count];
                        ++count;
                    }
                }
            }
        }
        //处理数组
        string retStr;
        for(int i=0;i<numRows;++i){
            for(int j=0;j<numColumns;++j){
                if(isalpha(martix[i][j])||ispunct(martix[i][j])){
                    retStr+=martix[i][j];
                }
            }
        }
        return retStr;
    }
    bool isOdd(int n){
        if((n&1)==1){
            return true;
        }
        return false;
    }
};

class Solution2{
public:
    string convert(string s, int numRows){
        if(numRows==1){
            return s;
        }

        string retStr;
        int len = s.length();
        int cyclen=2*numRows-2;
        //迭代的思想
        for(int i=0;i<numRows;++i){
            for(int j=0;j+i<len;j+=cyclen){
                retStr+=s[j+i];
                if(i!=0&&i!=numRows-1&&j+cyclen-i<len){
                    retStr+=s[j+cyclen-i];
                }
            }
        }
        return retStr;
    }
};
int main()
{
    Solution2 s; 
    string ret = s.convert("PAYPALISHIRING",4);

    cout<< ret <<endl;
    return 0;
}

