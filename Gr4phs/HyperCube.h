#pragma once
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iostream>

class HyperCube
{
	//Macierz przynaleznosci dziala poprawnie dla k = {2, 3};
	int **adjMatrix;
	int k = 0;
	
	//obliczanie wagi hamminga;
	int h(int a);
	//generuje odpowiednia pojemnosc z wytycznych z zadania
	int genC(int u, int v);
	//pomocnik przy konstruktorze
	void init();
	int max(int a, int b, int c, int d);
	//zmienia bit na pos pozycji w liczbnie number
	int toggle(int number, int pos);
	bool bfs(int **rGraph, int s, int t, int parent[]);
	int find_row(int u, int v);
public:
	HyperCube(const int k);
	~HyperCube();
	void print();
	int edmondsKarp(int s, int t);
};
/*
bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
	// Create a visited array and mark all vertices as not visited 
	bool visited[V];
	memset(visited, 0, sizeof(visited));

	// Create a queue, enqueue source vertex and mark source vertex 
	// as visited 
	queue <int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	// Standard BFS Loop 
	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		for (int v = 0; v < V; v++)
		{
			if (visited[v] == false && rGraph[u][v] > 0)
			{
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	// If we reached sink in BFS starting from source, then return 
	// true, else false 
	return (visited[t] == true);
}*/