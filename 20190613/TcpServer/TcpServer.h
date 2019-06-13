#pragma once
#include "Acceptor.h"
#include "EventLoop.h"
#include "TcpConnection.h"

namespace wd
{
using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using TcpConnectionCallback = std::function<void (const TcpConnectionPtr&)>;

class TcpServer
{
public:
    TcpServer(const string &ip,unsigned short port); 

    void start();

    void setConnectionCallback(const TcpConnectionCallback &&cb);
    void setMessageCallback(const TcpConnectionCallback &&cb);
    void setCloseCallback(const TcpConnectionCallback &&cb);
private:
    Acceptor _acceptor;
    EventLoop _loop;
};

}
