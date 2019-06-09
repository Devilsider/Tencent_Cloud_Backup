#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution1 {
public:
    string longestPalindrome(string s) {
        //寻找子串,暴力流
        int max=0;
        string maxSub;
        int len = (int)s.size();
        for(int i=0;i<len;++i){
            for(int j=i;j<len;++j){
                string subs(s.substr(i,j-i+1));
                if(palindrome(subs)){
                    if((int)subs.size()>max){
                        max=(int)subs.size();
                        maxSub=subs;
                    }
                }
            }
        }
        return maxSub;
    }

    bool palindrome(string subs){
        //判断回文
        int len = (int)subs.size();
        for(int i=0;i<len;++i){
            if(subs[i]!=subs[len-i-1]){
                return false;
            }
        }
        return true;
    }
};

class Solution2{
public:
    //求最长子串
    string longestPalindrome(string s) {
        if(0==s.size()) {
            return s;
        }
        string revS(s);
        reverse(revS.begin(),revS.end());
        int len=(int)s.size();
        vector<vector<int>> sMartix;
        sMartix.resize(len);
        for(auto &i:sMartix){
            i.resize(len);
        }
        int i,j;
        int maxLen=0,maxEnd=0;
        for( i=0;i<len;++i){
            for( j=0;j<len;++j){
                if(s[i]==revS[j]){
                    if(0==i||0==j){
                        sMartix[i][j]=1;
                    }
                    else {
                        sMartix[i][j]=sMartix[i-1][j-1]+1;
                    }
                }
                if(sMartix[i][j]>maxLen){
                    int beforeRev = len-j-1;
                    if((beforeRev+sMartix[i][j]-1)==i){
                        maxLen=sMartix[i][j];
                        maxEnd=i;
                    }
                }
            }
        }

        return s.substr(maxEnd-maxLen+1,maxLen);
    }
};

class Solution3{
//字符串中心扩展
public:
    string longestPalindrome(string s) {
        if(0==s.size()){
            return s;
        }
        int start=0,end=0;
        int len=(int)s.size();
        for(int i=0;i<len;++i){
            int len1=expandAroundCenter(s,i,i);
            int len2=expandAroundCenter(s,i,i+1);
            int maxLen=max(len1,len2);
            if(maxLen>(end-start)){
                start=i-(maxLen-1)/2;
                end=i+maxLen/2;
            }
        }
        return s.substr(start,end-start+1);
    }

    int expandAroundCenter(string s,int left,int right){
        int l=left;
        int r=right;
        while(l>=0&&r<(int)s.size()&&s[l]==s[r]){
            --l;
            ++r;
        }

        return r-l-1;
    }
};

class Solution4{
public:
    string longestPalindrome(string s) {
        //manacher's algorithm
        string tmpStr=processStr(s);
        int len=(int)s.size();
        vector<int> p;
        p.resize(len);

        int center=0,radius=0;

        for(int i=1;i<len-1;++i){
            int i_mirror=2*center - i;
            if(radius>i){
                p[i]=min(radius-i,p[i_mirror]);
            }
            else{
                p[i]=0;
            }
            while(tmpStr[i+1+p[i]]==tmpStr[i-1-p[i]]){
                ++p[i];
            }
            if(i+p[i]>radius){
                center=i;
                radius=i+p[i];
            }
        }

        int maxLen=0;
        int centerIndex=0;
        for(int i=1;i<len-1;++i){
            if(p[i]>maxLen){
                maxLen=p[i];
                centerIndex=i;
            }
        }

        return s.substr((centerIndex-maxLen)/2,maxLen);
    }

    string processStr(string s){
        int len=(int)s.size();
        if(0==len){
            return "^$";
        }

        string retStr("^");
        for(int i=0;i<len;++i){
            retStr.append("#").append(to_string(s[i]));
        }
        retStr.append("#$");
        return retStr;
    }
};

class Solution5{
    //manacher algorithm
public:
    string processStr(string s){
        int len=(int)s.size();
        if(0==len){
            return "^$";
        }

        string retStr("$#");
        for(int i=0;i<len;++i){
            retStr+=s[i];
            retStr+="#";
        }
        return retStr;
    }
    
    string longestPalindrome(string s) {
        string retStr=processStr(s);
        int len=(int)s.size();
        vector<int> p(s.size(),0);
        int radius=0,center=0,resCenter=0,resLen=0;
        for(int i=0;i<len;++i){
            p[i]=radius > i ? min(p[2*center-i],radius - i):1;
            while(retStr[i+p[i]]==retStr[i-p[i]]){
                ++p[i];
            }
            if(radius<i+p[i]){
                radius=i+p[i];
                center=i;
            }
            if(resLen<p[i]){
                resLen=p[i];
                resCenter=i;
            }
        }
        return s.substr((resCenter - resLen)/2,resLen-1);
    }
};

int main(){
    Solution5 s5;
    string s1 = "bananas";
    cout<<s5.processStr(s1) <<endl;
    cout << s5.longestPalindrome(s1) << endl;
    string s2 = "122122";
    cout << s5.longestPalindrome(s2) << endl;
    string s = "waabwswfd";
    cout << s5.longestPalindrome(s) << endl;
}


