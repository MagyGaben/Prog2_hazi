#include "I_src.h"
string I_src::type = "I_src";

bool I_src::setI(const double I)
{
	if (I == current)
		return false;
	current = I;
	return true;
}

double I_src::getI() const
{
	return current;
}

unsigned I_src::charteristics() const	//overwrite of the charteristics function
{
	return CURRENT;
}