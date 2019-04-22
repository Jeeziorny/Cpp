#include "pch.h"
#include "UndirectedGraph.h"


UndirectedGraph::UndirectedGraph(int x) : Graph(x)
{
}

UndirectedGraph::~UndirectedGraph()
{
}

void UndirectedGraph::_union(int a, int b)
{
	Vertex* x = vertices.at(a).find_set();
	Vertex* y = vertices.at(b).find_set();

	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].find_set() == y)
		{
			vertices[i].setRepresentant(x);
		}
	}
}

void UndirectedGraph::addEdge(int from, int to, double w)
{
	try {
		vertices.at(from).addAdj(&vertices.at(to), w);
		vertices.at(to).addAdj(&vertices.at(from), w);
	}
	catch (std::out_of_range e)
	{
		std::cerr << "There is no " << from << " or " << to << std::endl;
	}
	if (w > maxWeight)
		maxWeight = w;
	Edges.push_back(tuple<int, int, double>{from, to, w});
}

void UndirectedGraph::kruskal()
{
	vector<tuple<int, int, double>> mst =
		vector<tuple<int, int, double>>();
	int a, b;
	for (int i = 0; i < vertices.size(); i++)
		vertices[i].setRepresentant(&vertices[i]);			//make set
	sort(Edges.begin(), Edges.end(), sortByWeight);			//sort set
	for (auto e : Edges)
	{
		a = get<0>(e);
		b = get<1>(e);
		if (vertices.at(a).find_set() != vertices.at(b).find_set())
		{
			mst.push_back(tuple<int, int, double>{a, b, (double)get<2>(e)});
			_union(a, b);
		}
	}
	for (auto i : mst)
	{
		std::cout << "u=" << get<0>(i) << ", v=" << get<1>(i) << ", w=" << get<2>(i) << std::endl;
	}
}

void UndirectedGraph::prim()
{
	vector<tuple<int, int, double>> mst =
		vector<tuple<int, int, double>>();
	init_single_source(0);
	PriorityQueue<double> Q = PriorityQueue<double>();
	for (auto v : vertices)
		Q.insert(v.getId(), v.getD());
	while (!Q.empty())
	{
		int id = Q.pop().getKey();
		Vertex &t = vertices.at(id);
		for (auto v : t.getAllAdj())
		{
			if (v.first->getD() > v.second)
			{
				Q.priority(v.first->getId(), v.second);
				(*v.first).setD(v.second);
				(*v.first).setLast(vertices[id]);
			}
		}
		if (id != 0)
			mst.push_back(tuple<int, int, double>
		{id, t.getLast()->getId(), t.getD()});
	}

	for (auto i : mst)
	{
		std::cout << "u=" << get<0>(i) << ", v=" << get<1>(i) << ", w=" << get<2>(i) << std::endl;
	}
}