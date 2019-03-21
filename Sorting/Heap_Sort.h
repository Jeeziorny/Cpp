#ifndef Heap_Sort
#define Heap_Sort

#include <time.h>
#include "myTools.h"

using namespace toolBox;

inline int parent(int i) { return i/2; }
inline int left(int i) { return 2*i+1; }
inline int right(int i) { return 2*i+2; }

void heapSort(std::vector<int>& v, Order order);
void maxHeapify(std::vector<int>& v, int i, int heapSize);
void buildMaxHeap(std::vector<int>& v);
void minHeapify(std::vector<int>& v, int i, int heapSize);
void buildMinHeap(std::vector<int>& v);

#endif
