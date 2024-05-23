#pragma once
#include "Edge.h"
#include "memtrace.h"

class I_src :
    public Edge
{
    double current;
    static string type;
public:
    //constructor
    I_src(Verticle* a = nullptr, Verticle* b = nullptr, double I = 0) : current(I), Edge(a, b){};
    //setter of the I attribute
    bool setI(const double I);
    //getter of the I attribute
    double getI() const;
    //getter of the type attribute
    string getType() const
    {
        return type;
    }
    //returns CURRENT enum as an unsigned int
    unsigned charteristics() const;
};