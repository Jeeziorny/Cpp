#pragma once
#include <vector>

using namespace std;

class Vertex
{
public:
	//typedef std::shared_ptr<Vertex> vptr;
	typedef Vertex* vptr;
	enum Color {WHITE, GREY, BLACK};
private:
	vector<pair<vptr, double>> adjacent
		= vector<pair<vptr, double>>();
	int id;				//natural number;
	double d;			//distance from s;
	double f;
	vptr last;			//previous vertex on path;
	vptr representant;	//kruskall
	Color color;
public:
	Vertex(int id);
	~Vertex();

	void addAdj(Vertex *v, double w);

	void clearAdj();
	void setF(double f);
	double getF() const { return f; };
	Color getColor();
	void setColor(Color c);
	int getId();
	void setD(double d);
	double getD();
	void setLast(Vertex &v);
	Vertex* getLast();
	void resetLast();
	vptr find_set();
	void setRepresentant(Vertex *);

	vector<pair<vptr, double>>& getAllAdj();
};

