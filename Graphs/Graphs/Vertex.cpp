#include "pch.h"
#include "Vertex.h"


Vertex::Vertex(int id)
{
	this->id = id;
	this->d = (double)INT_MAX;
	this->last = nullptr;
	this->f = 0;
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

Vertex::Color Vertex::getColor()
{
	return color;
}

void Vertex::setColor(Vertex::Color c)
{
	color = c;
}

void Vertex::setF(double f)
{
	this->f = f;
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

Vertex* Vertex::getLast()
{
	return last;
}

void Vertex::resetLast()
{
	last = nullptr;
}

void Vertex::clearAdj()
{
	adjacent.clear();
}

vector<pair<Vertex *, double>>& Vertex::getAllAdj()
{
	return adjacent;
}

Vertex* Vertex::find_set()
{
	return representant;
}

void Vertex::setRepresentant(Vertex * a)
{
	this->representant = a;
}