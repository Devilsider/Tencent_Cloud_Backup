#pragma once
#include "SplitTool.h"

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::unordered_map;
using std::vector;

namespace wd
{

class DictProducer
{
public:
    DictProducer(const string & dir); //构造函数
    /* DictProducer(const string &dir,SplitTool *splitTool);//构造函数，专为处理中文 ,过后再实现*/
    void build_dict();//创建英文字典
    /* void build_cn_dict();//创建中文字典 待实现，基础功能完成后再实现*/
    void store_dict(const char * filepath);//将词典写入文件
    void show_files()const;//查看文件路径，作为测试用
    void show_dict()const ;//查看词典，测试用
private:
    void get_files();//获取文件的绝对路径
    void push_dict(const string & word);//存储某个单词

private:
    string _dir;//语料库文件存放路径
    vector<string> _files;//语料库文件的绝对路径
    unordered_map<string ,int > _dict;//配置文件的内容
    SplitTool * _splitTool;
};

}
