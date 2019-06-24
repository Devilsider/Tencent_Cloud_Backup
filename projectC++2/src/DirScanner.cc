#include "DirScanner.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#include <iostream>
using std::cout;
using std::endl;

namespace  wd
{

DirScanner::DirScanner(const string &filepath)
:_filepath(filepath)
{}

void DirScanner::operator()(const string &filepath)
{
    traverse(filepath);
}

void DirScanner::traverse(const string &filepath)
{
    _filepath = filepath;
    struct dirent *pDirInfo;
    DIR *pdir = opendir(_filepath.c_str());

    if(pdir==NULL)
    {
        cout<<"语料库打开错误！"<<endl;
    }

    while((pDirInfo = readdir(pdir))!=NULL)
    {
        if(strcmp(pDirInfo->d_name,".")==0||strcmp(pDirInfo->d_name,"..")==0)
        {
            continue;
        }
        if(pDirInfo->d_type!='d')
        {
            string tmp(_filepath);
            tmp.append(pDirInfo->d_name);
            _vecFilesfiles.push_back(tmp);
        }
    }
}

void DirScanner::showVecFiles()
{
    cout<<"-----------语料库文件绝对路径-------------"<<endl;
    for(auto &i:_vecFilesfiles)
    {
        cout<<i<<endl;
    }
    cout<<"------------------------------------------"<<endl;
}

}//end of wd

