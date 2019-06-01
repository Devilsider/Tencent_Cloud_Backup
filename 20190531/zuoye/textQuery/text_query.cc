#include "text_query.h"
#include "query_result.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <iostream>
using namespace std;

TextQuery::TextQuery(ifstream &is)
:file(new vector<string>)
{
    string text;
    while(getline(is,text)){
        file->push_back(text);
        int n=file->size()-1;
        istringstream line(text);
        string word;
        while(line>>word){
            auto p=handlePunct(word);//处理标点后可能有好几个单词，存到vector里面
            for(auto w:*p){
                auto &lines=wm[w];
                if(!lines){
                    lines.reset(new set<line_no>);//如果指针为空，重新创建对象
                }
                lines->insert(n);//行号插入进来
            }
        }
    }
}

QueryResult TextQuery::query(const string &sought)const{
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    //从map中获取匹配到的string的迭代器
    auto loc=wm.find(sought);
    if(loc==wm.end()){
        return QueryResult(sought,nodata,file);
    }
    else {
        return QueryResult(sought,loc->second,file);
    }
}

shared_ptr<vector<string>> TextQuery::handlePunct(const string &s){
    shared_ptr<vector<string>> p = make_shared<vector<string>>();
    size_t first=0,index=0;
    while(index!=s.size()){
        if(ispunct(s[index])){
            string word = s.substr(first,index-first);
            if(!word.empty()){
                p->push_back(word);
            }
            //vector 后面插入一个空格
            p->push_back(s.substr(index,1));
            ++index;
            first = index;
        }
        else {
            ++index;
        }
    }
    //将最后一段字符串添加进去(包含空格，不包含标点)
    string trail = s.substr(first);
    if(!trail.empty()){
        p->push_back(trail);
    }
    return p;
}
