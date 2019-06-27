#include "MyPage.h"
#include "Jieba.hpp"

#include <iostream>
using std::cout;
using std::endl;
using std::vector;

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

void MyPage::createWordFreMap()
{
    //分词
    cppjieba::Jieba jieba("./dict/jieba.dict.utf8","./dict/hmm_model.utf8","./dict/user.dict.utf8");
    vector<string> wordsTitle;
    vector<string> wordsDes;
    vector<string> wordsContent;
    jieba.Cut(_title,wordsTitle,true);
    jieba.Cut(_description,wordsDes,true);
    jieba.Cut(_content,wordsContent,true);
    
    for(auto &i:wordsTitle){
        auto iter = _wordFreMap.find(i);
        if(iter==_wordFreMap.end()){
            //没有找到
            _wordFreMap.insert(std::make_pair(i,1));
        }else {
            //找到了
            ++_wordFreMap[i];
        }
    }
    for(auto &i:wordsDes){
        auto iter = _wordFreMap.find(i);
        if(iter==_wordFreMap.end()){
            //没有找到
            _wordFreMap.insert(std::make_pair(i,1));
        }else {
            //找到了
            ++_wordFreMap[i];
        }
    }
    for(auto &i:wordsContent){
        auto iter = _wordFreMap.find(i);
        if(iter==_wordFreMap.end()){
            //没有找到
            _wordFreMap.insert(std::make_pair(i,1));
        }else {
            //找到了
            ++_wordFreMap[i];
        }
    }
}

}//end of namespace 

