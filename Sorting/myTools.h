#ifndef myTools
#define myTools

#include <vector>
#include <iostream>
#include <cstdlib>
#include <memory>

namespace toolBox
{
    enum Order      {ASC, DESC};
    enum sortType   {INSERT, SELECT, QUICK, HEAP, MQUICK};

    struct Stat {
        int k;
        std::string fileName;
    };

    struct Result {
        sortType type;
        unsigned long int comparisons;
        unsigned long int swaps;
        double time;
    };

    const int randBound = 100000;
    void printArr(std::vector<int> v);
    void fillMe(std::vector<int>& v, int c);
    void substitute(int& a, int& b);
}

#endif

