#include "InvertIndex.h"
#include "MyPage.h"

#include <iostream>
#include <fstream>
#include <sstream>
using std::ifstream;
using std::ofstream;
using std::stringstream;

namespace wd
{

void InvertIndex::read(const string &webpath,const string &newoffset)
{
    ifstream ifsWeb(webpath);
    ifstream ifsNewOffset(newoffset);

    string line;
    while(getline(ifsNewOffset,line))
    {
        stringstream ss;
        string web;
        char buff[65536];
        int docid,offset,len;
        ss<<line;
        ss>>docid>>offset>>len;
        ifsWeb.seekg(offset,ifsWeb.beg);
        ifsWeb.read(buff,len);
        web = buff;
        MyPage myPage; 
        myPage.parse(web);
        MyWebPage myWebPage(myPage.getDocid(),
                            myPage.getLink(),
                            myPage.getTitle(),
                            myPage.getDescription(),
                            myPage.getContent());
        _allMyWeb.push_back(myWebPage);
    }
    for(auto &i:_allMyWeb)
    {
        printf("%d\n",i.getDocid());
        printf("%s\n",i.getTitle().c_str());
        printf("%s\n",i.getLink().c_str());
        printf("%s\n",i.getDescription().c_str());
        printf("%s\n",i.getContent().c_str());
    }
    ifsWeb.close();
    ifsNewOffset.close();
}

}//end of namespace;
