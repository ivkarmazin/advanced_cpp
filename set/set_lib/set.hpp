#pragma once
#include "list"
#include "set.h"
using namespace std;

template <typename T>
Set<T>::Set(std::initializer_list<T> il)
{
    for (const auto x : il)
        insert(x);
}

template <typename T>
template <typename Iterator> 
Set<T>::Set(Iterator first, Iterator last) {
    for (Iterator it = first; it != last; it = next(it))
        insert(*it);
}

template <typename T>
Set<T>::Set(const Set& rs){
    if(this != &rs){
        recursiveDelete(root);
        root = copy(rs.root);
    }
}

template <typename T>
Set<T>& Set<T>::operator=(const Set<T>& rs)
{
    if(this != &rs){
        recursiveDelete(root);
        root = copy(rs.root);
    }
    return *this;
}

template <typename T>
void Set<T>::insert(const T& value)
{
    root = root->insert(root, value);
}

template <typename T>
void Set<T>::erase(const T& value)
{
    root = root->deleteNode(root, value);
}

template <typename T>
int Set<T>::size() const
{
    return root->getSize(root);
}

template <typename T>
bool Set<T>::empty() const
{
    return (root == NULL) ? true : false;
}

template <typename T>
typename Set<T>::iterator Set<T>::begin() const
{
    if (root != NULL)
        return BstIterator<T>(this, root->minKey(root));
    else
        return BstIterator<T>(this, NULL);
}

template <typename T>
typename Set<T>::iterator Set<T>::end() const
{
    return BstIterator<T>(this, NULL);
}

template <typename T>
typename Set<T>::iterator Set<T>::find(const T& value) const
{
    return BstIterator<T>(this, root->find(root, value));
}

template <typename T>
typename Set<T>::iterator Set<T>::lower_bound(const T& value) const
{
    return BstIterator<T>(this, root->lower_bound(root, value));
}



template <typename T>
TreapNode<T>* Set<T>::copy(TreapNode<T>* p)
{
    if (p == NULL)
        return NULL;
    TreapNode<T>* n = new TreapNode<T>(p->key, p->priority);
    n->left = copy(p->left);
    if(n->left != NULL)
        n->left->parent = n;
    n->right = copy(p->right);
    if(n->right != NULL)
        n->right->parent = n;
    n->mend(n);
    return n;
}

template <typename T>
void Set<T>::recursiveDelete(TreapNode<T>* root)
{
    if (root != NULL){
        recursiveDelete(root->left);
        recursiveDelete(root->right);
        delete(root);
    }
}






template <typename T>
BstIterator<T>::BstIterator(Set<T> const* my_setPtr, TreapNode<T>* node): 
    current(node), setPtr(my_setPtr)
{}

template <typename T>
typename BstIterator<T>::reference BstIterator<T>::operator*() const
{
    return current->key;
}

template <typename T>
BstIterator<T>& BstIterator<T>::operator++()
{
    current = current->successor(current);
    return *this;
}

template <typename T>
BstIterator<T> BstIterator<T>::operator++(int)
{
    BstIterator tmp = *this;
    current = current->successor(current);
    return tmp;
}

template <typename T>
BstIterator<T>& BstIterator<T>::operator--()
{
    if (current != NULL){
        current = current->predecessor(current);
    }
    else
        if (setPtr->root != NULL){
            current = setPtr->root->maxKey(setPtr->root);
        }
    return *this;
}

template <typename T>
BstIterator<T> BstIterator<T>::operator--(int)
{
    BstIterator tmp = *this;
    if (current != NULL){
        current = current->predecessor(current);
    }
    else
        if (setPtr->root != NULL){
            current = setPtr->root->maxKey(setPtr->root);
        }
    return tmp;
}

template <typename T>
bool BstIterator<T>::operator==(const BstIterator<T>& rhs)
{
    return current == rhs.current;
}

template <typename T>
bool BstIterator<T>::operator!=(const BstIterator<T>& rhs)
{
    return !(*this == rhs);
}