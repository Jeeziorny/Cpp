#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Select_Sort.h"
#include "Insert_Sort.h"
#include "Heap_Sort.h"
#include "Quick_Sort.h"
#include "MQuick_Sort.h"
#include "myTools.h"

bool compare(const char *str1, const char *str2);
void fillUs(std::vector<int>& a, std::vector<int>& b, std::vector<int>& c,
            std::vector<int>& d, std::vector<int>& e, int bound);
void launchStatMode(toolBox::Stat& a);
void getSequence(std::vector<int>& v);
bool isSorted(std::vector<int>& v, toolBox::Order ord);
void userService(std::string type, toolBox::Order ord);
void log();

int main(int argc, char * argv[])
{
    srand(time(NULL));
    std::string algorithm = "";
    toolBox::Order ord = toolBox::ASC;
    toolBox::Stat input;

    for (int i = 1; i < argc; i++) {
        if (compare(argv[i], "--type")) {
            algorithm = std::string(argv[++i]);
        } else if (compare(argv[i], "--asc")) {
            ord = toolBox::ASC;
        } else if (compare(argv[i], "--desc")) {
            ord = toolBox::DESC;
        } else if (compare(argv[i], "--stat")) {
            input.k = atoi(argv[++i]);
            input.fileName = std::string(argv[++i]);
            launchStatMode(input);
        } else {
            log();
        }
    }
    userService(algorithm, ord);/*
    std::unique_ptr<toolBox::Result> res =
        std::unique_ptr<toolBox::Result>(new toolBox::Result);
    std::vector<int> v;
    for (int i = 0; i < 40; i++) {
        fillMe(v, 10);
        mQuickSort(v, 0, v.size(), toolBox::ASC, res);
        printArr(v);
        v.clear();
    }*/
    return 0;
}

void userService(std::string type, toolBox::Order ord)
{
    std::vector<int> v;
    std::unique_ptr<toolBox::Result> res =
        std::unique_ptr<toolBox::Result>(new toolBox::Result);
    getSequence(v);
    if (type == std::string("select")) {
        selectSort(v, ord, res);
    } else if (type == std::string("insert")) {
        insertSort(v, ord, res);
    } else if (type == std::string("heap")) {
        heapSort(v, ord, res);
    } else if (type == std::string("mquick")) {
        mQuickSort(v, 0, v.size() - 1, ord, res);
    } else if (type == std::string("quick")) {
        quickSort(v, 0, v.size() - 1, ord, res);
    } else {
        log();
        exit(0);
    }

    std::cout   << "Total comparisons: " << res->comparisons
                << "\nTotal swaps: " << res->swaps
                << "\nTotal time (ms) " << res->time
                << "\nIs sequence sorted? " << isSorted(v, ord)
                << "\nOUT: \n ";
    printArr(v);
}

bool isSorted(std::vector<int>& v, toolBox::Order ord)
{
    if (v.empty() || v.size() == 1)
        return true;
    switch (ord) {
        case toolBox::ASC:
            for (int i = 1; i < v.size(); i++)
                if (v[i-1] > v[i])
                    return false;
            break;
        case toolBox::DESC:
            for (int i = 1; i < v.size(); i++)
                if (v[i-1] < v[i])
                    return false;
            break;
    }
    return true;
}

void getSequence(std::vector<int>& v)
{
    int n, temp;
    std::string line;

    std::cout << "Size: ";
    std::cin >> n;
    std::cin.get();
    std::getline(std::cin, line);
    std::istringstream ss(line);
    for (int i = 0; i < n; i++) {
        ss >> temp;
        v.push_back(temp);
    }
    std::cout << "\nIN:" << std::endl;
    printArr(v);
}


void launchStatMode(toolBox::Stat& a)
{
    std::ofstream myFile;
    myFile.open(a.fileName);

    std::vector<int> vInsert;
    std::vector<int> vSelect;
    std::vector<int> vQuick;
    std::vector<int> vHeap;
    std::vector<int> vMQuick;

    std::unique_ptr<toolBox::Result> rInsert =
        std::unique_ptr<toolBox::Result>(new toolBox::Result);
    std::unique_ptr<toolBox::Result> rSelect =
        std::unique_ptr<toolBox::Result>(new toolBox::Result);
    std::unique_ptr<toolBox::Result> rQuick  =
        std::unique_ptr<toolBox::Result>(new toolBox::Result);
    std::unique_ptr<toolBox::Result> rHeap   =
        std::unique_ptr<toolBox::Result>(new toolBox::Result);
    std::unique_ptr<toolBox::Result> rMQuick   =
        std::unique_ptr<toolBox::Result>(new toolBox::Result);

    for (int i = 0; i < a.k; i++) {
        for (int n = 100; n <= 10000; n += 100) {
            fillUs(vInsert, vSelect, vQuick, vHeap, vMQuick, n);
            heapSort(vHeap, toolBox::ASC, rHeap);
            insertSort(vInsert, toolBox::ASC, rInsert);
            selectSort(vSelect, toolBox::ASC, rSelect);
            quickSort(vQuick, 0, n-1, toolBox::ASC, rQuick);
            mQuickSort(vMQuick, 0, n-1, toolBox::ASC, rMQuick);
            std::cout << "n = " << n << " i = " << i << std::endl;
            myFile << n << ";" << rMQuick->type << ";" << rMQuick->comparisons << ";"
             << rMQuick->swaps << ";" << rMQuick->time << std::endl;
            myFile << n << ";" << rHeap->type << ";" << rHeap->comparisons << ";"
             << rHeap->swaps << ";" << rHeap->time << std::endl;
            myFile << n << ";" << rQuick->type << ";" << rQuick->comparisons << ";"
             << rQuick->swaps << ";" << rQuick->time << std::endl;
            myFile << n << ";" << rSelect->type << ";" << rSelect->comparisons << ";"
             << rSelect->swaps << ";" << rSelect->time << std::endl;
            myFile << n << ";" << rInsert->type << ";" << rInsert->comparisons << ";"
             << rInsert->swaps << ";" << rInsert->time << std::endl;

            vInsert.clear();
            vSelect.clear();
            vQuick.clear();
            vHeap.clear();
            vMQuick.clear();
        }
    }
    myFile.close();
}

void log()
{
    std::cout << "Incorrect parameter. Available parameters:\n";
    std::cout << "--type select|insert|heap|quick\n\tfor select sorting algorithm\n";
    std::cout << "--asc|--desc\n\tfor select sorting order\n";
    std::cout << "--stat k file_name\n\t don't wait for input.\n\tk independent repetitions, file_name for results\n";
}


void fillUs(std::vector<int>& a, std::vector<int>& b, std::vector<int>& c,
            std::vector<int>& d, std::vector<int>& e, int bound)
{
    int elem;
    for (int i = 0; i < bound; i++) {
        elem = rand() % toolBox::randBound - 50000;
        a.push_back(elem);
        b.push_back(elem);
        c.push_back(elem);
        d.push_back(elem);
        e.push_back(elem);
    }
}

bool compare(const char *str1, const char *str2)
{
    while (*str1 == *str2)
    {
        if (*str1 == '\0' && *str2 == '\0')
            return true;
        str1++;
        str2++;
    }
    return false;
}
