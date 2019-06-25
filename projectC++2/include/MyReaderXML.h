#pragma once
#include "tinyxml2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#include <regex>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace tinyxml2;

namespace wd
{
typedef struct 
{
    string title;
    string link;
    string description;
    string content;
}RssItem;

class MyReaderXML
{
public:
    void parseRss(const string &filename);
    void parseDoc(const string &filename);
    void dump(const string &filename);

    vector<string> & getVecFilesfile()
    {
        //获得vector
        return _vecFilesfile;
    }
private:
    vector<RssItem> _rss;
    vector<string> _vecFilesfile;//存储字符串化后的网页
};

}//end of namespace
