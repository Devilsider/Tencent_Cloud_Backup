#ifndef __WORD_QUERY_H__
#define __WORD_QUERY_H__
#include "query_base.h"
#include "query_result.h"
#include "text_query.h"
#include <string>
using namespace std;

class WordQuery:public Query_base
{
public:
    friend class Query;
    WordQuery(const string &s)
    :query_word(s) 
    {}
    QueryResult eval(const TextQuery &t)const
    {return t.query(query_word);}
    string rep()const {return query_word;};

private:
    string query_word;
};

#endif
