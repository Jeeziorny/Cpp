#include "Quick_Sort.h"

unsigned long int q_sort_comparison_counter = 0;
unsigned long int q_sort_key_swap_counter = 0;


void quickSort(std::vector<int>& v, int p, int r, toolBox::Order ord, std::unique_ptr<Result>& w)
{
    clock_t t = clock();
    if (ord == toolBox::ASC)
        quickSortProcedure(v, p, r, &partAsc);
    else
        quickSortProcedure(v, p, r, &partDesc);
    t = clock() - t;
    double time_taken = ((double) t);

    w -> type = toolBox::QUICK;
    w -> comparisons = q_sort_comparison_counter;
    w -> swaps = q_sort_key_swap_counter;
    w -> time = time_taken;

    //std::cerr << "Time: " << time_taken << " sec" << std::endl;
    //std::cerr << "Swap counter: " << q_sort_key_swap_counter << std::endl;
    //std::cerr << "Comparisons counter: " << q_sort_comparison_counter << std::endl;
    //reset counters
    q_sort_comparison_counter = q_sort_key_swap_counter = 0;
}

void quickSortProcedure(std::vector<int>& v, int p, int r, partitionFunction pFunc)
{
    //std::cerr << "QUICK_SORT> p < r: " << p << " < " << r << std::endl;
    q_sort_comparison_counter++;
    if (p < r) {
        int q = pFunc(v, p, r);
        //std::cerr << "QUICK_SORT> quick for [p, q) : " << p << ", " << q - 1 << std::endl;
        quickSortProcedure(v, p, q-1, pFunc);
        //std::cerr << "QUICK_SORT> quick for [q+1, r]: " << q + 1 << ", " << r << std::endl;
        quickSortProcedure(v, q+1, r, pFunc);
    }
}

int partAsc(std::vector<int>& v, int p, int r)
{
    int x = v[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        q_sort_comparison_counter++;
        //std::cerr << "QUICK_SORT>PARTasc> j < r : " << j << " < " << r << std::endl;
        q_sort_comparison_counter++;
        //std::cerr << "QUICK_SORT>PARTasc> v[j] <= pivot " << v[j] << " <= " << x << std::endl;
        if (v[j] <= x) {
            //std::cerr << "QUICK_SORT>PARTasc>ANS> true => swap " << std::endl;
            q_sort_key_swap_counter++;
            toolBox::substitute(v[++i], v[j]);
        }
    }
    //std::cerr << "QUICK_SORT>PARTasc> pivot swap " << std::endl;
    q_sort_key_swap_counter++;
    toolBox::substitute(v[i+1], v[r]);
    return i+1;
}

int partDesc(std::vector<int>& v, int p, int r)
{
    int x = v[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        q_sort_comparison_counter++;
        //std::cerr << "QUICK_SORT>PARTdesc> j < r : " << j << " < " << r << std::endl;
        q_sort_comparison_counter++;
        //std::cerr << "QUICK_SORT>PARTdesc> v[j] >= pivot " << v[j] << " >= " << x << std::endl;
        if (v[j] >= x) {
            //std::cerr << "QUICK_SORT>PARTdesc>ANS> true => swap " << std::endl;
            q_sort_key_swap_counter++;
            toolBox::substitute(v[++i], v[j]);
        }
    }
    //std::cerr << "QUICK_SORT>PARTdesc> pivot swap " << std::endl;
    q_sort_key_swap_counter++;
    toolBox::substitute(v[i+1], v[r]);
    return i+1;
}
