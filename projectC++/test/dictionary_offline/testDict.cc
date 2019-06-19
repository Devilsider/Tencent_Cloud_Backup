#include "/home/ubuntu/projectC++/include/IndexProducer.h"
#include "/home/ubuntu/projectC++/include/DictProducer.h"
#include "/home/ubuntu/projectC++/include/SplitTool.h"
#include "/home/ubuntu/projectC++/include/MinEditDistance.h"
#include "/home/ubuntu/projectC++/include/MyResult.h"
#include "/home/ubuntu/projectC++/include/MyDict.h"
#include "Jieba.hpp" 

#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>
#include <json/writer.h>

#include <iostream>
#include <queue>
#include <string>
#include <sstream>
using std::cout;
using std::endl;
using std::string;
using std::priority_queue;
using std::stringstream;
using namespace Json;
using namespace cppjieba;

int main()
{
    string test("/home/ubuntu/projectC++/data");
    wd::DictProducer dic(test);
    dic.build_dict();
    dic.build_cn_dict();
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

    //测试json文件
    Json::Value root;
    Json::Value arroyObj;
    Json::Value item;
    /* //创建一个对象 */
    /* item["_word"] = "nihao"; */
    /* item["_iDist"]=1; */
    /* item["_iFeq"]=10; */
    /* arroyObj["res1"].append(item); */
    /* item["_word"] = "wobuhao"; */
    /* item["_iDist"]=2; */
    /* item["_iFeq"]=5; */
    /* arroyObj["res2"].append(item); */
    /* item["_word"] = "zenmele"; */
    /* item["_iDist"]=4; */
    /* item["_iFeq"]=59; */
    /* arroyObj["res3"].append(item); */

    /* root.append(arroyObj); */

    /* root["strJson"]="jsonTest"; */
    /* root["address"]="sea"; */
    /* arroyObj.append(item);//item对象被作为值放入arrayObj中 */
    /* root["array"]=arroyObj; */
    //将json转换为字符串
    /* root.toStyledString(); */
    /* cout<<root<<endl; */
    //getchar();
    
    /* Json::Value root1; */
    /* Json::Reader reader; */
    /* if(reader.parse(root.toStyledString(),root1)) */
    /* { */
    /*     cout<<root<<endl; */
    /* } */

    


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



