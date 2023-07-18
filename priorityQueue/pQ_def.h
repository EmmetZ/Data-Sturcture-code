#ifndef PRIORITY_H_INCLUDE
#define PRIORITY_H_INCLUDE

#include "../Queue/abstract.h"

template<class Type>
class priorityQueue: public queue<Type>
{
private:
    int currentSize;
    Type *array;
    int maxSize;

    void doublespace();
    void buildHeap();
    void percolateDown(int hole);

public:
    priorityQueue(int capacity = 100);
    priorityQueue(const Type data[], int size);
    ~priorityQueue();
    bool isEmpty() const;
    void enQueue(const Type &x);
    Type deQueue();
    Type getHead() const;

};


template<class Type>
priorityQueue<Type>::priorityQueue(int capacity) 
{
    array = new Type[capacity];
    maxSize = capacity;
    currentSize = 0;
}


template<class Type>
priorityQueue<Type>::~priorityQueue()
{
    delete []array;
}


template<class Type>
bool priorityQueue<Type>::isEmpty() const
{
    return currentSize == 0;
}


template<class Type>
Type priorityQueue<Type>::getHead() const
{
    return array[1];
}


template<class Type>
void priorityQueue<Type>::enQueue(const Type &x) 
{
    if(currentSize == maxSize - 1) doublespace();

    int hole = ++currentSize; 
    for(; hole>1 && x<array[hole/2]; hole /= 2 )      //这里用for循环，hole>1条件可以阻止hole一直向上，会有一个终止条件
        array[hole] = array[hole / 2];
    array[hole] = x; 
}


template<class Type>
Type priorityQueue<Type>::deQueue() 
{
    Type minItem;
    minItem = array[1];
    array[1] = array[currentSize--];
    percolateDown(1);
    return minItem;
}


template<class Type>
void priorityQueue<Type>::percolateDown(int hole)
{
    int child = hole;
    Type tmp = array[hole];

    for(; hole*2 <= currentSize; hole = child) {
        child = hole*2;
        if(child != currentSize && array[child+1] < array[child])
            child++;
        if(array[child] < tmp) 
            array[hole] = array[child]; 
    }

    array[hole] = tmp;
}


template<class Type>
void priorityQueue<Type>::buildHeap()
{
    for(int i = currentSize / 2; i>0; --i)
        percolateDown(i);
}


template<class Type>
priorityQueue<Type>::priorityQueue(const Type *items, int size): maxSize(size + 10), currentSize(size)   //maxSize+10,避免一开始入队就需要调用doublespace()
{
    array = new Type[maxSize];
    for(int i = 0; i<size; ++i) {
        array[i+1] = items[i];
    }
    buildHeap();
}


template<class Type>
void priorityQueue<Type>::doublespace()
{
    Type *tmp = array;
    maxSize *= 2;
    array = new Type[maxSize];
    for(int i=0; i<=currentSize; ++i)
        array[i] = tmp[i];
    
    delete []tmp;
}



#endif