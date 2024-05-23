#pragma once
#include "TwoPort.h"
#include "memtrace.h"

class Gyrator :
    public TwoPort
{
    double r;
    static string type;
public:
    Gyrator(Verticle* a = nullptr, Verticle* b = nullptr, const double r = 1.0, Gyrator* that = nullptr) : TwoPort(a, b, that), r(r) {};
    //setter of the r attribute
    bool setr(const double n);
    //getter of the r attribute
    double getr() const;
    //getter of the type attribute
    string getType() const
    {
        return type;
    }
    //returns GYRATOR enum as an unsigned int
    unsigned charteristics() const;
};

