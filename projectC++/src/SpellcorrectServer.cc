#include "SpellcorrectServer.h"
#include "MyTask.h"

#include <iostream>

namespace wd
{

void SpellcorrectServer::onConnection(const TcpConnectionPtr &conn)
{
   cout<<conn->toString() <<" has connected! "<<endl;
   conn->send("welcome to server.");
}


void SpellcorrectServer::onMessage(const TcpConnectionPtr &conn)
{
    cout<<"onMessage..."<<endl;
    string msg = conn->receive();//jason字符串
    //业务逻辑交给子线程
    //decode,解封装
    //compute,提取出待查询单词
    //encode，封装好查到的信息
    MyTask MyTask(msg,conn);

    _threadPool.addTask(std::bind(&MyTask::process,MyTask));
}

void SpellcorrectServer::onClose(const TcpConnectionPtr &conn)
{
    cout<<"onClose..."<<endl;
    cout<<conn->toString()<<" has closed !"<<endl;
    
}

void SpellcorrectServer::start()
{
    
}
}//end of namespace wd


