#pragma once
#include "Vertex.h"
#include "PriorityQueue.h"
#include <iostream>

using namespace std;

class Graph
{
private:
	vector<Vertex> vertices = vector<Vertex>();

	void init_single_source(int id);
	void relax(Vertex &u, Vertex &v, double w);
	void relax2(int u, int v, double w);

	double maxWeight = -1.0;
public:
	Graph(int n);
	~Graph();
	void showPaths();
	void addEdge(int from, int to, double w);
	void addUndirectedEdge(int u, int v, double w);
	void dijkstra(int id);
};

