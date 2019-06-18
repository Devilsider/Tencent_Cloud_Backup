#include "/home/ubuntu/projectC++/include/IndexProducer.h"
#include "/home/ubuntu/projectC++/include/DictProducer.h"
#include "/home/ubuntu/projectC++/include/SplitTool.h"
#include "/home/ubuntu/projectC++/include/MinEditDistance.h"
#include "/home/ubuntu/projectC++/include/MyResult.h"
#include "/home/ubuntu/projectC++/include/MyDict.h"

#include <iostream>
#include <queue>
#include <string>
#include <sstream>
using std::cout;
using std::endl;
using std::string;
using std::priority_queue;
using std::stringstream;

int main()
{
    string test("/home/ubuntu/projectC++/data");
    wd::DictProducer dic(test);
    dic.build_dict();
    /* dic.show_files(); */
    /* dic.show_dict(); */
    dic.store_dict("/home/ubuntu/projectC++/dict/");

    wd::IndexProducer index("/home/ubuntu/projectC++/dict/Dictionary");
    index.init();
    /* index.showDict(); */
    /* index.showIndex(); */
    index.store("/home/ubuntu/projectC++/dict/");

    wd::MyDict * mydict=wd::MyDict::getInstance();
    mydict->init("/home/ubuntu/projectC++/dict/");
    mydict->showDict();
    mydict->showIndex();
    /* for(auto i:pindex->getDict()) */
    /* { */
    /*     cout<<"word: "<<i.first<<" frequency:  "<<i.second<<endl; */
    /* } */
    /* for(auto i:pindex->getIndex()) */
    /* { */
    /*     cout<<" "<<i.first<<endl; */
    /* } */
    /* string word("hello"); */
    /* priority_queue<wd::MyResult> que; */
    /* wd::MinEditDistance mined; */
    /* auto index=pindex->getIndex(); */
    /* auto dict=pindex->getDict(); */
    /* string tmp; */
    /* stringstream ss; */
    /* for(auto &ch:word) */
    /* { */
    /*     tmp.clear(); */
    /*     tmp=""; */
    /*     ss.clear(); */
    /*     ss.str(""); */
    /*     ss<<ch; */
    /*     tmp=ss.str(); */

    /*     auto indexSet = index[tmp]; */
    /*     for(auto &idx:indexSet) */
    /*     { */
    /*         if(!pindex->getBitMap().test(idx)) */
    /*         { */
    /*             int dist = mined.editDistance(word,dict[idx].first); */
    /*             wd::MyResult *pnode = new wd::MyResult(); */
    /*             pnode->_iDist=dist; */
    /*             pnode->_iFeq=dict[idx].second; */
    /*             pnode->_word=dict[idx].first; */

    /*             que.push(*pnode); */
    /*             pindex->getBitMap().set(idx); */
    /*         } */
    /*     } */

        
    /* } */
    /* while(que.size()!=0) */
    /* { */
    /*     cout<<"{word:"<<que.top()._word */
    /*         <<",dist:"<<que.top()._iDist */
    /*         <<",freq:"<<que.top()._iFeq<<"}"<<endl; */
    /*     que.pop(); */
    /* } */

    
    return 0;
}



