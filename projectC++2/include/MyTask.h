#pragma once
#include "TcpConnection.h"
#include "MyTask.h"
#include "MyWebPage.h"
#include "MyNode.h"

#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include <set>
using std::string;
using std::queue;
using std::vector;
using std::unordered_map;
using std::priority_queue;
using std::set;

namespace  wd
{

class MyTask
{
public:
    MyTask(const string &msg,
         const TcpConnectionPtr &conn
         );

    void process();//运行在子线程中，处理单词并将结果放到优先级队列
    //然后将优先级队列中前k个单词作为结果封装成jason文件发回客户端，
    //延迟发送，在IO线程发送
    string encodeJson();//将结果封装成json字符串发送过去
    string decodeJson();//读出结果
    void createQueryWeb(unordered_map<string,set<std::pair<int,double>>>&,vector<std::pair<string,double>>&);//生成查询到的网页
    void initQuery();//初始化查询单词
    double calCos(vector<double>&,vector<double>&);
private:
    string _query;//带查询的输入的字符串
    TcpConnectionPtr _conn;//conn->sendLoop(msg);延迟到IO线程传输
    vector<string> _words;//存储分割后的单词
    queue<MyWebPage> _que; //按序列存储结果网页
    priority_queue<MyNode> _resQue;//存储网页号和cos结果值
};

}
