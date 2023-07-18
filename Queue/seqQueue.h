#ifndef SEQQUEUE_H_INCLUDED
#define SEQQUEUE_H_INCLUDED


#include "abstract.h"

template <class elemType>
class seqQueue: public queue<elemType>
{
private:
    elemType *elem;
    int maxSize;
    int front, rear;
    void doublespace();

public:
    seqQueue(int size = 10);
    ~seqQueue();
    bool isEmpty() const;
    void enQueue(const elemType &x);
    elemType deQueue();
    elemType getHead() const;
};



//实现循环对列

template<class elemType>
seqQueue<elemType>::seqQueue(int size) 
{
    elem = new elemType[size];
    maxSize = size;
    front = rear = 0;
}


template<class elemType>
seqQueue<elemType>::~seqQueue()
{
    delete []elem;
}


template<class elemType>
bool seqQueue<elemType>::isEmpty() const
{
    return front == rear;
}


template<class elemType>
void seqQueue<elemType>::enQueue(const elemType &x)
{
    if((rear + 1)%maxSize == front) doublespace();
    rear = (rear + 1)%maxSize;
    elem[rear] = x;
}


template<class elemType>
elemType seqQueue<elemType>::deQueue()
{
    front = (front + 1)% maxSize;
    return elem[front];
}


template<class elemType>
elemType seqQueue<elemType>::getHead() const
{
    return elem[(front+1)%maxSize];
}


template<class elemType>
void seqQueue<elemType>::doublespace()
{
    elemType *tmp = elem;
    elem = new elemType[2*maxSize];
    for (int i = 0; i<maxSize; ++i)
        elem[i] = tmp[(front + i)%maxSize];
    front = 0;
    rear = maxSize - 1;
    maxSize *= 2;
    delete tmp;
}


#endif