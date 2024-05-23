#pragma once
#include "memtrace.h"
#include "Edge.h"

using namespace std;
class V_src :
    public Edge
{
    double voltage;
    static string type; //upgrade purposes
public:
    //Constructor
    V_src(Verticle* a = nullptr, Verticle* b = nullptr, double U = 0) : voltage(U), Edge(a, b){};
    //setter of the voltage attribute
    bool setV(const double U);
    //getter of the voltage attribute
    double getV() const;
    //getter of the type attribute
    string getType() const
    {
        return type;
    }
    //returns VOLTAGE enum as an unsigned int
    unsigned charteristics() const;
};

