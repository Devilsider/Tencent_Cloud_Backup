#pragma once
namespace wd
{

class Socket
{
public:
    Socket() ;
    explicit
    Socket(int fd) ;

    void shutdownWrite();
    
    int fd() const;
    
    ~Socket();

private:
    int _fd;
};

}//end of namespace wd
