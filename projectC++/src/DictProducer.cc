#include "/home/ubuntu/projectC++/include/DictProducer.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#include <fstream>
#include <iostream>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

namespace wd
{

DictProducer::DictProducer(const string &dir)
:_dir(dir)
{
    //将目录下的所有语料库文件读入进来
    string enDir(_dir),chDir(_dir);
    enDir.append("/en");
    chDir.append("/ch");

    struct dirent *pDirInfo;
    DIR *pdir=opendir(enDir.c_str());
    if(pdir==NULL)
    {
        cout<<"语料库目录不存在！打开错误！"<<endl;
    }
    while((pDirInfo=readdir(pdir))!=NULL)
    {
        if(strcmp(pDirInfo->d_name,".")==0||strcmp(pDirInfo->d_name,"..")==0)
        {
            continue;
        }
        if(pDirInfo->d_type!='d')
        {
            _enFiles.push_back((pDirInfo->d_name));
        }
    }
    struct dirent *pDirInfo1;
    DIR *pdir1=opendir(chDir.c_str());
    if(pdir1==NULL)
    {
        cout<<"语料库目录不存在！打开错误！"<<endl;
    }
    while((pDirInfo1=readdir(pdir1))!=NULL)
    {
        if(strcmp(pDirInfo1->d_name,".")==0||strcmp(pDirInfo1->d_name,"..")==0)
        {
            continue;
        }
        if(pDirInfo1->d_type!='d')
        {
            _chFiles.push_back((pDirInfo1->d_name));
        }
    }

}

void DictProducer::build_dict()
{
    get_en_files();
    for(auto &file:_enFiles)
    {
        ifstream ifs(file);
        string temp(file);
        temp.append("_process");
        open(temp.c_str(),O_RDWR|O_CREAT,0666);
        ofstream ofs(temp);//处理后的文件,用完及时删除
        if(!ifs.is_open())
        {
            cout<<" open file "<<file<<" error!"<<endl;
            return;
        }
        string text;
        while(getline(ifs,text))
        {
            for(auto &c:text)
            {
                if(isupper(c))
                {
                    c=tolower(c);
                }
                if(ispunct(c))
                {
                    c=' ';
                }
                if(isdigit(c))
                {
                    c=' ';
                }
            }
            ofs<<text<<endl;
        }
        ifs.close();
        ofs.close();
        
        //从修改后的文件里面读取内容并且统计
        ifstream ifs_process(temp);
        if(!ifs_process.is_open())
        {
            cout<<" open file "<<temp<<" error!"<<endl;
            return;
        }
        string word;
        while(ifs_process>>word)
        {
            //统计
            if(_dict.find(word)==_dict.end()){
                //没有该单词
                _dict.insert(std::make_pair(word,1));
            }
            else
            {
                //存在该单词
                ++_dict.find(word)->second;
            }
        }
        ifs_process.close();
        remove(temp.c_str());
    }
}

void DictProducer::store_dict(const char * filepath)
{
    //将统计好的单词存入磁盘中
    string DictFile(filepath);
    DictFile.append("Dictionary");
    //新建立词典文件 
    open(DictFile.c_str(),O_RDWR|O_CREAT,0666);
    ofstream ofs(DictFile);
    if(!ofs.is_open())
    {
        cout<<" open file "<<DictFile<<" error"<<endl;
        return;
    }
    for(auto &i:_dict)
    {
        ofs<<i.first<<" "<<i.second<<endl;
    }
    ofs.close();
}

void DictProducer::build_cn_dict()
{
    get_ch_files();
    for(auto &file:_chFiles)
    {
        ifstream ifs(file);
        string temp(file);
        temp.append("_process");
        open(temp.c_str(),O_RDWR|O_CREAT,0666);
        ofstream ofs(temp);//处理后的文件,用完及时删除
        if(!ifs.is_open())
        {
            cout<<" open file "<<file<<" error!"<<endl;
            return;
        }
        string text;
        while(getline(ifs,text))
        {
            for(auto &c:text)
            {
                if(ispunct(c))
                {
                    c=' ';
                }
                if(isdigit(c))
                {
                    c=' ';
                }
            }
            ofs<<text<<endl;
        }
        ifs.close();
        ofs.close();
        
        //从修改后的文件里面读取内容并且统计
        ifstream ifs_process(temp);
        if(!ifs_process.is_open())
        {
            cout<<" open file "<<temp<<" error!"<<endl;
            return;
        }
        string word;
        while(ifs_process>>word)
        {
            //统计
            if(_dict.find(word)==_dict.end()){
                //没有该单词
                _dict.insert(std::make_pair(word,1));
            }
            else
            {
                //存在该单词
                ++_dict.find(word)->second;
            }
        }
        ifs_process.close();
        remove(temp.c_str());
    }
}

void DictProducer::show_files()const 
{
    for(auto &i:_enFiles){
        cout<<i<<endl;
    }
}

void DictProducer::show_dict()const
{
    for(auto &i:_dict)
    {
        cout<<"{word:"<<i.first<<","
            <<"frequency:"<<i.second<<"}"<<endl;
    }
}

void DictProducer::get_en_files()
{
    for(auto &i:_enFiles)
    {
        string temp;
        temp.append(_dir).append("/en/").append(i);
        i=temp;
    }
}
void DictProducer::get_ch_files()
{
    for(auto &i:_chFiles)
    {
        string temp;
        temp.append(_dir).append("/ch/").append(i);
        i=temp;
    }
}

void DictProducer::push_dict(const string &word)
{
    //用来干嘛的？
    cout<<"push_dict"<<endl;
}

}//end of  wd
