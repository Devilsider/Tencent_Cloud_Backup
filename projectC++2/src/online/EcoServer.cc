#include "EcoServer.h"
#include "MyTask.h"

#include <iostream>
using std::bind;
using std::cout;
using std::endl;
namespace wd
{

void EcoServer::onConnection(const TcpConnectionPtr &conn)
{
   cout<<conn->toString() <<" has connected! "<<endl;
}


void EcoServer::onMessage(const TcpConnectionPtr &conn)
{
    cout<<"onMessage..."<<endl;
    string msg = conn->receive();//jason字符串
    printf("msg = %s\n",msg.c_str());
    //业务逻辑交给子线程
    //decode,解封装
    //compute,提取出待查询单词
    //encode，封装好查到的信息
    MyTask mytask(msg,conn);

    _threadPool.addTask(std::bind(&MyTask::process,mytask));
}

void EcoServer::onClose(const TcpConnectionPtr &conn)
{
    cout<<"onClose..."<<endl;
    cout<<conn->toString()<<" has closed !"<<endl;
    
}

void EcoServer::start()
{
    _threadPool.start();

    //绑定回调函数，调用类实例的成员函数，即EcoServer的成员函数
    using namespace std::placeholders;
    _tcpServer.setConnectionCallback(
                        bind(&EcoServer::onConnection,this,_1));
    _tcpServer.setMessageCallback(
                        bind(&EcoServer::onMessage,this,_1));
    _tcpServer.setCloseCallback(
                        bind(&EcoServer::onClose,this,_1));

    _tcpServer.start();
}

}//end of namespace wd


