#include "Acceptor.h"
#include "TcpConnection.h"
#include "EventLoop.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

//回调函数体现了可扩展性
void onConnection(const wd::TcpConnectionPtr &conn){
    cout<<conn->toString()<<" has connected!"<<endl;
    conn->send("welcome to server.");
}

void onMessage(const wd::TcpConnectionPtr &conn){
    //该回调函数执行时间不宜过长10ms
    cout<<"onMessage..." <<endl;
    string msg=conn->receive();

    cout<<">> receive msg from client: "<<msg<<endl;

    //业务逻辑交给
    //decode
    //compute
    //encode
    conn->send(msg);
}

void onClose(const wd::TcpConnectionPtr &conn){
    cout<<"onClose..."<<endl;
    cout<<conn->toString()<<" has closed ! "<<endl;
}

int main()
{
    wd::Acceptor acceptor("172.16.0.15",8888);
    acceptor.ready();

    wd::EventLoop loop(acceptor);
    loop.setConnectionCallback(onConnection);
    loop.setMessageCallback(onMessage);
    loop.setCloseCallback(onClose);

    return 0;
}

