#include "SpellcorrectServer.h"
#include "MyTask.h"

#include <iostream>
using std::bind;
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
    cout<<" msg = "<<msg<<endl;
    //业务逻辑交给子线程
    //decode,解封装
    //compute,提取出待查询单词
    //encode，封装好查到的信息
    MyTask mytask(msg,conn);

    _threadPool.addTask(std::bind(&MyTask::process,mytask));
}

void SpellcorrectServer::onClose(const TcpConnectionPtr &conn)
{
    cout<<"onClose..."<<endl;
    cout<<conn->toString()<<" has closed !"<<endl;
    
}

void SpellcorrectServer::start()
{
    _threadPool.start();

    //绑定回调函数，调用类实例的成员函数，即spellcorrectserver的成员函数
    using namespace placeholders;
    _tcpServer.setConnectionCallback(
                        bind(&SpellcorrectServer::onConnection,this,_1));
    _tcpServer.setMessageCallback(
                        bind(&SpellcorrectServer::onMessage,this,_1));
    _tcpServer.setCloseCallback(
                        bind(&SpellcorrectServer::onClose,this,_1));

    _tcpServer.start();
}

}//end of namespace wd


