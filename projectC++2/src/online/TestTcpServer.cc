 ///
 /// @file    TestAcceptor.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-07 15:42:14
 ///
 
#include "Threadpool.h"
#include "EcoServer.h"
#include "TcpServer.h"
#include "MyLibFile.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <fstream>
#include <memory>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::unique_ptr;

int main(void)
{   
    //在线部分
    wd::MyLibFile *mylibfile=wd::MyLibFile::getInstance();
    mylibfile->read("../../pagelib/webpage.lib","../../pagelib/new_offset.lib","../../pagelib/InvertIndex.lib");
    wd::EcoServer ecoServer("172.16.0.15",8889,4,10);
    ecoServer.start();
    return 0;
}
