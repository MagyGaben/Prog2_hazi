#pragma once
#include "memtrace.h"

class Edge;

class Verticle
{
	double potential;	//potential of the verticle, upgrade purposes
	double inflow;	//inflow in the verticle, upgrade purposes
	bool status;	//status of the verticle, upgrade purposes
	unsigned degree;	//degree of the verticle
	Edge **edges;	//pointer to the edges, which are connecting to the verticle
public:
	//Constructor
	Verticle(double potential = 0, double inflow = 0, unsigned d = 0, Edge** tmb = nullptr) : potential(potential), inflow(inflow), status(false), degree(d) { edges = tmb; }
	//Copy Constructor
	Verticle(const Verticle& other) : potential(other.potential), status(other.status), degree(other.degree), edges(other.edges), inflow(0.0) {}
	//Destructor
	~Verticle();
	//setter of the potential attribute
	bool setPot(double potential);
	//setter of the status attribute
	bool setStatus(bool status);
	//Connects an edge to the verticle
	bool addEdge(Edge* DBG_newedge);
	//returns true if the edge connects to the verticle
	bool isEdge(Edge* edge);
	//returns true if the verticle is equivalent to this
	bool isMe(Verticle* verticle);
	//getter of the potential attribute
	double getPot() const;
	//getter of the status attribute
	bool getStatus() const;
	//getter of the degree attribute
	unsigned getd() const;
	//getter of the edges attribute
	Edge** getEdgeArray() const;
};



