#include "heap_sort.h"
#include <iostream>
using namespace std;



int main()
{
    vector<int> arr={1,3,5,9,74,2,5,4,77,66,8879,4156};
    HeapSort<int> heap(arr);
    heap.heapSort();
    heap.print() ;
    
    vector<char> arr1={'q','d','h','a','w','j'};
    HeapSort<char> heap1(arr1);
    heap1.heapSort();
    heap1.print();
    return 0;
}

