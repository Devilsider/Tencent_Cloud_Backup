#ifndef __QUERY_BASE_H__
#define __QUERY_BASE_H__
#include "text_query.h"
#include <string>
using namespace std;

class Query_base
{
    friend class Query;
protected:
    using line_no=TextQuery::line_no;

    virtual ~Query_base()=default;

private:
    virtual QueryResult eval(const TextQuery&)const =0;
    virtual string rep()const =0;
};

#endif
