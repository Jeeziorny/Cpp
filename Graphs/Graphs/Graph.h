#pragma once
#include "Vertex.h"
#include "PriorityQueue.h"
#include <algorithm>
#include <tuple>

using namespace std;
bool sortByWeight(const std::tuple<int, int, double>& a,
	const std::tuple<int, int, double>& b);
bool compareByF(const Vertex* a, const Vertex* b);

class Graph
{
private:
	vector<tuple<int, int, double>> Edges =
		vector<tuple<int, int, double>>();

	int time;
protected:
	vector<Vertex> vertices = vector<Vertex>();

	void dfs_visit(Vertex& v);
	void transpoze();
	void dfs();
	void init_single_source(int id);
	void dijkstraRelax(Vertex &u, Vertex &v, double w);

	double maxWeight = 0.0;
	Vertex* last_dfs_visit;
public:
	Graph(int n);
	~Graph();
	void showPaths();
	virtual void addEdge(int from, int to, double w);
	void dijkstra(int id);
	void strongly_connected_components();
};



