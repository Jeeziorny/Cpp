#include "Select_Sort.h"

unsigned long int sel_sort_comparison_counter = 0;
unsigned long int sel_sort_key_swap_counter = 0;

void selectSort(std::vector<int>& v, Order order, std::unique_ptr<Result>& r)
{
    int j, min_idx, max_idx;
    int temp;
    clock_t t = clock();
    //std::cerr << "SEL_SORT>sort Order == ascending?\n";
    sel_sort_comparison_counter++;
    int SIZE = v.size();
    if (order == toolBox::DESC) {
        for (int i = 0; i < SIZE; i++) {
            max_idx = i;
            for (j = i+1; j < SIZE; j++) {
                if (v[j] > v[max_idx])
                    max_idx = j;
                sel_sort_comparison_counter += 2;
            }
            temp = v[max_idx];
            v[max_idx] = v[i];
            v[i] = temp;
            //std::cerr << "SEL_SORT>Swap: " << *it << " <-> " << v[indexOfMax] << std::endl;
            sel_sort_key_swap_counter++;
            //std::cerr << "SEL_SORT>Checking if " << *it << " is last element\n";
            sel_sort_comparison_counter++;
        }
    } else {
        for (int i = 0; i < SIZE; i++) {
            min_idx = i;
            for (j = i+1; j < SIZE; j++) {
                if (v[j] < v[min_idx])
                    min_idx = j;
                sel_sort_comparison_counter += 2;
            }
            temp = v[min_idx];
            v[min_idx] = v[i];
            v[i] = temp;
            //std::cerr << "SEL_SORT>Swap: " << *it << " <-> " << v[indexOfMin] << std::endl;
            sel_sort_key_swap_counter++;
            //std::cerr << "SEL_SORT>Checking if " << *it << " is last element\n";
            sel_sort_comparison_counter++;
        }
    }
    t = clock() - t;
    double time_taken = ((double) t);

    r -> type = toolBox::SELECT;
    r -> comparisons = sel_sort_comparison_counter;
    r -> swaps = sel_sort_key_swap_counter;
    r -> time = time_taken;

    //std::cerr << "Time: " << time_taken << " sec" << std::endl;
    //std::cerr << "Swap counter: " << sel_sort_key_swap_counter << std::endl;
    //std::cerr << "Comparisons counter: " << sel_sort_comparison_counter << std::endl;
    //reset counters
    sel_sort_comparison_counter = sel_sort_key_swap_counter = 0;
}
