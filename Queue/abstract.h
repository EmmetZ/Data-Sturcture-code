#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED


template <class elemType>
class queue
{
public:
    virtual bool isEmpty() const = 0;               //判断对列是否为空
    virtual void enQueue(const elemType &x) = 0;     //进队
    virtual elemType deQueue() = 0;                  //出队
    virtual elemType getHead() const = 0;            //读取队头元素
    virtual ~queue() {}                              //虚析构函数
};


#endif