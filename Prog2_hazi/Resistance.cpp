#include "Resistance.h"
string Resistance::type = "Resistance";

// Charteristics of a resistance is I = U/R
bool Resistance::calcI()
{
	if (R == 0)
		return false;
	this->setI(this->getU() / R);
	return true;
}

// Charteristics of a resistance is I*R = U
bool Resistance::calcU()
{
	return this->setU(this->getI() * R); // Reseting U
}

double Resistance::getR() const // getter for the resistance
{
	return R;
}

double Resistance::getP() const // getter for the power of the resistance
{
	return this->getI() * R * R;
}

void Resistance::operator=(Resistance &other) // overwrote operator =
{
	this->seta(other.geta());
	this->setb(other.getb());
	this->R = other.R;
	calcI();
}

Resistance &Resistance::operator+(Resistance &other) // returns the resulting resistance
{
	// Linear
	if (
		(this->geta() == other.getb() && this->getb() != this->geta()) // b is shared
		|| /* Yes this is an 'or' relation*/						   //	(a)------ (b) ------- (c)
		(this->getb() == other.geta() && this->geta() != other.getb()) // a & c are different
	)
	{
		return *new Resistance(this->geta(), other.getb(), (this->R + other.R));
	}

	// Paralell
	else if (
		(this->geta() == other.geta() && this->getb() == this->getb()) //		|-------|
		||															   // a O-	|		|	-O b		a and b are shared, even if the direction of each is reversed
		(this->geta() == other.getb() && this->getb() == other.geta()) //		|-------|
	)
	{
		return *new Resistance(this->geta(), other.getb(), (this->R + other.R));
	}
	else
		return *this;
}

unsigned Resistance::charteristics() const // overwrite of the charteristics function
{
	return RESISTANCE;
}
