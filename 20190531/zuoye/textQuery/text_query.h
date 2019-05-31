#ifndef __TEXT_QUERY_H__
#define __TEXT_QUERY_H__
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

class QueryResult;

class TextQuery
{
public:
    typedef vector<string>::size_type line_no;

    TextQuery(ifstream&);
    QueryResult query(const string &)const;

private:
    shared_ptr<vector<string>> file;
    map<string,shared_ptr<set<line_no>>> wm;//单词和所处行号
    shared_ptr<vector<string>> handlePunct(const string &);

};

#endif
