#ifndef __QUERY_H__
#define __QUERY_H__
#include "query_result.h"
#include "query_base.h"
#include "word_query.h"

#include <ostream>
#include <string>
#include <memory>
using namespace std;

class TextQuery;

class Query
{
public:
    friend Query operator~(const Query &);
    friend Query operator|(const Query &,const Query&);
    friend Query operator&(const Query &,const Query&);

    Query(const string &); 
    QueryResult eval(const TextQuery& t)const {
        return q->eval(t);
    }
    string rep()const {
        return q->rep();
    }
private:
    Query(shared_ptr<Query_base> query)
    :q(query)
    {}
    shared_ptr<Query_base> q;

};

ostream &operator<<(ostream &os,const Query &query);
inline Query::Query(const string &s)
:q(new WordQuer(s))
{}

#endif
