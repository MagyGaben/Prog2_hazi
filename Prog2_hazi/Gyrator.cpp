#include "Gyrator.h"


string Gyrator::type = "Gyrator";

bool Gyrator::setr(const double r)
{
    this->r = r;
    return true;
}

double Gyrator::getr() const
{
    return r;
}

unsigned Gyrator::charteristics() const
{
    return GYRATOR;
}