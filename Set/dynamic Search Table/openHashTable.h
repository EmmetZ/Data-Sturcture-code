#ifndef OPENHASHTABLE_H_INCLUDED
#define OPENHASHTABLE_H_INCLUDED

#include<iostream>
#include "abstract.h"

template <class KEY, class OTHER>
class openHashTable:public dynamicSearchTable<KEY, OTHER>
{
private:
    struct node
    {
        SET<KEY, OTHER> data;
        node *next;

        node(const SET<KEY, OTHER> &d, node *n = NULL){data = d, next = n;}
        node() {next = NULL;}
    };
    
    node **array;
    int size;
    int (*key)(const KEY &x);
    static int defaultKey(const int &x){return x;}

public:
    openHashTable(int length = 101, int(*f)(const KEY &x) = defaultKey);
    ~openHashTable();
    SET<KEY, OTHER> *find(const KEY &x) const;
    void insert(const SET<KEY, OTHER> &x);
    void remove(const KEY &x);
};


template <class KEY, class OTHER>
openHashTable<KEY, OTHER>::openHashTable(int length, int (*f)(const KEY &X))
{
    size = length;
    key = f;
    array = new int[size];
    for(int i = 0; i<size; ++i) array[i] = NULL;
}


template <class KEY, class OTHER>
openHashTable<KEY, OTHER>::~openHashTable()
{
    node *p, *q;
    for(int i = 0; i<size; ++i){
        p = array[i];
        while(p != NULL){q = p->next; delete p; p = q;};
    }

    delete array;
}


template <class KEY, class OTHER>
void openHashTable<KEY, OTHER>::insert(const SET<KEY, OTHER> &x) 
{
    int pos;
    node *p;

    pos = key(x.key) % size;
    array[pos] = new node(x, array[pos]);  
}


template <class KEY, class OTHER>
void openHashTable<KEY, OTHER>::remove(const KEY &x)
{
    int pos;
    node *p, *q;

    pos = key(x) % size;
    if(array[pos] == NULL) return;
    p = array[pos];
    if(array[pos]->data.key == x) {
        array[pos] = p->next;
        delete p;
        return;
    }

    while(p->next != NULL && !(p->next->data.key == x)) p = p->next;
    if(p->next != NULL) {
        q = p->next;
        p->next = q;
        delete q;
    }
}


template <class KEY, class OTHER>
SET<KEY, OTHER> *openHashTable<KEY, OTHER>::find(const KEY &x) const
{
    int pos;
    node *p;

    pos = key(x) % size;
    p = array[pos];
    while (p != NULL && !(p->data.key == x)) p = p->next;
    if(p == NULL) return NULL;
    else return (SET<KEY, OTHER> *)p;
}

#endif