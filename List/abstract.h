#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED


template <class elemType>
class list
{
public:
    virtual void clear() = 0;
    virtual int length() const = 0;
    virtual void insert(int i, const elemType &x);
    virtual remove(int i) = 0;
    virtual int search(const elemType &x, int i = 0);
    virtual elemType visit(int i) const = 0;
    virtual void traverse() const = 0;
    virtual ~list() {};
};


#endif