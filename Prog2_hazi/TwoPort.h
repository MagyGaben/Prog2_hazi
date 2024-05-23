#pragma once
#include "Edge.h"
#include "memtrace.h"
class TwoPort :
    public Edge
{
    Edge* Connected_to;
public:
    //constructor
    TwoPort(Verticle* a = nullptr, Verticle* b = nullptr, Edge* that = nullptr) : Connected_to(that), Edge(a, b) {};
    //setter of the Connected_to attribute
    bool setoth(Edge* other);
    //getter of the Connected_to attribute
    Edge* getoth() const;
};

