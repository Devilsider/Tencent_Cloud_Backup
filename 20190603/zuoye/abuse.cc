#include <iostream>
#include <memory>
using namespace std;

class Point
:public enable_shared_from_this<Point>
{
    public
}
int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

