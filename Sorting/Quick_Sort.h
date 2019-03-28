#ifndef Quick_Sort
#define Quick_Sort

#include "myTools.h"
#include <time.h>

using namespace toolBox;

typedef int (*partitionFunction)(std::vector<int>&, int, int);

void quickSort(std::vector<int>& v, int p, int r, toolBox::Order ord, std::unique_ptr<Result>& q);
void quickSortProcedure(std::vector<int>& v, int p, int r, partitionFunction pFunc);
int partAsc(std::vector<int>& v, int p, int r);
int partDesc(std::vector<int>& v, int p, int r);

#endif
