#include "Transformer.h"

string Transformer::type = "Transformer";

bool Transformer::setn(const double n)
{
    this->n = n;
    return true;
}

double Transformer::getn() const
{
    return n;
}

unsigned Transformer::charteristics() const
{
    return TRANSFORMER;
}
