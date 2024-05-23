#include "Verticle.h"

Verticle::~Verticle()
{
	delete[] this->edges;
}

bool Verticle::setPot(double potential) //setter for the potential of the verticle
{
	if (this->status == false)
	{
		this->potential = potential;
		return true;
	}
	return false;
}

bool Verticle::setStatus(bool status)	//setter for the status of the verticle
{
	if(this->status == status)
	return false;
	this->status = status;
	return true;
}

bool Verticle::addEdge(Edge* newedge)	//adds a new edge to the verticle
{
	if(newedge == nullptr)
	return false;
	for (size_t i = 0; i < this->degree; i++)
	{
		if (this->edges[i] == newedge) return false;
	}
	Edge** tmp = new Edge * [degree + 1];
	for (size_t i = 0; i < degree; i++)
	{
		tmp[i] = edges[i];
	}
	tmp[degree] = newedge;
	degree++;
	
	delete[] this->edges;
	this->edges = tmp;
	return true;
}

bool Verticle::isEdge(Edge* edge)	//returns if the edge is attached to this verticle
{
	for (size_t i = 0; i < degree; i++)
	{
		if (edges[i] == edge) return true;
	}
	return false;
}

bool Verticle::isMe(Verticle* verticle)	//returns if this verticle is equivalent to the given one
{
	if (verticle == this) return true;
	return false;
}

double Verticle::getPot() const			//getter for the potential
{
	return this->potential;
}

bool Verticle::getStatus() const		//getter for status
{
	return status;
}

unsigned Verticle::getd() const			//getter for the degree
{
	return degree;
}

Edge** Verticle::getEdgeArray() const	//getter for the edges array
{
	return edges;
}
