#pragma once
#include "SplitTool.h"

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::unordered_map;
using std::vector;
const char * const DICT_PATH = "./dict/jieba.dict.utf8";
const char * const HMM_PATH = "./dict/hmm_model.utf8";
const char * const USER_DICT_PATH = "./dict/user.dict.utf8";
const char * const IDF_PATH = "./dict/idf.utf8";
const char * const STOP_WORD_PATH = "./dict/stop_words.utf8";

namespace wd
{

class DictProducer
{
public:
    DictProducer(const string & dir); //构造函数
    /* DictProducer(const string &dir,SplitTool *splitTool);//构造函数，专为处理中文 ,过后再实现*/
    void build_dict();//创建英文字典
    void build_cn_dict();//创建中文字典 */
    void initChPath();//初始化cppjieba需要使用的词典路径
    void store_dict(const string &);//写入文件
    void show_files()const;//查看文件路径，作为测试用
    void show_dict()const ;//查看英文词典，测试用
private:
    void get_en_files();//获取英文文件的绝对路径
    void get_ch_files();//获取中文文件的绝对路径
    void push_dict(const string & word);//存储某个单词

private:
    string _dir;//语料库文件存放路径
    vector<string> _enFiles;//英文语料库文件的绝对路径
    vector<string> _chFiles;//中文语料库文件
    unordered_map<string ,int > _dict;//配置文件的内容
    SplitTool * _splitTool;
};

}
