#include <iostream>
#include "Select_Sort.h"
#include "Insert_Sort.h"
#include "Heap_Sort.h"
#include "myTools.h"

using namespace std;

int main()
{
    srand(time(NULL));
    std::vector<int> v;
    fillMe(v, 100);
    printArr(v);
    heapSort(v, ASC);
    heapSort(v, DESC);
    printArr(v);
    return 0;
}
