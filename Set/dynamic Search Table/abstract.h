#ifndef DYNAMICSEARCHTABLE_H_INCLUDED
#define DYNAMICSEARCHTABLE_H_INCLUDED

template<class KEY, class OTHER>
struct SET
{
    KEY key;
    OTHER other;
};

template<class KEY, class OTHER>
class dynamicSearchTable 
{
    virtual SET<KEY, OTHER> *find(const KEY &x) const = 0;
    virtual void insert(const SET<KEY, OTHER> &x) const = 0;
    virtual void remove(const KEY &x) = 0;
    virtual ~dynamicSearchTable() {};
};


#endif