#pragma once
namespace wd
{

class Socket
{
public:
    Socket() ;
    Socket(int) ;
    void shutdownWrite();
    int fd();
    ~Socket();

private:
    int _fd;
};

}//end of namespace wd
