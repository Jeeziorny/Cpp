#include "pch.h"
#include "Graph.h"


Graph::Graph(int n)
{
	for (int i = 0; i < n; i++)
		vertices.push_back(Vertex(i));
}


Graph::~Graph()
{
}



void Graph::addEdge(int from, int to, double w)
{
	try {
		vertices.at(from).addAdj(&vertices.at(to), w);
	}
	catch (std::out_of_range e)
	{
		std::cerr << "There is no " << from << " or " << to << std::endl;
	}

	if (w > maxWeight)
		maxWeight = w;
}

void Graph::addUndirectedEdge(int u, int v, double w)
{
	addEdge(u, v, w);
	addEdge(v, u, w);
}

void Graph::init_single_source(int id)
{
	for (auto i : vertices)
	{
		i.setD(maxWeight+1);
		i.resetLast();
	}
	try {
		vertices.at(id).setD(0);
	}
	catch (std::out_of_range e)
	{
		std::cerr << "Incorrect source (init_single_source)\n";
	}
}

void Graph::showPaths()
{
	for (auto v : vertices)
	{
		std::cout << "Id = " << v.getId() << ", weight: " << v.getD() << std::endl;
	}
}

void Graph::relax2(int u, int v, double w)
{
	//check is done from vertex u;
	if (vertices.at(v).getD() > vertices.at(u).getD() + w)
	{
		vertices.at(v).setD(vertices.at(u).getD() + w);
		vertices.at(v).setLast(vertices.at(u));
	}
}

void Graph::relax(Vertex &u, Vertex &v, double w)
{
	if (v.getD() > u.getD() + w)
	{
		v.setD(u.getD() + w);
		v.setLast(u);
	}
}
void Graph::dijkstra(int id)
{
	init_single_source(id);
	PriorityQueue<double> Q = PriorityQueue<double>();
	for (auto v : vertices)
	{
		Q.insert(v.getId(), v.getD());
	}
	while (!Q.empty())
	{
		int id = Q.pop().getKey();
		Vertex &t = vertices.at(id);
		for (auto v : t.getAllAdj())
			relax(t, *v.first, v.second);
	}
}