#ifndef __WORD_QUERY_H__
#define __WORD_QUERY_H__

#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <fstream>
#include <iostream>
using std::stringstream;
using std::cout;
using std::endl;
using std::unordered_map;
using std::string;
using std::ios;
using std::ifstream;
using std::ofstream;
using std::map;
using std::set;


class WordQuery
{
public:
    WordQuery(const string &filename,const string &modifyFilename) 
    :_filename(filename),_modifyFilename(modifyFilename)
    {}
    void textModify(){
        //区分大小写，去掉文件的标点符号
        ifstream ifs(_filename);
        ofstream ofs(_modifyFilename);
        if(!ifs.is_open()){
            cout<<" open file "<<_filename <<" error "<<endl;
            return ;
        }
        if(!ofs.is_open()){
            cout<<" open file "<<_modifyFilename <<" error "<<endl;
            return ;
        }
        string text;
        while(getline(ifs,text)){
            for(auto &c:text){
                if(ispunct(c)){
                    c=' ';
                }
            }
            ofs<<text<<endl;
        }
        ifs.close();
        ofs.close();
    }

    void read(){
        //将统计结果存储到unordered_map中
        ifstream ifs(_modifyFilename);
        if(!ifs.is_open()){
            cout<<" open file "<<_modifyFilename<<" error "<<endl;
            return ;
        }
        string text;
        string word;
        int line=0;
        while(getline(ifs,text)){
            ++line;
            int i=0,j=0;
            while(i<(int)text.size()){
                while(i<(int)text.size()&&text[i]==' '){
                    ++i;
                }
                j=i;
                while(i<(int)text.size()&&text[i]!=' '){
                    ++i;
                }
                word.clear();
                word=text.substr(j,i-j);
                //cout<<word<<endl;
                if(""==word){
                    continue;
                }
                if(_wordLine.find(word)==_wordLine.end()){
                    //map中不存在该单词
                    set<int> line_set;
                    line_set.insert(line);
                    _wordLine.insert(std::make_pair(word,line_set));
                }
                else{
                    //存在该单词
                    _wordLine.find(word)->second.insert(line);
                }
            }
        }
        /* 测试使用 */
        /* for(auto &c:_wordLine){ */
        /*     cout<<" "<<c.first<<" line is "; */
        /*     for(auto &j:c.second){ */
        /*         cout<<" "<<j; */
        /*     } */
        /*     cout<<endl; */
        /* } */
    }
    void query(string word){
        auto ret=_wordLine.find(word);
        if(ret==_wordLine.end()){
            cout<<" didn't find the word = "<<word<<" ."<<endl;
        }
        else{
            cout<<" "<<word<<" occurs "<<ret->second.size()<<" times."<<endl;
            for(auto &i:ret->second)
            {
                cout<<"     (line "<<i<<") "<<word<<endl;
            }
        }
    }

private:
    string _filename;
    string _modifyFilename;
    unordered_map<string,set<int>> _wordLine;
};

#endif
