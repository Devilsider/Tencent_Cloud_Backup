#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

class Solution{
public:
    string longestPalindrome(string s) {
        if(s.size()==0){
            return s;
        }
        int len=s.length();
        int start=0;
        int end=0;

        for(int i=0;i<len;++i){
            int len1=expend(s,i,i);
            int len2=expend(s,i,i+1);
            int maxLen=max(len1,len2);
            if(maxLen>(end-start)){
                start=i-(maxLen-1)/2;
                end=i+(maxLen)/2;
            }
        }
        return s.substr(start,end-start+1);
    }

    int expend(string s,int left,int right){
        int l=left;
        int r=right;
        int len=s.length();
        while(l>=0&&r<len&&s[l]==s[r]){
            --l;
            ++r;
        }
        return r-l-1;
    }
};
