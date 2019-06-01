#include "query_result.h"
#include <iostream>
using namespace std;

ostream &print(ostream &os,const QueryResult &qr){
    os<<"The result of your query ("<<qr.sought<<") occurs "<<qr.line_no()<<" times: \n";
    for(const auto &index:*qr.lines) {
        os<<"\t(line"<<index+1<<")"
            <<*(qr.file->begin()+index)<<endl;
    }
    return os;
}

//head 是输出范围的第一行
//trail 是输出范围的最后一行
ostream & print(ostream &os,const QueryResult &qr,size_t head,size_t trail){
    if(head>trail){
        os<<"illegal range!"<<endl;
        return os;
    }
    else{
        os<<"The result of your query ("<<qr.sought<<") occurs "<<qr.line_no()<<" times: \n";
        for(const auto &index:*qr.lines){
            if(index + 1>=head&&index+1<=trail){
                os<<"\t(line"<<index+1<<")"
                  <<*(qr.file->begin()+index)<<endl;
            }
        }
    }
    return os;
}

