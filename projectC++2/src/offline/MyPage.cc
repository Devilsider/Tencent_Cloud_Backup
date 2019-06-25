#include "MyPage.h"
#include <iostream>
using std::cout;
using std::endl;


namespace wd
{

void MyPage::parse(const string & web)
{

    int idx= 0 ;
    int len =(int)web.size();
    while(idx<len)
    {
        if(web.substr(idx,7)=="<docid>")
        {
            string res =  getSubStr(web,idx,"<docid>","</docid>");
            _docid = stoi(res);
        }
        else if(web.substr(idx,7)=="<title>")
        {
            _title = getSubStr(web,idx,"<title>","</title>");
        }
        else if(web.substr(idx,6)=="<link>")
        {
            _link = getSubStr(web,idx,"<link>","</link>");
        }
        else if(web.substr(idx,13)=="<description>")
        {
            _description = getSubStr(web,idx,"<description>","</description>");
        }
        else if(web.substr(idx,9)=="<content>")
        {
            _content = getSubStr(web,idx,"<content>","</content>");
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

