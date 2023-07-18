#ifndef SLINKLIST_INCLUDED
#define SLINKLIST_INCLUDED

#include "abstract.h"
#include<iostream>

template<class elemType>
class sLinkList: public list<elemType>
{
private:
    struct node
    {
        elemType data;
        node *next;

        node(const elemType &x, node *n=NULL)
            {data = x; next = n;}
        node(): next(NULL) {}
        ~node() {}
    };

    node *head;
    int currentLength;

    node *move(int i) const;

public:
    sLinkList();
    ~sLinkList() {clear(); delete head;}

    void clear();
    int length() const{return currentLength;}
    void insert(int i, const elemType &x);
    void remove(int i);
    int search(const elemType &x) const;
    elemType visit(int i) const;
    void traverse() const;     
};





#endif //SLINKLIST_INCLUDED