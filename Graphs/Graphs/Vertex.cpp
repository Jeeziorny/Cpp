#include "pch.h"
#include "Vertex.h"


Vertex::Vertex(int id)
{
	this->id = id;
	this->d = (double)INT_MAX;
}


Vertex::~Vertex()
{

}

int Vertex::getId()
{
	return id;
}

void Vertex::addAdj(Vertex *v, double w)
{
	adjacent.push_back(pair<vptr, double>(vptr(v), w));
}

void Vertex::setD(double d)
{
	this->d = d;
}

double Vertex::getD()
{
	return d;
}

void Vertex::setLast(Vertex &v)
{
	last = vptr(&v);
}

Vertex& Vertex::getLast()
{
	return *last;
}

void Vertex::resetLast()
{
	last = nullptr;
}

vector<pair<Vertex *, double>>& Vertex::getAllAdj()
{
	return adjacent;
}

