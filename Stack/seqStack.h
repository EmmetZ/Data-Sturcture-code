#ifndef SEQSTACK_H_INCLUDED
#define SEQSTACK_H_INCLUDED


#include "abstract.h"

template <class elemType>
class seqStack:public stack <elemType>
{
private:
    elemType *elem;
    int top_p;
    int maxSize;
    void doublespace();

public:
    seqStack(int initSize = 10);
    ~seqStack();
    bool isEmpty() const;
    void push(const elemType &x);
    elemType pop();
    elemType top() const;
};



template <class elemType>
seqStack<elemType>::seqStack(int initSize)
{
    elem = new elemType[initSize];
    top_p = -1;
    maxSize = initSize;
}


template <class elemType>
seqStack<elemType>::~seqStack()
{
    delete []elem;
}


template <class elemType>
bool seqStack<elemType>::isEmpty() const
{
    return top_p == -1;
}


template <class elemType>
void seqStack<elemType>::push(const elemType &x)
{
    if (top_p == maxSize-1) doublespace();
    elem[++top_p] = x;
}


template <class elemType>
elemType seqStack<elemType>::pop() 
{
    return elem[top_p--];
}


template <class elemType>
elemType seqStack<elemType>::top() const
{
    return elem[top_p];
}


template <class elemType>
void seqStack<elemType>::doublespace()
{
    elemType *tmp = elem;
    elem = new elemType[2*maxSize];
    for (int i = 0; i<maxSize; ++i) elem[i] = tmp[i];
    maxSize *= 2;
    delete tmp;
}


#endif