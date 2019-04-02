#ifndef Select_Sort
#define Select_Sort

#include <iterator>
#include <time.h>
#include "myTools.h"

using namespace toolBox;

void selectSort(std::vector<int>& v, Order order, std::unique_ptr<Result>& r);
int minIndex(std::vector<int>& v, int startPos);
int maxIndex(std::vector<int>& v, int startPos);

#endif
