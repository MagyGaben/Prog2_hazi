#pragma once
#include "memtrace.h"
#include "Verticle.h"
#include <string>

using namespace std;
enum CharacterCodes
{
	RESISTANCE = 1,
	TRANSFORMER,
	GYRATOR,
	VOLTAGE,
	CURRENT	//maradjon mindig utols�
};

class Edge
{
	Verticle* a;
	Verticle* b;
	double I;	//current on the edge
	double U;	//voltage on the branch
public:
	//constructor
	Edge(Verticle* a = nullptr, Verticle* b = nullptr) : a(a), b(b) , U(0), I(0)
	{ 
		if (this->a !=nullptr)
		this->a->addEdge(this);
		if (this->b != nullptr)
		this->b->addEdge(this); 
	}
	//setter of the U attribute
	bool setU(const double u);
	//getter of the U attribute
	double getU();
	//setter of the I attribute
	bool setI(const double I);
	//getter of the I attribute
	virtual double getI() const;

	//define dipole as an edge that has charteristics, type, etc, a literal dipol
	//I did not make a class for them, sincethere is no such a thing as a "dipol" 
	//instead i am using the edge name, as it is a mathematical definition

	//returns charteristics-enum as an unsigned int if a dipol is made
	virtual unsigned charteristics() const = 0;
	//setter of the a pointer attribute to the first verticle of the edge
	bool seta(Verticle* a);
	//setter of the b pointer attribute to the second verticle of the edge
	bool setb(Verticle* b);
	//setter of the a pointer attribute to the first verticle of the edge
	Verticle* geta() const;
	//setter of the b pointer attribute to the second verticle of the edge
	Verticle* getb() const;
	//switches a and b
	void switch_direction();
	//getter of the type attribute if a dipol is made
	virtual string getType() const = 0;
};


