#include "word_query.h"
#include <iostream>

int main()
{
    WordQuery wq("china_daily.txt","modifFile");
    wq.textModify();
    wq.read();
    wq.query("hello");
    wq.query("world");
    wq.query("scalar");
    wq.query("home");
    wq.query("The");
    wq.query("the");
    return 0;
}


