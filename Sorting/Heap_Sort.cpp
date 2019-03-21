#include "Heap_Sort.h"

int heap_sort_comparison_counter = 0;
int heap_sort_key_swap_counter = 0;

void heapSort(std::vector<int>& v, toolBox::Order order)
{
    clock_t t = clock();
    std::cerr << "HEAP_SORT>sort Order == ascending?\n";
    heap_sort_comparison_counter++;
    std::cerr << "HEAP_SORT>building heap...\n";
    if (order == toolBox::ASC) {
        buildMaxHeap(v);
        std::cerr << "HEAP_SORT>BUILDING DONE\n";
        for (int i = v.size() - 1; i > 0; i--) {
            toolBox::substitute(v[i], v[0]);
            std::cerr << "HEAP_SORT> " << v[i] << " swaps with " << v[0] << std::endl;
            heap_sort_key_swap_counter++;
            maxHeapify(v, 0, i);
        }
    } else {
        buildMinHeap(v);
        std::cerr << "HEAP_SORT>BUILDING DONE\n";
        for (int i = v.size() - 1; i > 0; i--) {
            toolBox::substitute(v[i], v[0]);
            std::cerr << "HEAP_SORT> " << v[i] << " swaps with " << v[0] << std::endl;
            heap_sort_key_swap_counter++;
            minHeapify(v, 0, i);
        }
    }
    t = clock() - t;
    double time_taken = ((double) t)/CLOCKS_PER_SEC;

    std::cerr << "Time: " << time_taken << " sec" << std::endl;
    std::cerr << "Swap counter: " << heap_sort_key_swap_counter << std::endl;
    std::cerr << "Comparisons counter: " << heap_sort_comparison_counter << std::endl;
    //reset counters
    heap_sort_comparison_counter = heap_sort_key_swap_counter = 0;
}

void minHeapify(std::vector<int>& v, int i, int heapSize)
{
    int l = left(i);
    int r = right(i);
    int smallest;
    std::cerr << "HEAP_SORT>minHeapify> left < heapSize && a[left] < a[parent]?\n";
    std::cerr << l << " < " << heapSize << " && " << v[l] << " < " << v[i] << std::endl;
    heap_sort_comparison_counter += 2;
    if (l < heapSize && v[l] < v[i])
        smallest = l;
    else
        smallest = i;
    std::cerr << "HEAP_SORT>minHeapify> right < heapSize && a[right] < min(a[parent], a[left])?\n";
    std::cerr << r << " < " << heapSize << " && " << v[r] << " < " << v[smallest] << std::endl;
    heap_sort_comparison_counter += 2;
    if (r < heapSize && v[r] < v[smallest])
        smallest = r;
    std::cerr << "HEAP_SORT>minHeapify> min(a[left], a[right], a[parent]) != a[parent]?\n";
    heap_sort_comparison_counter++;
    if (smallest != i) {
        std::cerr << "HEAP_SORT>minHeapify> ->True";
        std::cerr << "swap...";
        toolBox::substitute(v[i], v[smallest]);
        heap_sort_key_swap_counter++;
        minHeapify(v, smallest, heapSize);
    }
}

void maxHeapify(std::vector<int>& v, int i, int heapSize)
{
    int l = left(i);
    int r = right(i);
    int largest;
    std::cerr << "HEAP_SORT>maxHeapify> left < heapSize && a[left] > a[parent]?\n";
    std::cerr << l << " < " << heapSize << " && " << v[l] << " > " << v[i] << std::endl;
    heap_sort_comparison_counter += 2;
    if (l < heapSize && v[l] > v[i])
        largest = l;
    else
        largest = i;
    std::cerr << "HEAP_SORT>maxHeapify> right < heapSize && a[right] > max(a[parent], a[left])?\n";
    std::cerr << r << " < " << heapSize << " && " << v[r] << " > " << v[largest] << std::endl;
    heap_sort_comparison_counter += 2;
    if (r < heapSize && v[r] > v[largest])
        largest = r;
    std::cerr << "HEAP_SORT>maxHeapify> max(a[left], a[right], a[parent]) != a[parent]?\n";
    heap_sort_comparison_counter++;
    if (largest != i) {
        std::cerr << "HEAP_SORT>maxHeapify> ->True\n";
        std::cerr << "swap...\n";
        toolBox::substitute(v[i], v[largest]);
        heap_sort_key_swap_counter++;
        maxHeapify(v, largest, heapSize);
    }
}

void buildMaxHeap(std::vector<int>& v)
{
    for (int i = v.size()/2-1; i >= 0; i--) {
        maxHeapify(v, i, v.size());
        heap_sort_comparison_counter++;
    }
}

void buildMinHeap(std::vector<int>& v)
{
    for (int i = v.size()/2-1; i >= 0; i--) {
        minHeapify(v, i, v.size());
        heap_sort_comparison_counter++;
    }
}
