#pragma once
#include "TcpConnection.h"
#include "IndexProducer.h"
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
         const TcpConnectionPtr &conn
         );

    void process();//运行在子线程中，处理单词并将结果放到优先级队列
    //然后将优先级队列中前k个单词作为结果封装成jason文件发回客户端，
    //延迟发送，在IO线程发送
    
    int calcDistance(string &rhs);//计算编辑距离
    int minOfThree(int t1,int t2,int t3);//辅助函数，求三个数中的最小值

private:
    string _query;//带查询的单词'
    TcpConnectionPtr _conn;//conn->sendLoop(msg);延迟到IO线程传输
    priority_queue<MyResult> _que;//待候选词的序列
};

}
