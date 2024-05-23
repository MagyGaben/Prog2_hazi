#include "V_src.h"

string V_src::type = "V_src";

bool V_src::setV(const double U)		//setter for the Voltage of the Voltage Source
{						
	if(U == voltage)
	return false;
	voltage = U;
	return true;
}

double V_src::getV() const				//getter for the voltage
{
	return voltage;
}

unsigned V_src::charteristics() const	//overwrite of the charteristics function
{
	return VOLTAGE;
}
