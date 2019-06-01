#include "query_result.h"
#include "text_query.h"
#include "query.h"
#include "andquery.h"
#include "orquery.h"
#include "notquery.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
    ifstream fin("test.txt");
    TextQuery text(fin);
    auto q= Query("Daddy");
    auto result=q.eval(text);
    print(cout,result);
    cout<<endl;
    /* print(cout,result,-3,5); */
    /* cout<<endl; */
    /* print(cout,result,3,5); */
    /* cout<<endl; */
    /* print(cout,result,3,20); */
    /* cout<<endl; */
    q=~Query("Alice");
    result=q.eval(text);
    print(cout,result);

    q=Query("Alice");
    auto p=Query("hair");
    auto k=Query(q|p);
    result=k.eval(text);
    print(cout,result);


    q=Query("Alice");
    p=Query("hair");
    k=Query(q&p);
    result=k.eval(text);
    print(cout,result);
    return 0;
}

