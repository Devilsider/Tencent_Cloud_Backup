#pragma once
#include <string>
#include <vector>
using std::vector;
using std::string;

namespace wd
{
class DirScanner
{
public:
    
    DirScanner(const string &filepath);//初始化语料文件夹
   
    void operator ()(const string &filepath);//重载函数运算符
    void traverse(const string &dirname);//获取某一目录下的所有xml网页的所有文件
    vector<string >& getFile()
    {
        return _vecFilesfiles; 
    }
    void showVecFiles();//测试用
private:
    string _filepath;//存放语料文件的文件夹
    vector<string> _vecFilesfiles;//存放每一个语料文件的绝对路径
};

}//end of namespace
