#include "MyPage.h"
#include <iostream>
using std::cout;
using std::endl;


namespace wd
{

void MyPage::parse(const string & web)
{
    int docid;
    string title;
    string link; 
    string description;
    string content;

    int idx= 0 ;
    int len =(int)web.size();
    while(idx<len)
    {
        if(web.substr(idx,7)=="<docid>")
        {
            string res =  getSubStr(web,idx,"<docid>","</docid>");
            docid = stoi(res);
        }
        else if(web.substr(idx,7)=="<title>")
        {
            title = getSubStr(web,idx,"<title>","</title>");
        }
        else if(web.substr(idx,6)=="<link>")
        {
            link = getSubStr(web,idx,"<link>","</link>");
        }
        else if(web.substr(idx,13)=="<description>")
        {
            description = getSubStr(web,idx,"<description>","</description>");
        }
        else if(web.substr(idx,9)=="<content>")
        {
            content = getSubStr(web,idx,"<content>","</content>");
        }
        else {
            ++idx;
        }
    }

}
string MyPage::getSubStr(const string &web,int &idx,const string &start,const string &end)
{
    string res;
    idx = idx + (int)start.size();
    int count = idx;
    while(web.substr(count,(int)end.size())!=end)
    {
        ++count;
    }
    res = web.substr(idx, count - idx);
    return res;
}


}//end of namespace 

