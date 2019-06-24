#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#include "tinyxml2.h"

#include <regex>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using std::vector;
using std::string;
using std::endl;
using std::cout;
using namespace tinyxml2;

typedef struct{
    string title;
    string link;
    string description;
    string content;//文件名字，内容存到文件中去
}RssItem;


class readRss
{
public:
    readRss() {}
    void parseRss(const string &filename);
    void dump(const string &filename);
    ~readRss() {}

private:
    vector<RssItem> _rss;
};

