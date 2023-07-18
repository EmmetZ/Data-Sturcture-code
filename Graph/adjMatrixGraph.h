#ifndef ADJMATRIXGRAPH_INCLUDED
#define ADJMATRIXGRAPH_INCLUDED

#include<iostream>
#include"abstract.h"

template<class TypeOfVer, class TypeOfEdge>
class adjMatrixGraph: public graph<TypeOfVer, TypeOfEdge>
{
public:
    adjMatrixGraph(int vSize, const TypeOfVer d[], const TypeOfEdge noEdgeFlag);
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y) const;
    ~adjMatrixGraph();

private:
    TypeOfEdge **edge;
    TypeOfVer *ver;
    TypeOfEdge noEdge;
    int Vers, Edges;

    int find(TypeOfVer x) const
    {
        for(int i=0; i<Vers; ++i)
            if(ver[i] == x) return i; 
    }
};


template<class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::adjMatrixGraph(int vSize, const TypeOfVer d[], const TypeOfEdge noEdgeFlag)
{
    int i, j;

    Vers = vSize;
    Edges = 0;
    noEdge = noEdgeFlag;

    ver = new TypeOfVer[vSize];
    for(i=0; i<vSize; ++i) ver[i] = d[i];

    edge = new TypeOfEdge *[vSize];
    for(i=0; i<vSize; ++i) {
        edge[i] = new TypeOfEdge[vSize];
        for(j=0; j<vSize; ++j) edge[i][j] = noEdge;
        edge[i][i] = 0;
    }
}



template<class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::~adjMatrixGraph()
{
    delete []ver;
    for(int i=0; i<Vers; ++i) delete []edge[i];
    delete []edge;
}


template<class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w)
{
    int u = find(x), v = find(y);
    if(u>=Vers || v>=Vers) return;
    edge[u][v] = w;
    ++Edges;
}



template<class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y)
{
    int u = find(x), v = find(y);
    edge[u][v] = noEdge;
    --Edges;
}


template<class TypeOfVer, class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const
{
    int u = find(x), v = find(y);
    if(edge[u][v] == noEdge) return false;
    else return true;
}


#endif