#pragma once
#include <iostream>
#include <iterator>
using namespace std;

template <typename T>
class TreapNode {
    public:
        T key;
        int size, priority;
        TreapNode *left, *right, *parent;
        TreapNode() {}
        TreapNode(const T&  key, const int& priority);
        ~TreapNode() {};
        TreapNode* insert(TreapNode* root, const T&  key);
        TreapNode* deleteNode(TreapNode* root, const T& key);
        TreapNode* find(TreapNode* root, const T& key);
        TreapNode* lower_bound(TreapNode* root, const T& key);
        TreapNode* successor(TreapNode* node);
        TreapNode* predecessor(TreapNode* node);
        void inorder(const TreapNode* root) const;
        bool empty(const TreapNode* root) const;
        bool operator==(const TreapNode* rhs);
        TreapNode* minKey(TreapNode* node);
        TreapNode* maxKey(TreapNode* node);
        TreapNode* newNode(T key);
        int getSize(TreapNode* node);
        void mend(TreapNode* node);
    private:
        TreapNode *rightRotate(TreapNode *y);
        TreapNode *leftRotate(TreapNode *x);
        
};

#include "treap.hpp"