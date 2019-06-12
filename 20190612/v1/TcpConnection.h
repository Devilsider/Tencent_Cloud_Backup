#pragma once
#include "Socket.h"
#include "InetAddress.h"
#include "SocketIO.h"

namespace wd
{

class TcpConnection
{
public:
    TcpConnection(int fd);
    ~TcpConnection();

    string receive();
    void send(const string &msg);
    
    string toString()const;
    void shutdown();
private:
    InetAddress getLocalAddr(int fd);
    InetAddress getPeerAddr(int fd);
private:
    Socket _sock;
    SocketIO _socketIO;
    InetAddress _localAddr;
    InetAddress _peerAddr;
    bool _isShutdwonWrite;
    
};

}
