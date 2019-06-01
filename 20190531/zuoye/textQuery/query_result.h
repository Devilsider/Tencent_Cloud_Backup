#ifndef __QUERYRESULT_H__
#define __QUERYRESULT_H__

#include "text_query.h"
#include <iostream>
#include <memory>
#include <set>
#include <vector>
#include <string>
using namespace std;

class QueryResult
{
friend ostream& print(ostream&,const QueryResult&);
friend ostream& print(ostream&,const QueryResult&,size_t,size_t);
public:
    QueryResult(string s,
                shared_ptr<set<TextQuery::line_no>> l,
                shared_ptr<vector<string>> f
                )
    :sought(s),lines(l),file(f)
    {}

    set<TextQuery::line_no>::iterator begin(){
        return lines->begin();
    }
    set<TextQuery::line_no>::iterator end(){
        return lines->end();
    }
    shared_ptr<vector<string>> get_file(){
        return file;
    }

    
    
private:
    string sought;
    shared_ptr<set<TextQuery::line_no>> lines;
    shared_ptr<vector<string>> file;
    TextQuery::line_no line_no()const{
        return lines->size();
    }
};

ostream &print(ostream&,const QueryResult&);
ostream &print(ostream&,const QueryResult&,size_t,size_t);

#endif
