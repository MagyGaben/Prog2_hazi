#pragma once
#include "TwoPort.h"
#include "memtrace.h"

class Transformer :
    public TwoPort
{
    double n;
    static string type;
public:
    Transformer(Verticle* a = nullptr, Verticle* b = nullptr,const double n = 1.0, Transformer* that = nullptr) : TwoPort(a, b, that), n(n) {};
    //setter of the n attribute
    bool setn(const double n);
    //getter of the n attribute
    double getn() const;
    //getter of the type attribute
    string getType() const
    {
        return type;
    }
    //returns TRANSFORMER enum as an unsigned int
    unsigned charteristics() const;
};

