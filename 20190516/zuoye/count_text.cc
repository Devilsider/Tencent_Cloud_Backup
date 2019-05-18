#include <string.h>
#include <map>
#include<string>
#include<fstream>
#include <iostream>
using std::map;
using std::cout;
using std::endl;
using std::string;
using std::fstream;
using std::ios;
using std::ifstream;
using std::ofstream;
class Dictionary{
public:
    Dictionary(char *filename,char *countResName,char *countWord)
    :_filename(new char[strlen(filename)+1]()),
    _countResName(new char[strlen(countResName)+1]())
     ,_countWord(new char[strlen(countWord)+1]())
    {
        strcpy(_filename,filename);
        strcpy(_countResName,countResName);
        strcpy(_countWord,countWord);
    }
    ~Dictionary(){
        if(_filename){
            delete []_filename;
        }
        if(_countResName){
            delete []_countResName;
        }
        if(_countWord){
            delete []_countWord;
        }
    }
    void textModify(){
       //大写变小写，标点符号变成空格 
        ifstream ifs(_filename);
        ofstream ofs(_countResName,ios::app);
        if(!ifs.is_open()){
            cout<<"open file "<<_filename<<" error"<<endl;
            return ;
        }
        string text;
        while(getline(ifs,text)){
            /* cout<<"1---text is "<<text<<endl; */
            for(auto &c:text){
                if(isupper(c)){
                    c=tolower(c);
                }
                if(ispunct(c)){
                    c=' ';
                }
            }
            /* cout<<"2-----text is "<<text<<endl; */
            ofs<<text<<endl;
        }
        ifs.close();
        ofs.close();
    }
    void read(){
        ifstream ifs(_countResName);
        if(!ifs.is_open()) {
            cout<<"open file "<<_filename<<" error"<<endl;
            return ;
        }
        /* string text; */ 
        string word;
        while(ifs>>word){
        //    cout<<"word ="<<word<<endl;
            ++wordCount[word];
        }
        /* for( auto &i:wordCount){ */
        /*     cout<<i.first<<" is "<<i.second<<"times"<<endl; */
        /* } */
        ifs.close();
    }
    void store(){
        ofstream ofs(_countWord,ios::app);
        if(!ofs.is_open()){
            cout<<"open file "<<_countWord<<" error"<<endl;
            return;
        }
        for(auto &i:wordCount){
            ofs<<i.first<<"  "<<i.second<<endl;
        }
        ofs.close();
    }


    void setFilename(char filename[])
    {
        strcpy(_filename,filename);
    }
    char * getFilename(){
        return _filename;
    }
private:
    char *_filename;
    char *_countResName;
    char *_countWord;
    map<string,int> wordCount;
};
int main()
{
    Dictionary dic("The_Holy_Bible.txt","res","count");
    dic.textModify();
    dic.read();
    dic.store();
    return 0;
}

