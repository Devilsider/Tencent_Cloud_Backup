#pragma once
#include "Simhasher.hpp"

#include <string>
#include <vector>
using std::vector;
using std::string;

namespace  wd
{

class MySimhasher
{
public:
   
    MySimhasher(const string &s1,
             const string &s2,
             const string &s3,
             const string &s4);//四个字符串分别是词典路径，s1=jieba.dict.utf8的路径
                                    //s2 = hmm_model.utf8
                                    //s3 =idf.utf8
                                    //s4 = stop_words.utf8; 
    simhash::Simhasher &getMySimhasher()
    {
        return _mySimhasher;
    }
private:
    simhash::Simhasher _mySimhasher;
};

}//end of namespace wd
