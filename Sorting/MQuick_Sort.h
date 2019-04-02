#ifndef MQuick_Sort
#define MQuick_Sort

#include "myTools.h"
#include "Insert_Sort.h"


typedef int (*partitionFunction)(std::vector<int>&, int, int);

void mQuickSort(std::vector<int>& v, int p, int r, toolBox::Order ord,
                 std::unique_ptr<Result>& q);
void mQuickAsc(std::vector<int>& v, int p, int r);
int partAscQ(std::vector<int>& v, int p, int r);
void mQuickDesc(std::vector<int>& v, int p, int r);
int partDescQ(std::vector<int>& v, int p, int r);
int& median(int& a, int& b, int& c);

#endif
