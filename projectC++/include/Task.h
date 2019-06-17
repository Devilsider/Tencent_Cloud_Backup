#pragma once
#include "TcpConnection.h"
#include "MyResult.h"

#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include <set>
using std::string;
using std::priority_queue;
using std::vector;
using std::unordered_map;
using std::set;

namespace  wd
{

class Task
{
public:
    Task(const string &msg,
         const TcpConnectionPtr &conn,
         vector<std::pair<string,int>> *dict,
         unordered_map<string,set<int>> *index)
    :_conn(conn),
    _query(msg),
    _pdict(dict),
    _pindex(index)
    {}

    void process();//运行在子线程中，处理单词并将结果放到优先级队列
    //然后将优先级队列中前k个单词作为结果封装成jason文件发回客户端，
    //延迟发送，在IO线程发送
    
    int calcDistance(string &rhs);//计算编辑距离
    int minOfThree(int t1,int t2,int t3);//辅助函数，求三个数中的最小值

private:
    TcpConnectionPtr _conn;//conn->sendLoop(msg);延迟到IO线程传输
    string _query;//带查询的单词'
    priority_queue<MyResult> _que;//待候选词的序列
    vector<std::pair<string,int>> *_pdict;//调用已经处理好的词典
    unordered_map<string,set<int>> *_pindex;//调用建立的索引
};

}
