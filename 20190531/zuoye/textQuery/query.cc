#include "query.h"
#include <iostream>
using namespace std;

ostream & operator<<(ostream&os,const Query &query){
    return os<<query.rep();
}
