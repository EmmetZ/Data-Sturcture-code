#ifndef LINKQUEUE_H_INCLUDED
#define LINKQUEUE_H_INCLUDED


#include "abstract.h"
#include<iostream>

template<class elemType>
class linkQueue:public queue<elemType>
{
private:
    struct node
    {
        elemType data;
        node *next;
        node(const elemType &x, node *N = NULL)
        {data = x; next = N;}
        node():next(NULL) {}
        ~node() {}
    };

    node *front, *rear;

public:
    linkQueue();
    ~linkQueue();
    bool isEmpty() const;
    void enQueue (const elemType &x);
    elemType deQueue();
    elemType getHead() const;
};


template<class elemType>
linkQueue<elemType>::linkQueue()
{
    front = rear = NULL;
}


template<class elemType>
linkQueue<elemType>::~linkQueue()
{
    node *tmp;
    while(front != NULL) {
        tmp = front;
        front = front -> next;
        delete tmp;
    }
}


template<class elemType>
bool linkQueue<elemType>::isEmpty() const
{
    return front == NULL;
}


template<class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)
{
    if (rear == NULL) {
        front = rear = new node(x);
    }
    else {
        node *tmp = new node(x);
        rear -> next = tmp;
        rear = tmp;
    }
    
}


template<class elemType>
elemType linkQueue<elemType>::deQueue()
{
    node *tmp = front;
    elemType x = tmp->data;
    front = front->next;
    if(front == NULL) rear = NULL;
    delete tmp;
    return x;
}


template<class elemType>
elemType linkQueue<elemType>::getHead() const
{
    return front->data;
}


#endif