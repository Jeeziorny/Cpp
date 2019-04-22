// Graphs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "UndirectedGraph.h"

int main()
{
	Graph g = Graph(7);
	UndirectedGraph ug = UndirectedGraph(6);

	g.addEdge(0, 1, 1);
	g.addEdge(4, 0, 1);
	g.addEdge(4, 5, 1);
	g.addEdge(1, 5, 1);
	g.addEdge(1, 4, 1);
	g.addEdge(1, 2, 1);
	g.addEdge(6, 2, 1);
	g.addEdge(5, 6, 1);
	g.addEdge(6, 5, 1);
	g.addEdge(5, 3, 1);
	g.addEdge(6, 7, 1);
	g.addEdge(7, 7, 1);
	g.addEdge(3, 7, 1);
	g.addEdge(2, 3, 1);
	g.addEdge(3, 2, 1);

	g.strongly_connected_components();
}