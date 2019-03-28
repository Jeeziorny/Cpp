#include "MQuick_Sort.h"

unsigned long int mq_sort_comparison_counter = 0;
unsigned long int mq_sort_key_swap_counter = 0;

void mQuickSort(std::vector<int>& v, int p, int r, toolBox::Order ord, std::unique_ptr<Result>& w)
{
    clock_t t = clock();
    if (ord == toolBox::ASC)
        mQuickSortProcedure(v, p, r, &mPartAsc);
    else
        mQuickSortProcedure(v, p, r, &mPartDesc);
    insertSort(v, ord, w);
    t = clock() - t;
    double time_taken = ((double) t);

    w -> type = toolBox::MQUICK;
    w -> comparisons += mq_sort_comparison_counter;
    w -> swaps += mq_sort_key_swap_counter;
    w -> time = time_taken;

    mq_sort_comparison_counter = mq_sort_key_swap_counter = 0;
}


void mQuickSortProcedure(std::vector<int>& v, int p, int r, partitionFunction pFunc)
{
    //std::cerr << "QUICK_SORT> p < r: " << p << " < " << r << std::endl;
    mq_sort_comparison_counter++;
    if (p  + 16 < r) {
        int q = pFunc(v, p, r);
        //std::cerr << "QUICK_SORT> quick for [p, q) : " << p << ", " << q - 1 << std::endl;
        mQuickSortProcedure(v, p, q-1, pFunc);
        //std::cerr << "QUICK_SORT> quick for [q+1, r]: " << q + 1 << ", " << r << std::endl;
        mQuickSortProcedure(v, q+1, r, pFunc);
    }
}

int mPartDesc(std::vector<int>& v, int p, int r)
{
    int x = median(v[p], v[r/2], v[r]);
    int i = p - 1;
    for (int j = p; j < r; j++) {
        mq_sort_comparison_counter++;
        //std::cerr << "QUICK_SORT>PARTdesc> j < r : " << j << " < " << r << std::endl;
        mq_sort_comparison_counter++;
        //std::cerr << "QUICK_SORT>PARTdesc> v[j] >= pivot " << v[j] << " >= " << x << std::endl;
        if (v[j] >= x) {
            //std::cerr << "QUICK_SORT>PARTdesc>ANS> true => swap " << std::endl;
            mq_sort_key_swap_counter++;
            toolBox::substitute(v[++i], v[j]);
        }
    }
    //std::cerr << "QUICK_SORT>PARTdesc> pivot swap " << std::endl;
    mq_sort_key_swap_counter++;
    toolBox::substitute(v[i+1], v[r]);
    return i+1;
}

int mPartAsc(std::vector<int>& v, int p, int r)
{
    int x = median(v[p], v[r/2], v[r]);
    int i = p - 1;
    for (int j = p; j < r; j++) {
        mq_sort_comparison_counter++;
        //std::cerr << "QUICK_SORT>PARTasc> j < r : " << j << " < " << r << std::endl;
        mq_sort_comparison_counter++;
        //std::cerr << "QUICK_SORT>PARTasc> v[j] <= pivot " << v[j] << " <= " << x << std::endl;
        if (v[j] <= x) {
            //std::cerr << "QUICK_SORT>PARTasc>ANS> true => swap " << std::endl;
            mq_sort_key_swap_counter++;
            toolBox::substitute(v[++i], v[j]);
        }
    }
    //std::cerr << "QUICK_SORT>PARTasc> pivot swap " << std::endl;
    mq_sort_key_swap_counter++;
    toolBox::substitute(v[i+1], v[r]);
    return i+1;
}

int median(int a, int b, int c)
{
    mq_sort_comparison_counter++;
    if (a <= b && b <= c)
        return b;
    mq_sort_comparison_counter++;
    if (b <= c && c <= a)
        return c;
    return a;
}
