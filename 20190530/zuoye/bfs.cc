#include "bfs.h"
#include <iostream>

using namespace std;

int main()
{
    vector<string> vs={"a","b","c"};
    BFS bfs(vs) ;
    int ret=bfs.findPath("a","b");
    cout<<"ret ="<<ret<<endl;
    return 0;
}

