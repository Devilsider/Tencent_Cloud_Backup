#include "TcpServer.h"
#include <iostream>

namespace wd
{
TcpServer::TcpServer(const string &ip,unsigned short port)
:_acceptor(ip,port),
    _loop(_acceptor)
{}

void TcpServer::start()
{
    _acceptor.ready();
    _loop.loop();
}


void TcpServer::setConnectionCallback(const TcpConnectionCallback &&cb)
{
    _loop.setConnectionCallback(std::move(cb));
}
void TcpServer::setMessageCallback(const TcpConnectionCallback &&cb)
{
    _loop.setMessageCallback(std::move(cb));
}
void TcpServer::setCloseCallback(const TcpConnectionCallback &&cb)
{
    _loop.setCloseCallback(std::move(cb));
}

}
