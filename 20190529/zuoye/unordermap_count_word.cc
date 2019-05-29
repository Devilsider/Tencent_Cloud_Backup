#include <sys/time.h>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::fstream;
using std::ios;
using std::ifstream;
using std::ofstream;
using std::unordered_map;

class Dictionary{
public:
    Dictionary(const string & filename,const string &countResName,const string &countWord)
    :_filename(filename),_countResName(countResName),_countWord(countWord)
    {}
    void textModify(){
        //将文件里面的大写字母变小写，去掉标点符号
        ifstream ifs(_filename);//源文件
        ofstream ofs(_countResName);//修改后文件
        if(!ifs.is_open()){
            cout<<" open file "<<_filename<<" error "<<endl;
            return;
        }
        string text;
        while(getline(ifs,text)){
            for(auto &c:text){
                if(isupper(c)){
                    c=towlower(c);
                }
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
        //从修改后的文件读取内容并且统计
        ifstream ifs(_countResName);
        if(!ifs.is_open()){
            cout<<" opne file "<<_countResName<<" error"<<endl;
            return;
        }
        string word;
        while(ifs>>word){
            //创建对象并且统计
            if(wordCount.find(word)!=wordCount.end()){
            //存在该对象
                ++wordCount.find(word)->second;
            }
            else {
                //不存在插入
                wordCount.insert(std::make_pair(word,1));
            }
        }
        ifs.close();
    }
    void store(){
        //将map中的统计结果输入到文件中去
        ofstream ofs(_countWord);
        if(!ofs.is_open()){
            cout<<" opne file "<<_countWord<<" error"<<endl;
            return ;
        }
        for(auto &i:wordCount){
            ofs<<i.first<<" "<<i.second<<endl;
        }
        ofs.close();
    }
    void setFilename(string filename){
        _filename=filename;
    }
    void setcountResName(string countResName){
        _countResName=countResName;
    }
    void setcountWord(string countWord){
        _countWord=countWord;
    }
    string getFilename(){
        return _filename;
    }
    string getcountResName(){
        return _countResName;
    }
    string getcountWord(){
        return _countWord;
    }
private:
private:
    string _filename;
    string _countResName;
    string _countWord;
    unordered_map<string,int> wordCount;
};

int main()
{
    //timeval 
    clock_t start , end;
    start = clock();
    Dictionary dic("The_Holy_Bible.txt","res","count"); 
    dic.textModify();
    dic.read();
    dic.store();
    end= clock();
    cout<<"use cpu time "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
    return 0;
}

