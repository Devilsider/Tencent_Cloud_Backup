#ifndef __BINARYQUERY_H__
#define __BINARYQUERY_H__

#include "query.h"
#include "query_base.h"
#include <string>
using namespace std;

class BinaryQuery:public Query_base
{
protected:
    BinaryQuery(const Query &l,const Query &r,string s) 
    :lhs(l),rhs(r),opSym(s)
    {}
    string rep() const{
        return "("+lhs.rep()+" "+opSym+" "+rhs.rep()+")";
    }
    Query lhs,rhs;
    string opSym;

};

#endif
