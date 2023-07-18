#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED

template <class KEY, class OTHER>
struct SET
{
    KEY key;
    OTHER other;
    
    
    int seqSearch_unordered(SET<KEY, OTHER> data[], int size, const KEY &x);//无序查找
    int seqSearch_ordered(SET<KEY, OTHER> data[], int size, const KEY &x);//有序查找
    int binarySearch(SET<KEY, OTHER> data[], int size, const KEY &x);//二分查找

    

};






template <class KEY, class OTHER>
int SET<KEY, OTHER>::seqSearch_unordered(SET<KEY, OTHER> data[], int size, const KEY &x)
{
    int i;
    data[0]->key = x;
    for(i = size; x != data; --i);
    return i;
}


template <class KEY, class OTHER>
int SET<KEY, OTHER>::seqSearch_ordered(SET<KEY, OTHER> data[], int size, const KEY &x)
{
    data[0]->key = x;
    int i;
    for(i = size; x < data[i]->key; --i);
    if(x < data[i]->key || i == 0) return 0;
    else return i;
}


template <class KEY, class OTHER>
int SET<KEY, OTHER>::binarySearch(SET<KEY, OTHER> data[], int size, const KEY &x)
{
    int low = 1, high = size, mid;
    while(low <= high) {
        mid = (low + high) / 2;
        if(x == data[mid]->key) return mid;
        else 
            if(x < data[mid]->key) high = mid - 1;   //这里+1/-1是避免落入死循环！
            else low = mid + 1;   
    }

    return 0;
}   










#endif