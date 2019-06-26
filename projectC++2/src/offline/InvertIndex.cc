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
        myPage.createWordFreMap();
        MyWebPage myWebPage(myPage.getDocid(),
                            myPage.getLink(),
                            myPage.getTitle(),
                            myPage.getDescription(),
                            myPage.getContent(),
                            myPage.getWordFreMap());
        
        _allMyWeb.push_back(myWebPage);
        for(auto &i:myWebPage.getWordFreMap())
        {
            auto iter = _wordCount.find(i.first);
            if(iter == _wordCount.end())
            {
                //没找到
                _wordCount.insert(std::make_pair(i.first,1));
            }else {
                //找到该单词
                ++_wordCount[i.first];
            }
        }
    }
    ifsWeb.close();
    ifsNewOffset.close();
}
void InvertIndex::createInvertIndex()
{
//生成倒排索引表
    for(auto iter=_allMyWeb.begin();iter!=_allMyWeb.end();++iter)
    {
        auto unmap = iter->getWordFreMap();
        for(auto iter2 = unmap.begin();iter2!=unmap.end();++iter2)
        {
            auto i = _wordCount.find(iter2->first);
            if(i==_wordCount.end()){
                //没有在文章中出现过,不可能，_wordCount就是根据其建立的
            }else{
                string word = iter2->first;
                int N = (int)_allMyWeb.size();
                double tf = iter2->second;
                double df = i->second;
                double idf = log(N/df);
                int docid = iter->getDocid();
                double weight =  tf*idf;//计算出权重，等下归一化
                //插入倒排索引表
                /* std::cout<<word<<" :N= "<<N<<",tf = "<<tf<<",df= "<<df<<",idf= "<<idf<<",weight="<<weight<<std::endl; */
                auto iter3 = _invertIndex.find(word);
                if(iter3==_invertIndex.end())
                {//没找到
                    set<std::pair<int,double>> docAndWei;
                    docAndWei.insert(std::make_pair(docid,weight));
                    _invertIndex.insert(std::make_pair(word,docAndWei));
                }else{
                    //找到了
                    iter3->second.insert(std::make_pair(docid,weight));
                }
            }
        }
    }
    //unordered_map对所有的权重进行归一化处理
    for(auto iter = _invertIndex.begin();iter!= _invertIndex.end();++iter)
    {
        double M;
        double weight2Sum= 0;
        auto tmpSet = iter->second;
        for(auto iter2 = tmpSet.begin();iter2!=tmpSet.end();++iter2)
        {
            weight2Sum += iter2->second * iter2->second;
        }
        M = sqrt(weight2Sum);
        //归一化
        //更新替换未归一化的set
        set<std::pair<int ,double>> newSet;
        for(auto iter3 = tmpSet.begin();iter3!=tmpSet.end();++iter3)
        {
            double tempWeight;
            int tempDocid;
            tempDocid = iter3->first;
            tempWeight = iter3->second/M;
            newSet.insert(std::make_pair(tempDocid,tempWeight));
        }
        swap(iter->second,newSet);
    }
}
void InvertIndex::store(const string & filepath)
{
    ofstream ofs(filepath,std::ios::app);
    for(auto iter=_invertIndex.begin();iter!=_invertIndex.end();++iter)
    {
        ofs<<iter->first;
        auto tmpSet = iter->second; 
        for(auto iter2 = tmpSet.begin();iter2!=tmpSet.end();++iter2)
        {
            ofs<<" "<<iter2->first<<" "<<iter2->second;
        }
        ofs<<std::endl;
    }
    ofs.close();
}

}//end of namespace;
