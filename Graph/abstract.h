#ifndef GRAPH_INCLUDED
#define GRAPH_INCLUDED

#include<iostream>

template<class TypeOfVer, class TypeOfEdge>
class graph
{
public:
    virtual void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) = 0;
    virtual void remove(TypeOfVer x, TypeOfEdge y) = 0;
    virtual bool exist(TypeOfVer x, TypeOfEdge y) const = 0;
    int numOfVer() const {return Vers;}
    int numOfEdge() const  {return Edges;}

protected:
    int Vers, Edges;
};  


#endif