#pragma once
#include <vector>
#include <memory>

using namespace std;

class Vertex
{
public:
	//typedef std::shared_ptr<Vertex> vptr;
	typedef Vertex* vptr;
private:
	vector<pair<vptr, double>> adjacent
		= vector<pair<vptr, double>>();
	int id;			//natural number;
	double d;		//distance from s;
	vptr last;		//previous vertex on path;

public:
	Vertex(int id);
	~Vertex();

	void addAdj(Vertex *v, double w);

	int getId();
	void setD(double d);
	double getD();
	void setLast(Vertex &v);
	Vertex& getLast();
	void resetLast();

	vector<pair<vptr, double>>& getAllAdj();
};

