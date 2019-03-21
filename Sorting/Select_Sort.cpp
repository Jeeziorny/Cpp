#include "Select_Sort.h"

int sel_sort_comparison_counter = 0;
int sel_sort_key_swap_counter = 0;

void selectSort(std::vector<int>& v, Order order)
{
    clock_t t = clock();
    int i = 0;
    std::cerr << "SEL_SORT>sort Order == ascending?\n";
    sel_sort_comparison_counter++;
    if (order != ASC) {
        for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++, ++i) {
            int indexOfMax = maxIndex(v, i);
            toolBox::substitute(*it, v[indexOfMax]); //O(1)
            std::cerr << "SEL_SORT>Swap: " << *it << " <-> " << v[indexOfMax] << std::endl;
            sel_sort_key_swap_counter++;
            std::cerr << "SEL_SORT>Checking if " << *it << " is last element\n";
            sel_sort_comparison_counter++;
        }
    } else {
        for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++, ++i) {
            int indexOfMin = minIndex(v, i);
            toolBox::substitute(*it, v[indexOfMin]); //O(1)
            std::cerr << "SEL_SORT>Swap: " << *it << " <-> " << v[indexOfMin] << std::endl;
            sel_sort_key_swap_counter++;
            std::cerr << "SEL_SORT>Checking if " << *it << " is last element\n";
            sel_sort_comparison_counter++;
        }
    }
    t = clock() - t;
    double time_taken = ((double) t)/CLOCKS_PER_SEC;
    std::cerr << "Time: " << time_taken << " sec" << std::endl;
    std::cerr << "Swap counter: " << sel_sort_key_swap_counter << std::endl;
    std::cerr << "Comparisons counter: " << sel_sort_comparison_counter << std::endl;
    //reset counters
    sel_sort_comparison_counter = sel_sort_key_swap_counter = 0;
}

int minIndex(std::vector<int>& v, int startPos)
{
    std::cerr << "SEL_SORT>MIN>Searching for min in vector\n";
    int result = startPos++;
    for (std::vector<int>::iterator it = v.begin() + startPos; it != v.end(); ++it) {
        std::cerr << "SEL_SORT>MIN> " << v.at(result) << " > " << *it << " ?\n";
        sel_sort_comparison_counter++;
        if (v.at(result) > *it) {
            result = std::distance(v.begin(), it); //O(1) for random access iterators (supported in std::vector);
        }
        std::cerr << "SEL_SORT>MIN>Checking if " << *it << " is last element\n";
        sel_sort_comparison_counter++;
    }
    return result;
}

int maxIndex(std::vector<int>& v, int startPos)
{
    std::cerr << "SEL_SORT>MAX>Searching for max in vector\n";
    int result = startPos++;
    for (std::vector<int>::iterator it = v.begin() + startPos; it != v.end(); ++it) {
        std::cerr << "SEL_SORT>MAX> " << v.at(result) << " < " << *it << " ?\n";
        sel_sort_comparison_counter++;
        if (v.at(result) < *it) {
            result = std::distance(v.begin(), it); //O(1) for random access iterators (supported in std::vector);
        }
        std::cerr << "SEL_SORT>MAX>Checking if " << *it << " is last element\n";
        sel_sort_comparison_counter++;
    }
    return result;
}
