#include "MinEditDistance.h"
#include <iostream>


int main()
{
    wd::MinEditDistance minEdit; 

    string s1("ace");
    string s2("abcdef");

    int ret= minEdit.editDistance(s1,s2);

    cout<<" "<<ret<<endl;
    return 0;
}

