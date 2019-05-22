#include "pch.h"
#include "HyperCube.h"
#include <queue>


HyperCube::HyperCube(const int k)
{
	this->k = k;
	adjMatrix = new int*[k];
	for (int i = 0; i < k; i++)
		adjMatrix[i] = new int[pow(2, k)];
	init();
}

int HyperCube::h(int a) {
	int r = 0;
	for (int j = 0; j < 32; j++) {
		if (a < 0) r++;
		a <<= 1;
	}
	return r;
}

HyperCube::~HyperCube()
{
	//dodaj delete []. Pamietaj, ze musisz przeiterowac po tablicy tablic
	//a na koncu usunac cala.
	for (int i = 0; i < k; i++)
		delete[] adjMatrix[i];
	delete[] adjMatrix;
}

void HyperCube::init() {
	/*
	Przelatuje po macierzy przynaleznosci.
	Pojemnosc jest rozna od zera (krawedz istnieje)
	tylko wtedy, gdy dla danej kolumny modyfikacja jej indeksu (toggle(j, i))
	ma wieksza wage hamminga niz sam indeks kolumny (j).

	Pojemnosc jest rowna zero, gdy krawedz nie istnieje.
	*/
	for (int j = 0; j < pow(2, k); j++) {
		for (int i = 0; i < k; i++) {
			if (h(j) < h(toggle(j, i)))
				adjMatrix[i][j] = genC(i, j);
			else
				adjMatrix[i][j] = 0;
		}
	}
}

int HyperCube::genC(int u, int v) {
	//Spojrz na wytyczne zadania, wtedy zrozumiesz kod.
	//rand jest zakomentowany, bo generuje niekiedy zera, 
	//co utrudnialo debugowanie.
	int a = h(u);
	int b = h(v);
	int c = k - h(u);
	int d = k - h(v);
	int bound = pow(2, max(a, b, c, d));
	return rand() % bound;
}

int HyperCube::max(int a, int b, int c, int d) {
	return std::max(std::max(a, b), std::max(c, d));
}

//ta funkcja zmienia bit w number na pos pozycji.
int HyperCube::toggle(int number, int pos) {
	return number ^= 1 << pos;
}

void HyperCube::print() {
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < pow(2, k); j++) {
			std::cout << adjMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

bool HyperCube::bfs(int ** rGraph, int s, int t, int parent[]) {
	bool * visited = new bool[pow(2, k)];
	for (int i = 0; i < pow(2, k); i++)
		visited[i] = false;

	std::queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int i = 0; i < k; i++) {
			//v staje sie kolejnymi liczbami, ktore znajduja sie 
			//w kolumnie u dzieki funkcji toggle();
			int v = toggle(u, i);
			if (visited[v] == false && rGraph[i][u] > 0) {
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}
	return visited[t] == true;
}

int HyperCube::edmondsKarp(int s, int t) {
	int u, v, z;
	int **rGraph;
	rGraph = new int*[k];
	for (int i = 0; i < k; i++)
		rGraph[i] = new int[pow(2, k)];

	//tymczasowy graf wypelniam tym, co jest w obiekcie.
	for (u = 0; u < k; u++)
		for (v = 0; v < pow(2, k); v++)
			rGraph[u][v] = adjMatrix[u][v];

	//Zastanow sie, czy parentow moze byc tyle samo co wierzcholkow
	int *parent = new int[pow(2, k)];
	int max_flow = 0;

	//bfs szuka najkrotszych sciezek i wsadza do parenta
	while (bfs(rGraph, s, t, parent)) {
		int path_flow = INT_MAX;
		//ide po sciezce szukajac minimum
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			z = find_row(u, v);
			path_flow = std::min(path_flow, rGraph[z][u]);
		}
		//odejmuje idac po sciezce
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			z = find_row(u, v);
			rGraph[z][u] -= path_flow;
		}
		max_flow += path_flow;
	}
	return max_flow;
}


/*
Majac dane u i v funkcja zwraca wiersz z kolumny u,
w ktorej jest v. Sluzy to znalezieniu komorki parenta
w funkcji edmondsKarp.
*/
int HyperCube::find_row(int u, int v) {
	for (int i = 0; i < k; i++) {
		if (toggle(u, i) == v) {
			return i;
		}
	}
	return -1;
}