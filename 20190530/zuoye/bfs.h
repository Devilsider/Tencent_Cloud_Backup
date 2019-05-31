#ifndef __BFS_H__
#define __BFS_H__
#include <string>
#include <utility>
#include <list>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>
#include <deque>
using namespace std;
//构建有单词节点组成的图,通过BFS广度优先遍历遍历图，求出路径

class BFS
{
public:
    BFS(vector<string> wordlist) 
    :_wordList(wordlist)
    {
        for(auto &i:_wordList){
            //初始hashtable
            _wordVisited.insert(make_pair(i,false));
            _wordLevel.insert(make_pair(i,0));
        }
        /* //初始化邻接矩阵,二维矩阵，创建_wordList.size() * _wrodList.size()的矩阵 */
        /* _wordMap.resize(_wordList.size()); */
        /* for(auto i=_wordMap.begin();i!=_wordMap.end();++i){ */
        /*     i->resize(_wordList.size()); */
        /* } */
    }

    bool canTransfer(const string &str1,const string &str2){
        //判断两个字符串是否可以转换,若不相同字母数大于1,则不能
        int count=0;
        if(str1.size()!=str2.size()){
            return false;
        }
        for(size_t idx=0;idx<str1.size();++idx){
            if(count>1) {
                return false;
            }
            if(str1[idx]!=str2[idx]){
                ++count;
                if(count>1) {
                     return false;
                }
            }
        }
        return true;
    }

    void generateMap(){
        //初始化邻接矩阵,二维矩阵，创建_wordList.size() * _wrodList.size()的矩阵
        _wordMap.resize(_wordList.size());
        for(auto i=_wordMap.begin();i!=_wordMap.end();++i){
            i->resize(_wordList.size());
        } 
        //构建矩阵
        size_t i,j;
        for( i=0;i<_wordMap.size();++i){//可优化,变成上三角或者下三角
            for(j=0;j<_wordMap.size();++j){
                if(canTransfer(_wordList[i],_wordList[j])){
                    _wordMap[i][j]=true;
                }
                else{
                    _wordMap[i][j]=false;
                }
            }
        }
    }

    int findPath(string beginword,string endword){
        if(_wordLevel.find(endword)==_wordLevel.end()){
            //单词表中没有该目标单词,返回0
            return 0;
        }
        if(_wordLevel.find(beginword)==_wordLevel.end()){
            //单词表中没有源单词，将源单词加入到表中
            _wordList.push_back(beginword);
            _wordLevel.insert(make_pair(beginword,0));
            _wordVisited.insert(make_pair(beginword,false));
            /* _wordMap.resize(_wordList.size()); */
            /* for(auto i=_wordMap.begin();i!=_wordMap.end();++i){ */
            /*     i->resize(_wordList.size()); */
            /* } */   
        }
        _beginWord=beginword;
        _endWord=endword;
        //第一个节点beginWord如队列，从图中开始访问
        _que.push_back(make_pair(beginword,0));
        _wordVisited.find(beginword)->second=true;

        generateMap();

        pair<string ,int> temp;
        while(!_que.empty()){
            
            cout<<" now is _que"<<endl;
            for(auto &i:_que){
                cout<<"  ("<<i.first<<","<<i.second<<")";
            }
            cout<<endl;
            temp=_que.front();
            _que.pop_front();
            
            if(temp.first==endword){
                return ++temp.second;
            }

            //建立与之可以转换的所有单词链表
            list<string> nextWord;
            auto it=find(_wordList.begin(),_wordList.end(),temp.first);
            auto pos=distance(_wordList.begin(),it);//找到在表中位置
            //和map对应
            for(size_t i=0;i<_wordMap[pos].size();++i){
                if(_wordMap[pos][i]){
                    //为true，加入list中
                    nextWord.push_back(_wordList[i]);
                }
            }
            cout<<endl;
            /* for(auto &i:nextWord){ */
            /*     cout<<" "<<i; */
            /*     cout<<endl; */
            /* } */
            //遍历队列中元素
            for(auto &i:nextWord){
                cout<<" i "<<i<<endl;
                if(!_wordVisited.find(i)->second){
                    //没有被访问
                    string newTemp(i);
                    //插入队列,并在hash表中置为true
                    _que.push_back(make_pair(newTemp,temp.second+1));
                    cout<<"---newTemp=  "<<newTemp<<endl;
                    cout<<"temp = "<<temp.first<<" temp.val= "<<temp.second<<endl;
                    _wordVisited.find(i)->second=true;
                }
            }

        }
        return 0;
    }


private:
    vector<string> _wordList;//存储所有单词
    unordered_map<string,int> _wordLevel;//存储所有单词及其在图中的层级
    string _beginWord;//开始的单词
    string _endWord;//结束的单词
    vector<vector<bool>> _wordMap;//用邻接矩阵存储两个单词之间是否可以相互转换
    unordered_map<string,bool> _wordVisited;//用来存储该单词是否被访问过
    deque<pair<string,int>> _que;//用来存储所有的访问节点，辅助数据结构，遍历邻接矩阵的时候用
};


#endif
