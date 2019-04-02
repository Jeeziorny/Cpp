#include "MQuick_Sort.h"

unsigned long int mq_sort_comparison_counter = 0;
unsigned long int mq_sort_key_swap_counter = 0;

void mQuickSort(std::vector<int>& v, int p, int r, toolBox::Order ord, std::unique_ptr<Result>& w)
{
    clock_t t = clock();
    //std::cerr << "INS_SORT>sort Order == ascending?\n";
    if (ord == toolBox::ASC)
        mQuickAsc(v, p, r);
    else
        mQuickDesc(v, p, r);
    t = clock() - t;

    double time_taken = ((double) t);

    w -> type = toolBox::MQUICK;
    w -> comparisons = mq_sort_comparison_counter;
    w -> swaps = mq_sort_key_swap_counter;
    w -> time = time_taken;

    mq_sort_comparison_counter = mq_sort_key_swap_counter = 0;
}

void mQuickAsc(std::vector<int>& v, int p, int r)
{
    mq_sort_comparison_counter++;
    if (p < r) {
        int q = partAscQ(v, p, r);
        mq_sort_comparison_counter++;
        if (q != -1) {
            mQuickAsc(v, p, q - 1);
            mQuickAsc(v, q + 1, r);
        } else
            return;
    }
}

int partAscQ(std::vector<int>& v, int p, int r)
{
    mq_sort_comparison_counter++;
    //std::cerr << "decision if quick or insert: " << (((r - p) > 16) ? "quick" : "insert") << std::endl;
    if (r - p > 16) {
        mq_sort_key_swap_counter++;
        //std::cerr << "mquick>partitioning>calculating median" << std::endl;
        toolBox::substitute(median(v[p], v[(r-p)/2 + p], v[r]), v[r]);
        int x = v[r];
        int i = p - 1;
        for (int j = p; j < r; j++) {
            mq_sort_comparison_counter += 2;
            if (v[j] <= x) {
                //std::cerr << "mquick>partitioning>SWAP\n";
                mq_sort_key_swap_counter++;
                toolBox::substitute(v[++i], v[j]);
            }
        }
        mq_sort_key_swap_counter++;
        //std::cerr << "mquick>partitioning>pivot swap\n";
        toolBox::substitute(v[i+1], v[r]);
        return i+1;
    } else {
        int key, j;
        for (int i = p; i <= r; i++) {
            mq_sort_comparison_counter++;
            key = v[i];
            for (j = i - 1; j >= 0 && v[j] > key; j--) {
                //std::cerr << "mquick>partitioning>insert>swapping\n";
                mq_sort_comparison_counter += 2;
                mq_sort_key_swap_counter++;
                v[j+1] = v[j];
            }
            //std::cerr << "mquick>partitioning>insert>swapping last\n";
            mq_sort_key_swap_counter++;
            v[j+1] = key;
        }
    }
    return -1;
}

void mQuickDesc(std::vector<int>& v, int p, int r)
{
    mq_sort_comparison_counter++;
    if (p < r) {
        int q = partDescQ(v, p, r);
        mq_sort_comparison_counter++;
        if (q != -1) {
            mQuickDesc(v, p, q - 1);
            mQuickDesc(v, q + 1, r);
        } else
            return;
    }
}

int partDescQ(std::vector<int>& v, int p, int r)
{
    mq_sort_comparison_counter++;
    //std::cerr << "decision if quick or insert: " << (((r - p) > 16) ? "quick" : "insert") << std::endl;
    if (r - p > 16) {
        mq_sort_key_swap_counter++;
        //std::cerr << "mquick>partitioning>calculating median" << std::endl;
        toolBox::substitute(median(v[p], v[(r-p)/2 + p], v[r]), v[r]);
        int x = v[r];
        int i = p - 1;
        for (int j = p; j < r; j++) {
            mq_sort_comparison_counter += 2;
            if (v[j] >= x) {
                //std::cerr << "mquick>partitioning>SWAP\n";
                mq_sort_key_swap_counter++;
                toolBox::substitute(v[++i], v[j]);
            }
        }
        mq_sort_key_swap_counter++;
        //std::cerr << "mquick>partitioning>pivot swap\n";
        toolBox::substitute(v[i+1], v[r]);
        return i+1;
    } else {
        int key, j;
        for (int i = p; i <= r; i++) {
            mq_sort_comparison_counter++;
            key = v[i];
            for (j = i - 1; j >= 0 && v[j] <key; j--) {
                //std::cerr << "mquick>partitioning>insert>swapping\n";
                mq_sort_comparison_counter += 2;
                mq_sort_key_swap_counter++;
                v[j+1] = v[j];
            }
            //std::cerr << "mquick>partitioning>insert>swapping last\n";
            mq_sort_key_swap_counter++;
            v[j+1] = key;
        }
    }
    return -1;
}

int& median(int& a, int& b, int& c)
{
    mq_sort_comparison_counter++;
    if (a <= b && b <= c)
        return b;
    mq_sort_comparison_counter++;
    if (b <= c && c <= a)
        return c;
    return a;
}
