#include "bfs2.h"
#include <iostream>

int main()
{
    vector<string> dic={"hog","cog"};


    Solution  bfs;
    int ret=bfs.ladderLength("hog","cog",dic);
    cout<<" ret = "<<ret<<endl;
    return 0;
}

