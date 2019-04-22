#include "pch.h"
#include "Graph.h"

void Graph::dfs_visit(Vertex& v)
{
	v.setColor(Vertex::GREY);
	v.setD(++time);
	bool gotAdj = false;
	for (auto& u : v.getAllAdj())
	{
		if (u.first->getColor() == Vertex::WHITE)
		{
			gotAdj = true;
			u.first->setLast(v);
			last_dfs_visit = u.first;
			dfs_visit(*u.first);
		}
	}
	v.setColor(Vertex::BLACK);
	v.setF(++time);
	if (!gotAdj)
		last_dfs_visit = &v;
}

void Graph::transpoze()
{
	vector<tuple<int, int, double>> nEdges =
		vector<tuple<int, int, double>>();
	for (Vertex& v : vertices)
	{
		v.clearAdj();
		v.resetLast();
	}
	last_dfs_visit = nullptr;
	int temp;
	for (auto p : Edges)
	{
		nEdges.push_back(tuple<int, int, double>{
			get<1>(p), get<0>(p), get<2>(p)
		});
		vertices.at(get<1>(p))
			.addAdj(&vertices[get<0>(p)], get<2>(p));
	}
	Edges = nEdges;
	last_dfs_visit = nullptr;
}

void Graph::dfs()
{
	Vertex* temp = nullptr;
	vector<Vertex *> ptrs = vector<Vertex *>();
	for (auto& v : vertices)
	{
		v.setColor(Vertex::WHITE);
		ptrs.push_back(&v);
	}
	time = 0;
	sort(ptrs.begin(), ptrs.end(), compareByF);
	for (auto ptr : ptrs)
	{
		if (ptr->getColor() == Vertex::WHITE)
		{
			dfs_visit(*ptr);
			temp = last_dfs_visit;
			while (temp != nullptr)
			{
				std::cout << temp->getId() << ", ";
				temp = temp->getLast();
			}
			std::cout << std::endl;
		}
	}
}
/*
	for (auto& v : vertices)
	{
		if (v.getColor() == Vertex::WHITE)
		{
			dfs_visit(v);
			temp = last_dfs_visit;
			while (temp != nullptr)
			{
				std::cout << temp->getId() << ", ";
				temp = temp->getLast();
			}
			std::cout << std::endl;
		}
	}
*/
//}

Graph::Graph(int n)											
{
	for (int i = 0; i <= n; i++)
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
	Edges.push_back(tuple<int, int, double>{from, to, w});
	if (w > maxWeight)
		maxWeight = w;
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
		vertices.at(id).resetLast();
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
	Vertex * curr;
	for (auto v : vertices)
	{
		std::cerr << "\nPath to: " << v.getId() << "\n";
		curr = &v;
		while (curr != nullptr)
		{
			std::cerr << curr->getId() << " ";
			curr = curr->getLast();
		}
	}

}

void Graph::dijkstraRelax(Vertex &u, Vertex &v, double w)
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
			dijkstraRelax(t, *v.first, v.second);
	}
}

void Graph::strongly_connected_components()
{
	dfs();
	transpoze();
	std::cout << "\n\n\n\n\n\n\n";
	dfs();
}

bool sortByWeight(const std::tuple<int, int, double>& a,
	const std::tuple<int, int, double>& b)
{
	return (get<2>(a) < get<2>(b));
}

bool compareByF(const Vertex* a, const Vertex* b)
{
	return (a->getF() > b->getF());
}