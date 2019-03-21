#include "myTools.h"

namespace toolBox
{
    void printArr(std::vector<int> v) {
        for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
            std::cout << " " << *it;
        }
        std::cout << std::endl;
    }

    void fillMe(std::vector<int>& v, int c) {
        for (int i = 0; i < c; i++) {
            v.push_back(std::rand()%100);
        }
    }

    void substitute(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

}

