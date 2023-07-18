#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

#include <iostream>
#include "abstract.h"

template<class KEY, class OTHER>
class binarySearchTree: public dynamicSearchTable<KEY, OTHER>
{
private:
    struct BinaryNode
    {
        SET<KEY, OTHER> data; 
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const SET<KEY, OTHER> &thedata, BinaryNode *lt = NULL, BinaryNode *rt = NULL)
        : data(thedata), left(lt), right(rt) {}
    };
    
    BinaryNode *root;

public:
    binarySearchTree();
    ~binarySearchTree();
    SET<KEY, OTHER> *find(const KEY &x) const;
    void insert(const SET<KEY, OTHER> &x);
    void remove(const KEY &x);

private:
    void insert(const SET<KEY, OTHER> &x, BinaryNode *&t);
    void remove(const KEY &x, BinaryNode *&t);
    SET<KEY, OTHER> *find(const KEY &x, BinaryNode *t) const;
    void makeEmpty(BinaryNode *t);
};




template<class KEY, class OTHER>
SET<KEY, OTHER> *binarySearchTree<KEY ,OTHER>::find(const KEY &x) const
{
    return find(x,root);
}


template<class KEY, class OTHER>
SET<KEY, OTHER> *binarySearchTree<KEY ,OTHER>::find(const KEY &x, BinaryNode *t) const
{
    if(t == NULL || t->data.key == x) return &(t->data);               //&:取地址   or return (SET<KEY, OTHER> * ) t;
    if(x<t->data.key) return find(x, t->left);
    else return find(x, t->right);
}


template<class KEY, class OTHER>
void binarySearchTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x)
{
    insert(x, root);
}


template<class KEY, class OTHER>
void binarySearchTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x, BinaryNode *&t)
{
    if(t == NULL) t = new BinaryNode(x, NULL, NULL);
    else 
        if(x.key<t->data.key) insert(x, t->left);
        else if(t->data.key<x.key) insert(x, t->right);
}


template<class KEY, class OTHER>
void binarySearchTree<KEY, OTHER>::remove(const KEY &x)
{
    remove(x, root);
}


template<class KEY, class OTHER>
void binarySearchTree<KEY,OTHER>::remove(const KEY &x, BinaryNode *&t)
{
    if(t == NULL) return;
    if(x<t->data.key) remove(x, t->left);
    else 
        if(x>t->data.key) remove(x ,t->right);        
        else 
            if(t->left != NULL && t->right != NULL) {
                BinaryNode *tmp = t->right;
                while(tmp->left != NULL) tmp = tmp->left;
                t->data = tmp->data;
                remove(t->data, t->right);
            }
            else{
                BinaryNode *olfdNode = t;
                t = (t->left != NULL)? t->left : t->right;
                delete olfdNode; 
            }
}


template<class KEY, class OTHER>
binarySearchTree<KEY, OTHER>::binarySearchTree()
{
    root = NULL;
}


template<class KEY, class OTHER>
void binarySearchTree<KEY, OTHER>::makeEmpty(BinaryNode *t)
{
    if(t = NULL) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}


template<class KEY, class OTHER>
binarySearchTree<KEY, OTHER>::~binarySearchTree()   
{
    makeEmpty(root);
}



#endif

