#pragma once
#include "Graph.h"

class UndirectedGraph :
	public Graph
{
private:
	vector<tuple<int, int, double>> Edges =
		vector<tuple<int, int, double>>();

	void _union(int a, int b);
public:
	UndirectedGraph(int x);
   ~UndirectedGraph();
	void addEdge(int from, int to, double w);
	void kruskal();
	void prim();
};

