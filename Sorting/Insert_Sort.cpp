#include "Insert_Sort.h"

unsigned long int ins_sort_comparison_counter = 0;
unsigned long int ins_sort_key_swap_counter = 0;

void insertSort(std::vector<int>& v, Order order, std::unique_ptr<Result>& r)
{
    clock_t t = clock();
    int key, bound, j;
    bound = v.size();
    //std::cerr << "INS_SORT>sort Order == ascending?\n";
    ins_sort_comparison_counter++;
    if (order == ASC) {
        for (int i = 1; i < bound; i++) {
            //std::cerr << "INS_SORT> " << i << " < " << bound << "?\n";
            ins_sort_comparison_counter++;
            key = v[i];
            for (j = i - 1; j >= 0 && v[j] > key; j--) {
                //std::cerr << "j: " << j << " >= 0 && v[j]: " << v[j]  << " > key: " << key << " ?\n";
                ins_sort_comparison_counter += 2;
                //std::cerr << "INS_SORT>SHIFT> v[" << j+1 << "] <- v[" << j << "]\n";
                v[j+1] = v[j];
                ins_sort_key_swap_counter++;
            }
            v[j+1] = key;
            ins_sort_key_swap_counter++;
        }
    } else {
        for (int i = 1; i < bound; i++) {
            //std::cerr << "INS_SORT> " << i << " < " << bound << "?\n";
            ins_sort_comparison_counter++;
            key = v[i];
            for (j = i - 1; j >= 0 && v[j] < key; j--) {
                //std::cerr << "j: " << j << " >= 0 && v[j]: " << v[j]  << " < key: " << key << " ?\n";
                ins_sort_comparison_counter += 2;
                //std::cerr << "INS_SORT>SHIFT> v[" << j+1 << "] <- v[" << j << "]\n";
                v[j+1] = v[j];
                ins_sort_key_swap_counter++;
            }
            v[j+1] = key;
            ins_sort_key_swap_counter++;
        }
    }
    t = clock() - t;
    double time_taken = ((double) t);

    r -> type = toolBox::INSERT;
    r -> comparisons = ins_sort_comparison_counter;
    r -> swaps = ins_sort_key_swap_counter;
    r -> time = time_taken;

    //std::cerr << "Time: " << time_taken << " sec" << std::endl;
    //std::cerr << "Swap counter: " << ins_sort_key_swap_counter << std::endl;
    //std::cerr << "Comparisons counter: " << ins_sort_comparison_counter << std::endl;
    //reset counters
    ins_sort_comparison_counter = ins_sort_key_swap_counter = 0;
}
