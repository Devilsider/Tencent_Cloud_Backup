#pragma once
#include <string>
#include <map>
#include <iostream>
#include <fstream>
using std::string;
using std::map;
using std::ifstream;
using std::cout;
using std::endl;

namespace wd
{

class Configuration
{
public:
    Configuration(const string &filepath)
    :_filepath(filepath)
    {}

    void read()
    {
        ifstream ifs(_filepath);//源文件
        if(!ifs.is_open())
        {
            cout<<"open file "<<_filepath<<" error "<<endl;
            return;
        }
        string filename;
        getline(ifs,filename);

        _configMap.insert(std::make_pair(_filepath,filename));
    }

    map<string,string> &getConfigMap()
    {
        return _configMap;
    }
    string getFilepath()const
    {
        return _filepath;
    }
private:
    string _filepath;//配置文件路径
    map<string , string> _configMap;//配置文件内容
};

}
