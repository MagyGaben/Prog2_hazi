#pragma once
#include "memtrace.h"

#include "Edge.h"
using namespace std;
class Resistance :
	public Edge
{
	double R;
	static string type;
public:
	//Constructor
	Resistance(Verticle* a = nullptr, Verticle* b = nullptr, double R = 0) :R(R), Edge(a, b) { this->setU(0.0); };
	//Calculates I, upgrade purposes
	bool calcI();
	//Calculates U, upgrade purposes
	bool calcU();
	//getter of the R attribute
	double getR() const;
	//Calculates Power, upgrade purposes
	double getP() const;
	//operator=, upgrade purposes
	void operator=(Resistance& other);
	//operator+, upgrade purposes
	Resistance& operator+(Resistance& other);
	//getter of the type attribute
	string getType() const
	{
		return type;
	}
	//returns RESISTANCE enum as an unsigned int
	unsigned charteristics() const;

};

