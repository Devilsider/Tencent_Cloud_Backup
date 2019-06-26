#pragma once
#include "TcpServer.h"
#include "Threadpool.h"
#include <memory>
#include <functional>
using std::shared_ptr;
namespace wd
{

class EcoServer
{
public:
    
    EcoServer(const string &ip,unsigned short port,size_t threadnum
                       ,size_t quesize)
    :_tcpServer(ip,port),
    _threadPool(threadnum,quesize)
    {}

    

    void start();
    void onConnection(const TcpConnectionPtr &conn);
    void onMessage(const TcpConnectionPtr &conn);
    void onClose(const TcpConnectionPtr &conn);


private:
    TcpServer _tcpServer;
    Threadpool _threadPool;
};

}
