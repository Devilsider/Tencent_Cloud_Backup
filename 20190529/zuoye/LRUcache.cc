#include "LRUcache.h"


int main()
{
    LRUCache *cache = new LRUCache(2);
    int ret;
    cache->put(1, 1);
    cache->print();
    cout<<"----------------" <<endl;
    cache->put(2, 2);
    cache->print();
    cout<<"----------------" <<endl;
    ret=cache->get(1);       // returns 1
    cout<<" ret = "<<ret<<endl;
    cache->print();
    cout<<"----------------" <<endl;
    cache->put(3, 3);    // evicts key 2
    cache->print();
    cout<<"----------------" <<endl;
    ret=cache->get(2);       // returns -1 (not found)
    cout<<" ret = "<<ret<<endl;
    cache->print();
    cout<<"----------------" <<endl;
    cache->put(4, 4);    // evicts key 1
    cache->print();
    cout<<"----------------" <<endl;
    ret=cache->get(1);       // returns -1 (not found)
    cout<<" ret = "<<ret<<endl;
    cache->print();
    cout<<"----------------" <<endl;
    ret=cache->get(3);       // returns 3
    cout<<" ret = "<<ret<<endl;
    cache->print();
    cout<<"----------------" <<endl;
    ret=cache->get(4);       // returns 4
    cout<<" ret = "<<ret<<endl;
    cache->print();
    cout<<"----------------" <<endl;
    return 0;
}

