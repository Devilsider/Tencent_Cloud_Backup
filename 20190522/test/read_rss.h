 #ifndef __READ_RSS_H__
  #define __READ_RSS_H__
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
  using std::cout;
  using std::endl;
  using std::string;
  using std::vector;
  using namespace tinyxml2;
  typedef struct {
      string title;
      string link;
      string description;
      string content;//文件名字，内容存到文件中去
  }RssItem;
 
  class RssReader
  {
  public:
      RssReader(){}
      void parseRss(const string &filename);
      void dump(const string &filename);
      ~RssReader(){
 
      }
 
  private:
      vector<RssItem> _rss;
  };
 
  #endif

