#include "/home/ubuntu/projectC++/include/IndexProducer.h"
#include "/home/ubuntu/projectC++/include/DictProducer.h"
#include "/home/ubuntu/projectC++/include/SplitTool.h"
#include "/home/ubuntu/projectC++/include/MinEditDistance.h"
#include "/home/ubuntu/projectC++/include/MyResult.h"
#include "/home/ubuntu/projectC++/include/MyDict.h"
#include "/home/ubuntu/projectC++/include/Jieba.hpp" 

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
using std::wstring;

int main()
{
    /* string test("/home/ubuntu/projectC++/data"); */
    /* wd::DictProducer dic(test); */
    /* dic.build_dict(); */
    /* dic.build_cn_dict(); */
    /* /1* dic.show_files(); *1/ */
    /* /1* dic.show_dict(); *1/ */
    /* dic.store_dict("/home/ubuntu/projectC++/dict/"); */

    /* wd::IndexProducer index("/home/ubuntu/projectC++/dict/Dictionary"); */
    /* index.init(); */
    /* /1* index.showDict(); *1/ */
    /* /1* index.showIndex(); *1/ */
    /* index.store("/home/ubuntu/projectC++/dict/"); */

    /* wd::MyDict * mydict=wd::MyDict::getInstance(); */
    /* mydict->init("/home/ubuntu/projectC++/dict/"); */
    /* /1* mydict->showDict(); *1/ */
    /* /1* mydict->showIndex(); *1/ */

    cppjieba::Jieba jieba(
        DICT_PATH,
        HMM_PATH,
        USER_DICT_PATH,
        IDF_PATH,
        STOP_WORD_PATH);

    string s("你好世界我不好哈哈哈哈哈哈粉刺疤哈哈");
    vector<string> words;
    jieba.Cut(s,words,true);
    cout<<limonp::Join(words.begin(),words.end(),"/")<<endl;
    
    wstring s1=L"计划完成令计划的计划";
    int len =(int) s1.size();
    for(int idx=0;idx<len;++idx){
        wcout<<s1.substr(0,1)<<endl;
    }


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



