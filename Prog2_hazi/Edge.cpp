#include "Edge.h"

bool Edge::setU(const double u)	//setter for the voltage
{
	U = u;
	return true;
}

double Edge::getU()	//getter for the voltage
{
	return U;
}

bool Edge::setI(const double I)	//setter for the current
{
	if(this->I != I)
	{
		this->I = I;
		return true;
	}
	return false;
}

double Edge::getI() const	//getter for the current
{
	return I;
}

bool Edge::seta(Verticle* a)	//setter for the first vertcle
{
	if (a != this->a && a != this->b)
	{
		this->a = a;
		return true;
	}
    return false;
}

bool Edge::setb(Verticle* b)	//setter for the second verticle
{
	if (b != this->a && b != this->b)
	{
		this->a = b;
		return true;
	}
	return false;
}

Verticle* Edge::geta() const	//getter for the first verticle's pointer
{
	return a;
}

Verticle* Edge::getb() const	//getter for the second verticle's pointer
{
	return b;
}

void Edge::switch_direction()	//switch the direction of the edge
{
	Verticle* tmp = a;
	a = b;
	b = tmp;
}
