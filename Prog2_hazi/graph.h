#pragma once
#include "memtrace.h"
#include "V_src.h"
#include "I_src.h"
#include "Resistance.h"
#include "Transformer.h"
#include "Gyrator.h"
#include "matrix.h"
using namespace std;

class graph
{
	vector<Verticle*> V;
	Edge** E;

	unsigned n;	//number of vertivles
	unsigned b;	//number of edges
	unsigned l;	//number of loops
	void setl();
public:
	//basic functions
	graph(Verticle V[] = nullptr, Edge** E = nullptr, unsigned n = 0, unsigned b = 0) : V(), E(E), n(n), b(b), l(b - n + 1) 
	{
		for (size_t i = 0; i < n; i++)
		{
			this->V.push_back(&V[i]);
		}
	};
	graph(unsigned n);
	graph(graph& other);
	~graph();

	//
	bool addv(Verticle* v);
	bool adde(Edge* e);
	void deledge(unsigned i);
	//getter of the n attribute
	unsigned getn() const;
	//getter of the b attribute
	unsigned getb() const;
	//getter of the l attribute
	unsigned getl();
	//getter of the i element of the V array
	Verticle* getv(unsigned i) const;
	//getter of the i element of the E array
	Edge* getedge(unsigned i) const;

	//returns true if the verticle is element of the graph
	unsigned isverticle(Verticle *v);
	//returns true if the edge is element of the graph
	unsigned isedge(Edge *e);

	//solves the graph for each branch
		//UPGRADE IDEA: solves the graph automaticly
		//UPGRADE IDEA: solves each verticle also
	bool solve(ostream& out = cout, istream& in = cin);
};

