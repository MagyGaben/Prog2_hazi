#include "TwoPort.h"

bool TwoPort::setoth(Edge* other)
{
	if(other == nullptr)
	return false;
	this->Connected_to = other;
	return true;
}

Edge* TwoPort::getoth() const
{
	return Connected_to;
}
