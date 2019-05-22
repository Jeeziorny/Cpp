#include "pch.h"
#include <iostream> 
#include "HyperCube.h"

using namespace std;

int main(void) {
	HyperCube hc = HyperCube(10);
	std::cout << hc.edmondsKarp(0, 1023) << std::endl;
	//hc.print();
}

/*
Udalo Ci sie wygenerowac macierz o rozmiarze 2^k na k.
Teraz musisz zaimplementowac szukanie maksymalnego przeplywu
z wykorzystaniem macierzy przynaleznosci.
*/

// Number of vertices in given graph 
//#define V 4   
