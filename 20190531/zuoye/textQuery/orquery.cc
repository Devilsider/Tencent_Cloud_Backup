#include "orquery.h"
#include "query_result.h"
#include "query.h"
#include "text_query.h"
#include <iostream>

QueryResult OrQuery::eval(const TextQuery &text)const {
    auto right=rhs.eval(text);
    auto left=rhs.eval(text);
    auto ret_lines=make_shared<set<line_no>>(left.begin(),left.end());
    ret_lines->insert(right.begin(),left.end());
    return QueryResult(rep(),ret_lines,left.get_file());
}


