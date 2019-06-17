#pragma once
#include "TcpServer.h"
#include "Threadpool.h"
#include "IndexProducer.h"
#include <memory>
#include <functional>
using std::shared_ptr;
namespace wd
{

class SpellcorrectServer
{
public:
    using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
    using TcpConnectionCallback = std::function<void(const TcpConnectionPtr&)>;
    using Functor = std::function<void()>;
    
    SpellcorrectServer()
    :_tcpServer("172.16.0.15",8888),
    _threadPool(4,10),
    _indexProducer("/home/ubuntu/projectC++/data/Dictionary")
    {}

    void start();
    void onConnection(const TcpConnectionPtr &conn);
    void onMessage(const TcpConnectionPtr &conn);
    void onClose(const TcpConnectionPtr &conn);


private:
    TcpServer _tcpServer;
    Threadpool _threadPool;
    IndexProducer _indexProducer;
};

}
