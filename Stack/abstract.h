#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

template <class elemType>
class stack
{
public:
    virtual bool isEmpty() const = 0;
    virtual void push(const elemType &x) = 0;
    virtual elemType pop() = 0;
    virtual elemType top() const = 0;
    virtual ~stack() {}
};


#endif