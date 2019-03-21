#ifndef myTools
#define myTools

#include <vector>
#include <iostream>
#include <cstdlib>

namespace toolBox
{
    void printArr(std::vector<int> v);
    void fillMe(std::vector<int>& v, int c);
    enum Order {ASC, DESC};
    void substitute(int& a, int& b);
}

#endif

